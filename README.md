# AsgConfig

This is a package for testing out some ideas to upgrade the tool configuration
functionality provided by ASG. The end-goal is to provide infrastructure that
allows users to configure and manage their analysis tools in a similar way
across the two main environments (Athena, RootCore).

## Overview

The general strategy that I'm going with for now is to introduce services for
the RootCore environment which mimic the features in Athena/Gaudi for creating,
managing, and configuring tools. Then, with this alternate set of infrastructure
backends, providing a common way to specify tool configuration via config files.
This strategy differs from the dual-use pattern of AsgTool, in which the base
class implementation is switched at compile-time. Another strategy would be to
try and make the Athena/Gaudi services useable outside of the framework. This
choice of approach can be revisited.

Some design goals:

1. Backwards compatibility; don't break existing workflows. I.e., the new
   infrastructure should be optional.
2. Robust lifetime management of tools and services. E.g., don't use static
   lifetime management of tools, avoid singletons, etc.
3. Modular structure; clear division of responsiblity.

The basic components that are being tested for the upgrade are:
* Property objects that hold a property value to store in a catalog.
* A configuration service (i.e. JO svc) which can hold properties that will
  be assigned to tools upon tool creation.
* A standalone tool service for AsgTools which uses a ROOT-dictionary-based
  factory creation mechanism.
* An upgraded ToolHandle which can talk to this new tool service to retrieve,
  and create configured tools on demand.

## Design discussions

### Property value storage and assignment

In Gaudi, the Property class can either reference a tool's member variable or
it can allocate its own variable for storage in a catalog. However, the
AsgTools Property class only provides the former, so I need to implement a
solution for storing property values in a catalog at configuration time.

Possible solutions for property storage:

1. Extend AsgTools Property to be able to allocate its value and store that.
2. Store the actual Property _values_ in a separate structure in the catalog
   and use the AsgTools Property class to reference those.
3. Implement a new type of property object that owns its value and store that.

For now, I've implemented option 3 as the [PropertyVal] (AsgConfig/PropertyVal.h)
class. Similar to the other Property implementations, a derived template class
handles the value type. I don't actually think this is the best long-term
solution.

The catalog of PropertyVals is for now in a [ConfigSvc] (AsgConfig/ConfigSvc.h)
class which also provides a configureTool method.

### Tool management

How should the lifetime of the tools be managed?

1. Shared or unique ownership by clients in a tool handle.
2. Unique ownership by a tool service.

Gaudi technically uses reference counting but as far as I can tell in practice
the ToolSvc triggers finalization of the tools and serves as the owner. For now
I'm following the service-owned model (#2), though solution 1 may actually be
a more appealing approach in the long run as it de-couples the tool lifetime
from the tool service lifetime and can strictly enforce private-ness of tools.

The current implementation is the [AsgToolSvc] (AsgConfig/AsgToolSvc.h).

### Service design and management

Before this stuff is set in stone it will be important to converge on an exact
definition of what "service" means outside of Athena/Gaudi. For now I'm loosely
taking it to mean a shared component which simply corresponds to some existing
service functionality in Athena/Gaudi.

How could services be managed?

1. Singleton pattern.
2. Shared ownership by clients.
3. Unique ownership by a service manager or registry.

Option 1 should probably be avoided because
[singletons are bad] (https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-singleton).
Also, with my current choice of tool management in a tool service this could
cause problems due to static lifetime management of tools.

For now I'm going with option 2. A [ServiceStore] (AsgConfig/ServiceStore.h)
holds a weak\_ptr registry so that clients can retrieve shared\_ptrs to a
service by name.

I don't currently have a smart mechanism for service creation. For now, clients
create the initial services and then they can be retrieved. It wouldn't be too
difficult to use a ROOT dict factory method, though I may need a way to ensure
services stay alive in between usages during initialization.

There are a number of additional open questions, such as:
* Does this infrastructure require a new implementation of ServiceHandle?
  * maybe...
* Should there be a common AsgService base class?
  * could help with boiler plate.
* Should these services also be configurable like a tool is, with properties?
  * things quickly getting complicated...
* Should we mirror the initialize() state of Gaudi services?
  * nicer to grab all resources at construction if possible.

### Incoporation into ToolHandle

I have a modified version of the AsgTools ToolHandle:
[asg::dev::ToolHandle] (AsgConfig/ToolHandle.h). The handle will
preferentially check for existence of the AsgToolSvc and try to retrieve its
tool from there. For backwards compatibility, for now it will fall back to the
usual ToolStore based retrieval if the AsgToolSvc doesn't exist.

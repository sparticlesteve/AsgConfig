# AsgConfig

This is a package for testing out some ideas to upgrade the tool configuration
functionality provided by ASG. The end-goal is to have an environment that
allows users to configure and manage their analysis tools in a uniform way
across the two main environments (Athena, RootCore), with support for
configuration files.

## Overview

The basic components that are being tested for the upgrade are:
* Property objects that hold a property value to store in a catalog.
* A configuration service (i.e. JO svc) which can hold properties that will
  be assigned to tools upon tool creation.
  * Currently called ConfigSvc.
* A standalone tool service for AsgTools which uses a ROOT-dictionary-based
  factory creation mechanism
  * Currently called AsgToolSvc.
* An upgraded ToolHandle which can talk to this new tool service to retrieve,
  and create configured tools on demand.
  * Currently dev::ToolHandle.

The design details are in a high state of flux. Some discussions follow below.

## Design discussions

### Property value storage

What I've done for now is to introduce a new set of property classes that own
a value. The Property classes in AsgTools for standalone usage currently do
not have this capability. They hold a pointer to the actual property member
variable in a tool. If the AsgTools property objects were modified to be able
to hold their values (like the Gaudi counterparts), then those classes could
simply be reused here.

### Applying properties to tools

The standalone version of the PropertyMgr is missing the interface to set
a tool's property using a Property object. Such a method would simplify this
functionality here. For now, instead, the PropertyVal objects in this package
have a method which takes a PropertyMgr ptr and applies itself to the tool.

### What exactly is a service?

For now I'm just using the term service to represent a shared component for
the standalone environment only. This could be confusing, so it might be good
to nail down the real terms and definitions before any code is released. It is
worth noting, at least, that the concept of a service here is actually fairly
close to the gaudi concept of a service. However, I'm not writing dual-use
services. I am instead writing standalone _replacements_ for gaudi services.

### Design of services and tool lifetime management

A few questions need to be answered:

1. How should the lifetime of the tools be managed?
  * shared/unique ownership by clients?
  * unique ownership by the tool service?
2. How should the AsgToolSvc (or other services') lifetime be managed?
  * as a singleton?
  * shared ownership by clients?
  * unique ownership by a service manager or registry?
3. How should the services like AsgToolSvc be accessed by clients like the
   ToolHandle?
  * via singleton global access?
  * via a global service registry?

These questions are closely coupled because certain solutions to some questions
rule out possible solutions to others. One constraint is that the tools cannot
be managed with static lifetime. So, if the tool svc is a singleton, then it
cannot own the tools.

Here are a few scenarios that could work:

1. Singleton toolsvc, client-shared ownership of tools (unique\_ptr for private
   tools)
2. Client-shared toolsvc, retrieved via a weak\_ptr registry, owns the tools
3. Client-shared toolsvc, with client-shared tools

I've decided to start with option number #2 for now. I can consider other
possibilities later, particularly after some discussion with other developers.
In this model, the ToolHandle can retrieve the AsgToolSvc via a static
ServiceStore which functions a lot like the AsgTools/ToolStore (except for the
reference counting).

#ifndef ASGCONFIG_TOOLHANDLE_H
#define ASGCONFIG_TOOLHANDLE_H

// Local include(s):
#include "AsgTools/AsgToolsConf.h"

#ifdef ASGTOOL_ATHENA
#   include "GaudiKernel/ToolHandle.h"

// TODO: Does this actually work?
namespace dev
{
  template<class T>
  using ::ToolHandle<T>;
}

#elif defined(ASGTOOL_STANDALONE)

// System include(s):
#include <string>
#include <iosfwd>
#include <memory>

// Local include(s):
#include "AsgTools/StatusCode.h"
#include "AsgConfig/AsgToolSvc.h"

namespace asg {
   class IAsgTool;
}

namespace dev
{

/// Non-templated base class for the ToolHandle types
///
/// This base class takes care of implementing all the functionality of
/// ToolHandle that doesn't depend on the template parameter of the class.
/// Making the built binaries a bit smaller, and faster.
///
/// @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
///
/// $Revision: 724296 $
/// $Date: 2016-02-16 08:24:42 -0800 (Tue, 16 Feb 2016) $
///
class ToolHandleBase {

public:
   /// Constructor with a type/name string
   ToolHandleBase( const std::string& typeAndName = "", asg::IAsgTool* parent = 0 );

   /// Return the type/name string specified by the user
   const std::string& typeAndName() const;
   /// Return the tool's type name
   const std::string& type() const;
   /// Return the tool's instance name
   const std::string& name() const;
   /// Return the tool's parent tool name
   const std::string& parentName() const;

   /// Change the handle's type and name
   void setTypeAndName(const std::string& typeAndName);
   /// Change the handle's name
   void setName(const std::string& name);

protected:
   /// The type/name string specified in the constructor
   std::string m_typeAndName;
   /// The type name of the target tool
   std::string m_type;
   /// The instance name of the target tool
   std::string m_name;
   /// The name of the parent ool
   std::string m_parentName;

}; // class ToolHandleBase

/// Partial re-implementation of Gaudi's ToolHandle class
///
/// This class can be used in a dual-use tool to find other dual-use tools
/// that have been instantiated by the user.
///
/// @author David Adams <dladams@bnl.gov>
/// @author Attila Krasznahorkay <Attila.Krasznahorkay@cern.ch>
///
/// $Revision: 724296 $
/// $Date: 2016-02-16 08:24:42 -0800 (Tue, 16 Feb 2016) $
///
template< class T >
class ToolHandle : public ToolHandleBase {

public:
   /// A convenience type declaration
   typedef T value_type;

   /// Constructor from a tool pointer
   ToolHandle( T* ptool = 0 );

   /// Constructor from a tool name.
   /// Testing out a simple constructor argument and member pointer to the
   /// AsgToolSvc. This is _not_ a good long-term solution.
   ToolHandle( const std::string& toolname, asg::IAsgTool* parent = 0 );

   /// Dereferencing operator
   T& operator*() const;
   /// Dereferencing operator
   T* operator->() const;

   /// Retrieve tool.
   /// For compatibility with Gaudi.
   /// Returns success if pointer is non-null and of the correct type.
   StatusCode retrieve() const;

   /// Return true if tool has no pointer or name
   bool empty() const;

   /// Return if the pointer is set
   bool isSet() const;

private:

   /// Try to retrieve the tool from the tool svc
   void retrieveTool() const;

   /// Pointer to the tool
   mutable T* m_ptool;

   /// Pointer to the standalone tool service.
   /// TODO: use an interface for this.
   std::shared_ptr<ana::AsgToolSvc> m_toolSvc;

}; // class ToolHandle

/// A convenience operator for printing the values of such objects
template< class T >
std::ostream& operator<< ( std::ostream& out,
                           const ToolHandle< T >& handle );

} // namespace dev

// Include the implementation of the code:
#include "AsgConfig/ToolHandle.icc"

#else
#   error "What environment are we in?!?"
#endif // Environment selection
#endif // ASGCONFIG_TOOLHANDLE_H

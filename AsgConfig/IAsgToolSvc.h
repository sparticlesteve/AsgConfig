#ifndef ASGCONFIG_IASGTOOLSVC_H
#define ASGCONFIG_IASGTOOLSVC_H

// STL includes
#include <string>

// Local includes
#include "AsgConfig/IAsgService.h"

// Forward declarations
namespace asg
{
  class IAsgTool;
}

namespace asg
{
  
  /// @class IAsgToolSvc
  /// @brief An interface for a standalone (non-Athena) AsgTool service.
  ///
  /// Design is subject to change.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class IAsgToolSvc : public virtual asg::IAsgService
  {

    public:

      /// Retrieve a tool by type and name.
      virtual asg::IAsgTool*
      getTool(const std::string& name, const std::string& type) = 0;

      /// Retrieve tool cast to a specified type
      template<class T>
      T* getToolCast(const std::string& name, const std::string& type)
      {
        return dynamic_cast<T*>( getTool(name, type) );
      }

  }; // class IAsgToolSvc

} // namespace asg

#endif

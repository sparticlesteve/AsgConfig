#ifndef ASGCONFIG_ICONFIGSVC_H
#define ASGCONFIG_ICONFIGSVC_H

// STL includes
#include <string>

// Local includes
#include "AsgConfig/IAsgService.h"
#include "AsgConfig/PropertyVal.h"

// Forward declarations
namespace asg
{
  class AsgTool;
}

namespace asg
{

  /// @class IConfigSvc
  /// @brief An interface for a standalone AsgTool configuration service.
  ///
  /// Design is subject to change.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class IConfigSvc : public virtual asg::IAsgService
  {

    public:

      /// @brief Assign one property for a tool.
      virtual void
      setProperty(const std::string& toolName, const ana::PropertyVal* prop) = 0;

      /// @brief Get the list of properties for a tool
      virtual const ana::PropertyValList&
      getProperties(const std::string& toolName) const = 0;

      /// Configure a tool with properties
      virtual StatusCode configureTool(asg::AsgTool* tool) = 0;

  }; // class IConfigSvc

} // namespace asg

#endif

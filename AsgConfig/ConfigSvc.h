#ifndef ASGCONFIG_CONFIG_SVC_H
#define ASGCONFIG_CONFIG_SVC_H

// Eventaully should only be compiled outside of Athena
#ifdef ROOTCORE

// System includes
#include <memory>
#include <string>
#include <map>

// Framework includes
#include "AsgTools/AsgMessaging.h"

// Local includes
#include "AsgConfig/PropertyVal.h"

// Forward declarations
namespace asg
{
  class AsgTool;
}

namespace ana
{

  /// @class ConfigSvc
  /// @brief Singleton service for holding/applying tool config properties.
  ///
  /// We store here PropertyVal objects which hold their own values, rather
  /// than use AsgTools/Property objects which do not.
  ///
  /// I would prefer not to use a singleton, but I think we'll need more
  /// infrastructure first.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class ConfigSvc : public asg::AsgMessaging
  {

    public:

      /// Retrieve the singleton instance.
      static ConfigSvc& getInstance();

      /// @brief Assign one property for a tool.
      /// The given property is copied into storage.
      void setProperty(const std::string& toolName,
                       const PropertyVal* prop);

      /// Assign list of properties to a tool.
      /// The given list is copied into storage.
      void setProperties(const std::string& toolName,
                         const PropertyValList& props);

      /// Get the list of properties registered for a tool
      const PropertyValList& getProperties(const std::string& toolName) const;

      /// Configure a tool with known properties.
      StatusCode configureTool(asg::AsgTool* tool);

    private:

      /// Private constructor
      ConfigSvc();

      /// PropertyVal storage map type
      using PropMap = std::map< std::string, PropertyValList >;

      /// PropertyVal storage map
      PropMap m_props;

  }; // class ConfigSvc

} // namespace ana

#endif // ROOTCORE

#endif

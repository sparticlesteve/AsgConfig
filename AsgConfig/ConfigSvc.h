#ifndef QUICK_ANA__CONFIG_SVC_H
#define QUICK_ANA__CONFIG_SVC_H

// Eventaully should only be compiled outside of Athena
#ifdef ROOTCORE

// System includes
#include <memory>
#include <string>
#include <map>

// Framework includes
#include "AsgTools/AsgMessaging.h"

// Local includes
#include "AsgConfig/Property.h"

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
  /// We store here AsgConfig's custom Property objects rather than the AsgTools
  /// Property because we need to own the internal property values.
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
                       const Property* prop);

      /// Assign list of properties to a tool.
      /// The given list is copied into storage.
      void setProperties(const std::string& toolName,
                         const PropertyList& props);

      /// Configure a tool with known properties.
      StatusCode configureTool(asg::AsgTool* tool);

    private:

      /// Private constructor
      ConfigSvc();

      /// Property storage map type
      using PropMap = std::map< std::string, PropertyList >;

      /// Property storage map
      PropMap m_props;

  }; // class ConfigSvc

} // namespace ana

#endif // ROOTCORE

#endif

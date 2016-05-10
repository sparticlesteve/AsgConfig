#ifndef ASGCONFIG_CONFIGSVC_H
#define ASGCONFIG_CONFIGSVC_H

// Eventaully should only be compiled outside of Athena
#ifdef ROOTCORE

// System includes
#include <memory>
#include <string>
#include <map>

// Framework includes
#include "AsgTools/AsgMessaging.h"

// Local includes
#include "AsgConfig/IConfigSvc.h"
#include "AsgConfig/PropertyVal.h"

// Forward declarations
namespace asg
{
  class AsgTool;
}

namespace ana
{

  /// @class ConfigSvc
  /// @brief A service for holding/applying tool config properties.
  ///
  /// We store here PropertyVal objects which hold their own values, rather
  /// than use AsgTools/Property objects which do not.
  ///
  /// This design is subject to change.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class ConfigSvc : public virtual asg::IConfigSvc,
                    public asg::AsgMessaging
  {

    public:

      /// Standard constructor
      ConfigSvc(const std::string& name);

      /// Service name
      virtual const std::string& name() const override final { return m_name; }

      /// @brief Assign one property for a tool.
      /// The given property is copied into storage.
      virtual void setProperty(const std::string& toolName,
                               const PropertyVal* prop) override final;

      /// @brief Assign list of properties to a tool.
      /// The given list is copied into storage.
      /// @todo TODO: do we want this?
      void setProperties(const std::string& toolName,
                         const PropertyValList& props);

      /// Get the list of properties registered for a tool
      virtual const PropertyValList&
      getProperties(const std::string& toolName) const override final;

      /// Configure a tool with known properties.
      virtual StatusCode configureTool(asg::AsgTool* tool) override final;

    private:

      /// PropertyVal storage map type
      using PropMap = std::map< std::string, PropertyValList >;

      /// PropertyVal storage map
      PropMap m_props;

      /// Service name
      std::string m_name;

  }; // class ConfigSvc

} // namespace ana

#endif // ROOTCORE

#endif

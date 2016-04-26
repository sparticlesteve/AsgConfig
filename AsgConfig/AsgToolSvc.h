#ifndef ASGCONFIG_ASGTOOLSVC_H
#define ASGCONFIG_ASGTOOLSVC_H

// Should only be compiled outside of Athena
#ifdef ROOTCORE

// System includes
#include <memory>
#include <string>
#include <unordered_map>

// Framework includes
#include "AsgTools/AsgMessaging.h"
#include "AsgTools/IAsgTool.h"

// Local includes
#include "AsgConfig/IAsgService.h"

// Forward declarations
namespace asg
{
  class AsgTool;
}
namespace ana
{
  class ConfigSvc;
}

namespace ana
{

  /// @class AsgToolSvc
  /// @brief A service for constructing and configuring AsgTools.
  ///
  /// This design is likely to change.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class AsgToolSvc : public virtual asg::IAsgService,
                     public asg::AsgMessaging
  {

    public:

      /// Standard constructor
      AsgToolSvc(const std::string& name);

      /// Service name
      virtual const std::string& name() const override final { return m_name; }

      /// @brief Retrieve a tool by type and name.
      ///
      /// This method will check for an already-existing tool and return it.
      /// If the tool doesn't already exist, it will be constructed and
      /// configured according to the contents of the ConfigSvc.
      asg::IAsgTool* getTool(const std::string& name, const std::string& type);

      /// Retrieve tool cast to a specified type
      template<class T>
      T* getToolCast(const std::string& name, const std::string& type)
      {
        return dynamic_cast<T*>( getTool(name, type) );
      }

    private:

      /// Construct a tool using the ROOT dictionary
      std::unique_ptr<asg::AsgTool> createTool(const std::string& name,
                                               const std::string& type);

      /// Tool storage
      std::unordered_map< std::string, std::unique_ptr<asg::IAsgTool> > m_tools;

      /// Pointer to the standalone ConfigSvc.
      /// TODO: use an interface.
      std::shared_ptr<ConfigSvc> m_configSvc;

      /// Service name
      std::string m_name;

  }; // class AsgToolSvc

} // namespace ana

#endif // ROOTCORE

#endif

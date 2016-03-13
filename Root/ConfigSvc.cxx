// Framework includes
#include "AsgTools/AsgTool.h"

// Local includes
#include "AsgConfig/ConfigSvc.h"
#include "AsgConfig/PropertyUtil.h"

namespace ana
{

  //---------------------------------------------------------------------------
  // Retrieve the singleton instance
  //---------------------------------------------------------------------------
  ConfigSvc& ConfigSvc::getInstance()
  {
    static ConfigSvc conf;
    return conf;
  }

  //---------------------------------------------------------------------------
  // Store one property for a tool
  //---------------------------------------------------------------------------
  void ConfigSvc::setProperty(const std::string& toolName,
                              const Property* prop)
  {
    // Clone the property into our own storage
    m_props[toolName].updateProperty( std::move(prop->clone()) );
  }

  //---------------------------------------------------------------------------
  // Store list of properties for a tool
  //---------------------------------------------------------------------------
  void ConfigSvc::setProperties(const std::string& toolName,
                                const PropertyList& props)
  {
    auto& propList = m_props[toolName];
    for(auto prop : props)
      propList.updateProperty( std::move(prop->clone()) );
  }

  //---------------------------------------------------------------------------
  // Configure a tool
  //---------------------------------------------------------------------------
  StatusCode ConfigSvc::configureTool(asg::AsgTool* tool)
  {
    // Find the property list for this tool
    auto itr = m_props.find(tool->name());
    if(itr != m_props.end()) {
      for(auto prop : itr->second) {
        ATH_CHECK( applyProperty(prop, tool) );
      }
    }
    return StatusCode::SUCCESS;
  }

  //---------------------------------------------------------------------------
  // Constructor
  //---------------------------------------------------------------------------
  ConfigSvc::ConfigSvc()
    : AsgMessaging("ConfigSvc")
  {
  }

} // namespace ana

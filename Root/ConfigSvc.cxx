// Framework includes
#include "AsgTools/AsgTool.h"

// Local includes
#include "AsgConfig/ServiceStore.h"
#include "AsgConfig/ConfigSvc.h"

namespace ana
{

  //---------------------------------------------------------------------------
  // Constructor
  //---------------------------------------------------------------------------
  ConfigSvc::ConfigSvc(const std::string& name)
    : asg::AsgMessaging(name), m_name(name)
  {}

  //---------------------------------------------------------------------------
  // Store one property for a tool
  //---------------------------------------------------------------------------
  void ConfigSvc::setProperty(const std::string& toolName,
                              const PropertyVal* prop)
  {
    // Clone the property into our own storage
    m_props[toolName].updateProperty( std::move(prop->clone()) );
  }

  //---------------------------------------------------------------------------
  // Store list of properties for a tool
  //---------------------------------------------------------------------------
  void ConfigSvc::setProperties(const std::string& toolName,
                                const PropertyValList& props)
  {
    auto& propList = m_props[toolName];
    for(auto prop : props)
      propList.updateProperty( std::move(prop->clone()) );
  }

  //---------------------------------------------------------------------------
  // Get list of properties for a tool
  //---------------------------------------------------------------------------
  const PropertyValList& ConfigSvc::getProperties(const std::string& toolName) const
  {
    static const PropertyValList emptyList;
    auto itr = m_props.find(toolName);
    if(itr != m_props.end())
      return itr->second;
    else
      return emptyList;
  }

  //---------------------------------------------------------------------------
  // Configure a tool
  //---------------------------------------------------------------------------
  StatusCode ConfigSvc::configureTool(asg::AsgTool* tool)
  {
    // Find the property list for this tool
    auto itr = m_props.find( tool->name() );
    auto propMgr = tool->getPropertyMgr();
    if(itr != m_props.end()) {
      for(auto prop : itr->second) {
        ATH_CHECK( prop->applyProperty(propMgr) );
      }
    }
    return StatusCode::SUCCESS;
  }

} // namespace ana

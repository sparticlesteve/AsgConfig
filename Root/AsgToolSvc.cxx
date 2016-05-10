// ROOT includes
#include "TClass.h"
#include "TInterpreter.h"

// Framework includes
#include "AsgTools/ToolStore.h"
#include "AsgTools/AsgTool.h"

// Local includes
#include "AsgConfig/AsgToolSvc.h"
#include "AsgConfig/ServiceStore.h"
#include "AsgConfig/IConfigSvc.h"

namespace ana
{

  //---------------------------------------------------------------------------
  // Constructor
  //---------------------------------------------------------------------------
  AsgToolSvc::AsgToolSvc(const std::string& name)
    : asg::AsgMessaging(name), m_name(name)
  {}

  //---------------------------------------------------------------------------
  // Retrieve a tool by type and name
  //---------------------------------------------------------------------------
  asg::IAsgTool* AsgToolSvc::getTool(const std::string& name,
                                     const std::string& type)
  {
    // First, look for the tool in our map
    auto toolItr = m_tools.find(name);
    if(toolItr == m_tools.end()) {

      // We don't have the tool, but maybe it's in the ToolStore,
      // in which case we don't own it.
      const bool silent = true;
      auto storeTool =
        dynamic_cast<asg::AsgTool*>( asg::ToolStore::get(name, silent) );
      if(storeTool) return storeTool;

      // If the tool doesn't exist, then we need to create it
      auto tool = createTool(name, type);
      if(!tool) {
        ATH_MSG_ERROR("Failed to create tool: " << name);
        return nullptr;
      }

      // Configure the tool via the IConfigSvc
      // TODO: I need a nicer way to deal with the ConfigSvc.
      if(!m_configSvc) {
        m_configSvc = asg::ServiceStore::get<asg::IConfigSvc>("ConfigSvc");
        if(!m_configSvc) {
          ATH_MSG_WARNING("Failed to retrieve ConfigSvc");
        }
      }
      if(m_configSvc) {
        if(m_configSvc->configureTool(tool.get()).isFailure())
          return nullptr;
      }

      // Initialize the tool
      if(tool->initialize().isFailure()) {
        ATH_MSG_ERROR("Failure initializing " << name);
        return nullptr;
      }

      // Insert it in our map
      toolItr = m_tools.insert( std::make_pair(name, std::move(tool)) ).first;
    }

    // Return the tool
    return toolItr->second.get();
  }

  //---------------------------------------------------------------------------
  // Create a tool using the ROOT dictionary
  //---------------------------------------------------------------------------
  std::unique_ptr<asg::AsgTool>
  AsgToolSvc::createTool(const std::string& name, const std::string& type)
  {
    ATH_MSG_DEBUG("Creating tool of type " << type);

    // Load the ROOT dictionary
    TClass* toolClass = TClass::GetClass( type.c_str() );
    if(!toolClass){
      ATH_MSG_ERROR("Unable to load class dictionary for type " << type);
      return nullptr;
    }

    // In order to call a non-default constructor with the ROOT dictionary,
    // we have to perform some low-level ROOT interpreter magic. First, we
    // need the name of the constructor, which we get by stripping off the
    // namespace prefix.
    std::string constructorName = type.substr( type.rfind(":") + 1 );

    // Next, we prepare the constructor function.
    auto callFunc = gInterpreter->CallFunc_Factory();
    long offset = 0; // not relevant for ctors
    const char* argForm = "const std::string&";
    gInterpreter->CallFunc_SetFuncProto(callFunc, toolClass->GetClassInfo(),
                                        constructorName.c_str(), argForm,
                                        &offset);

    // Make sure the function is well-formed
    if(!gInterpreter->CallFunc_IsValid(callFunc)) {
      ATH_MSG_ERROR("Invalid constructor call for type " << type <<
                    " and constructor " << constructorName);
      gInterpreter->CallFunc_Delete(callFunc);
      return nullptr;
    }

    // Set the name constructor argument
    gInterpreter->CallFunc_SetArg(callFunc, &name);

    // Call the function. Here it's a little strange, because the ROOT function
    // returns a 'long', so we have to cast it back to a useful pointer.
    auto tool = reinterpret_cast<asg::AsgTool*>
      ( gInterpreter->CallFunc_ExecInt(callFunc, 0) );

    // Cleanup the CallFunc
    gInterpreter->CallFunc_Delete(callFunc);

    // Construct tool from dictionary with TClass::New.
    // Doesn't work. Requires a default constructor.
    ////asg::AsgTool* tool = static_cast<asg::AsgTool*>( toolClass->New() );
    ////tool->setName(name);

    // Return it wrapped in a smart pointer
    return std::unique_ptr<asg::AsgTool>(tool);
  }

} // namespace ana

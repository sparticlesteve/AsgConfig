// System includes
#include <string>

// Framework includes
#include "AsgTools/AsgTool.h"

// Local includes
#include "AsgTools/MessageCheck.h"
#include "AsgConfig/Property.h"
#include "AsgConfig/PropertyUtil.h"

ANA_MSG_SOURCE(msgPropUtil, "PropertyUtil")

// Anonymous namespace for template helper function
namespace
{

  //---------------------------------------------------------------------------
  // Template function to apply a property to a tool.
  //---------------------------------------------------------------------------
  template<class T>
  StatusCode applyPropertyT(const ana::Property* prop, asg::AsgTool* tool)
  {
    using namespace msgPropUtil;

    // Try to cast the property
    auto typeProp = dynamic_cast<const ana::PropertyT<T>*>(prop);
    if(!typeProp) return StatusCode::FAILURE;
    ANA_CHECK( tool->setProperty(prop->name(), typeProp->value()) );
    return StatusCode::SUCCESS;
  }

}


namespace ana
{

  //---------------------------------------------------------------------------
  // Apply property to tool
  //---------------------------------------------------------------------------
  StatusCode applyProperty(const ana::Property* prop, asg::AsgTool* tool)
  {
    using namespace msgPropUtil;

    if(prop->type() == typeid(bool)) {
      ANA_CHECK( applyPropertyT<bool>(prop, tool) );
    }
    else if(prop->type() == typeid(int)) {
      ANA_CHECK( applyPropertyT<int>(prop, tool) );
    }
    else if(prop->type() == typeid(float)) {
      ANA_CHECK( applyPropertyT<float>(prop, tool) );
    }
    else if(prop->type() == typeid(std::string)) {
      ANA_CHECK( applyPropertyT<std::string>(prop, tool) );
    }
    else{
      ANA_MSG_ERROR( "Unknown property type: " << prop->type().name() );
      return StatusCode::FAILURE;
    }
    return StatusCode::SUCCESS;
  }

} // namespace ana

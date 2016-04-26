#include "AsgTools/MessageCheck.h"
#include "AsgTools/UnitTest.h"

#include "CxxUtils/make_unique.h"

#include "gtest/gtest.h"

#include "AsgConfig/ConfigSvc.h"
#include "AsgConfig/ChildTool.h"

namespace
{
  using namespace ana;

  TEST(ConfigSvcTest, EmptyProperties)
  {
    ConfigSvc configSvc("ConfigSvc");
    const auto& propList = configSvc.getProperties("test");
    EXPECT_EQ( propList.size(), 0u );
  }

  TEST(ConfigSvcTest, ConfigureTool)
  {
    ConfigSvc configSvc("ConfigSvc");
    const std::string toolName = "TestTool";
    ana::FloatProperty ptProp("MuonPtMin", 20.f);
    ana::StringProperty stringProp("StringProp", "testString");
    ana::BoolProperty boolProp("BoolProp", true);
    configSvc.setProperty(toolName, &ptProp);
    configSvc.setProperty(toolName, &stringProp);
    configSvc.setProperty(toolName, &boolProp);
    ChildTool tool(toolName);
    EXPECT_SUCCESS( configSvc.configureTool(&tool) );
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

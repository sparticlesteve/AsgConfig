// Support
#include "AsgTools/MessageCheck.h"
#include "AsgTools/UnitTest.h"
#include "gtest/gtest.h"
#ifdef ROOTCORE
#  include "xAODRootAccess/Init.h"
#endif

// Local includes
#include "AsgConfig/AsgToolSvc.h"

// STL
#include <string>

namespace
{
  using namespace asg::msgUserCode;

  TEST(ToolSvcTest, CreateTool)
  {
    ana::AsgToolSvc toolSvc("AsgToolSvc");
    const std::string toolName = "ChildTool";
    const std::string toolType = "ChildTool";
    auto tool = toolSvc.getTool(toolName, toolType);
    EXPECT_TRUE( tool != nullptr );
  }
}

int main(int argc, char** argv)
{
#ifdef ROOTCORE
  StatusCode::enableFailure();
  ANA_CHECK( xAOD::Init() );
#endif
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

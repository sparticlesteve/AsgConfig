#include "CxxUtils/make_unique.h"

#include "AsgConfig/ToolHandle.h"
#include "AsgConfig/IMyTool.h"

#include "AsgTools/MessageCheck.h"
#include "AsgTools/UnitTest.h"
#include "AsgTools/UnitTestTool1.h"
#include "AsgTools/UnitTestTool2.h"

#include "gtest/gtest.h"

#include "xAODRootAccess/Init.h"

using namespace asg::msgUserCode;

TEST( HandleTest, Empty )
{
  dev::ToolHandle<IMyTool> handle("");
  ASSERT_TRUE( handle.empty() );
}

TEST( HandleTest, NonEmptyName )
{
  dev::ToolHandle<IMyTool> handle("test");
  ASSERT_FALSE( handle.empty() );
}

TEST( HandleTest, NonEmptyPtr )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool1>("test");
  dev::ToolHandle<asg::IUnitTestTool1> handle( tool.get() );
  ASSERT_FALSE( handle.empty() );
}

TEST( HandleTest, RetrieveEmpty )
{
  dev::ToolHandle<asg::IUnitTestTool1> handle;
  ASSERT_FAILURE( handle.retrieve() );
}

TEST( HandleTest, RetrieveName )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool1>("test");
  ToolHandle<asg::IUnitTestTool1> handle("test");
  ASSERT_SUCCESS( handle.retrieve() );
}

TEST( HandleTest, RetrievePtr )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool1>("test");
  dev::ToolHandle<asg::IUnitTestTool1> handle( tool.get() );
  ASSERT_SUCCESS( handle.retrieve() );
}

TEST( HandleTest, DereferenceName )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool1>("test");
  dev::ToolHandle<asg::IUnitTestTool1> handle("test");
  ASSERT_EQ( &*handle, tool.get() );
}

TEST( HandleTest, DereferenceWrongType )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool2>("test");
  dev::ToolHandle<asg::IUnitTestTool1> handle("test");
  ASSERT_THROW_REGEX( *handle, "Couldn't find tool with name" );
}

TEST( HandleTest, DereferencePtr )
{
  auto tool = CxxUtils::make_unique<asg::UnitTestTool1>("test");
  dev::ToolHandle<asg::IUnitTestTool1> handle( tool.get() );
  ASSERT_EQ( &*handle, tool.get() );
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

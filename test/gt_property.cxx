#include "AsgTools/MessageCheck.h"
#include "AsgTools/UnitTest.h"
#include "CxxUtils/make_unique.h"

#include "AsgConfig/Property.h"

#include "gtest/gtest.h"

namespace
{
  using CxxUtils::make_unique;
  using ana::BoolProperty;
  using ana::IntProperty;
  using ana::FloatProperty;
  using ana::StringProperty;
  using ana::PropertyValList;

  using namespace asg::msgUserCode;

  TEST(PropertyTest, NameEqual)
  {
    StringProperty stringProp("StringProp", "Pi");
    EXPECT_EQ( stringProp.name(), "StringProp" );
  }

  TEST(PropertyTest, BoolValue)
  {
    EXPECT_TRUE( BoolProperty("BoolProp", true).value() );
    EXPECT_FALSE( BoolProperty("BoolProp", false).value() );
  }

  TEST(PropertyTest, IntVal)
  {
    IntProperty intProp("IntProp", 42);
    EXPECT_EQ( intProp.value(), 42 );
  }

  TEST(PropertyTest, FloatVal)
  {
    FloatProperty floatProp("FloatProp", 3.14f);
    EXPECT_EQ( floatProp.value(), 3.14f );
  }

  TEST(PropertyTest, StringVal)
  {
    StringProperty stringProp("StringProp", "Pi");
    EXPECT_EQ( stringProp.value(), "Pi" );
  }

  TEST(PropertyTest, CloneEqual)
  {
    StringProperty stringProp("StringProp", "Pi");
    auto propClone = stringProp.clone();
    auto propTClone = dynamic_cast<StringProperty*>( propClone.get() );
    ASSERT_TRUE( propTClone != nullptr );
    EXPECT_EQ( propTClone->name(), stringProp.name() );
    EXPECT_EQ( propTClone->type(), stringProp.type() );
    EXPECT_EQ( propTClone->value(), stringProp.value() );
  }

  // List of properties test fixture
  class PropertyValListTest : public ::testing::Test {
    protected:
      PropertyValListTest() {
        propList.updateProperty( make_unique<BoolProperty>("BoolProp", true) );
        propList.updateProperty( make_unique<IntProperty>("IntProp", 42) );
        propList.updateProperty( make_unique<FloatProperty>("FloatProp", 3.14f) );
        propList.updateProperty( make_unique<StringProperty>("StringProp", "Pi") );
      }
      PropertyValList propList;
  };

  TEST_F(PropertyValListTest, CopyConstruct)
  {
    PropertyValList copyList(propList);
    ASSERT_EQ( propList.size(), copyList.size() );
    // TODO: need a good way to test property equality
  }

  TEST_F(PropertyValListTest, MoveAssign)
  {
    const auto num = propList.size();
    PropertyValList otherList = std::move(propList);
    EXPECT_EQ( propList.size(), 0u );
    EXPECT_EQ( otherList.size(), num );
    auto prop = otherList.find("StringProp");
    ASSERT_TRUE( prop != nullptr );
    auto stringProp = dynamic_cast<const StringProperty*>(prop);
    ASSERT_TRUE( stringProp != nullptr );
    EXPECT_EQ( stringProp->value(), "Pi" );
  }

  TEST_F(PropertyValListTest, Find)
  {
    auto prop = propList.find("FloatProp");
    ASSERT_TRUE( prop != nullptr );
    auto floatProp = dynamic_cast<const FloatProperty*>(prop);
    ASSERT_TRUE( floatProp != nullptr );
    EXPECT_EQ( floatProp->value(), 3.14f );
  }

  TEST_F(PropertyValListTest, FindNull)
  {
    auto p = propList.find("NotFound");
    EXPECT_TRUE( p == nullptr );
  }

} // namespace

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

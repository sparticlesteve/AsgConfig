// ASG toolkit
#include "AsgTools/UnitTest.h"
#include "AsgTools/MessageCheck.h"

// Local includes
#include "AsgConfig/ServiceStore.h"

// Googletest
#include "gtest/gtest.h"

// ROOT includes
#include "TError.h"


using SvcPtr_t = std::shared_ptr<asg::IAsgService>;

namespace
{
  /// Simple test service
  class TestService : public asg::IAsgService
  {
    public:
      TestService(const std::string& name) : m_name(name) {}
      virtual const std::string& name() const override final { return m_name; }
    private:
      std::string m_name;
  };

  /// A different simple test service
  class TestService2 : public asg::IAsgService
  {
    public:
      TestService2(const std::string& name) : m_name(name) {}
      virtual const std::string& name() const override final { return m_name; }
    private:
      std::string m_name;
  };

  /// Simple helper class to suppress ROOT error messages
  struct QuietRoot
  {
    QuietRoot() : oldLvl(gErrorIgnoreLevel) { gErrorIgnoreLevel = kFatal; }
    ~QuietRoot() { gErrorIgnoreLevel = oldLvl; }
    const Int_t oldLvl;
  };
}

namespace asg
{

  TEST(ServiceStoreTest, NotFound)
  {
    auto svc = ServiceStore::get("test");
    EXPECT_FALSE( svc );
  }

  TEST(ServiceStoreTest, PutNull)
  {
    SvcPtr_t nullSvc(nullptr);
    QuietRoot q;
    EXPECT_FAILURE( ServiceStore::put(nullSvc) );
  }

  TEST(ServiceStoreTest, EmptyName)
  {
    auto badSvc = std::make_shared<TestService>("");
    QuietRoot q;
    EXPECT_FAILURE( ServiceStore::put(badSvc) );
  }

  TEST(ServiceStoreTest, DuplicatePut)
  {
    auto svc1 = std::make_shared<TestService>("TestService");
    auto svc2 = std::make_shared<TestService>("TestService");
    EXPECT_SUCCESS( ServiceStore::put(svc1) );
    QuietRoot q;
    EXPECT_FAILURE( ServiceStore::put(svc2) );
  }

  TEST(ServiceStoreTest, PutGet)
  {
    auto svc = std::make_shared<TestService>("TestService");
    EXPECT_SUCCESS( ServiceStore::put(svc) );
    EXPECT_TRUE( ServiceStore::get("TestService") );
    EXPECT_TRUE( ServiceStore::get<TestService>("TestService") );
  }

  TEST(ServiceStoreTest, FailCast)
  {
    auto svc = std::make_shared<TestService>("TestService");
    EXPECT_SUCCESS( ServiceStore::put(svc) );
    EXPECT_FALSE( ServiceStore::get<TestService2>("TestService") );
  }

}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}

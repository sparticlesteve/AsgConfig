// STL includes
#include <map>

// ROOT includes
#include "TError.h"

// Local includes
#include "AsgConfig/ServiceStore.h"


// Use an anonymous namespace for the map
namespace
{
  /// The storage map type
  using SvcMap_t = std::map< std::string, std::weak_ptr<asg::IAsgService> >;
  /// Static storage map
  static SvcMap_t svcMap;
}

namespace asg
{

  //---------------------------------------------------------------------------
  // Put a service in the store
  //---------------------------------------------------------------------------
  StatusCode ServiceStore::put(const std::shared_ptr<IAsgService>& svc)
  {
    // Catch null ptrs
    if(!svc) {
      ::Error("ServiceStore", "Trying to put null pointer!");
      return StatusCode::FAILURE;
    }
    // Catch empty names
    const auto& name = svc->name();
    if(name.empty()) {
      ::Error("ServiceStore", "Trying to put service with empty name!");
      return StatusCode::FAILURE;
    }
    // Catch duplicates. Allow to replace expired duplicates.
    auto itr = svcMap.find(name);
    if(itr != svcMap.end() && !itr->second.expired()) {
      ::Error("ServiceStore", "Trying to add duplicate svc with name %s", name.c_str());
      return StatusCode::FAILURE;
    }
    // Ok, now we can add it
    svcMap[name] = svc;

    return StatusCode::SUCCESS;
  }

  //---------------------------------------------------------------------------
  // Get a service from the store
  //---------------------------------------------------------------------------
  std::shared_ptr<IAsgService> ServiceStore::get(const std::string& name)
  {
    auto itr = svcMap.find(name);
    if(itr != svcMap.end()) {
      return itr->second.lock();
    }
    return std::shared_ptr<IAsgService>(nullptr);
  }

}

#include <cassert>
#include <utility>
#include "CxxUtils/make_unique.h"
#include "AsgConfig/Property.h"

using CxxUtils::make_unique;
using std::unique_ptr;
using ana::PropertyList;

int main()
{
  // Test some values
  ana::BoolProperty boolProp("BoolProp", true);
  assert(boolProp.value() == true);

  ana::IntProperty intProp("IntProp", 3);
  assert(intProp.value() == 3);

  ana::FloatProperty floatProp("FloatProp", 3.14f);
  assert(floatProp.value() == 3.14f);

  ana::StringProperty stringProp("StringProp", "Pi");
  assert(stringProp.value() == "Pi");

  // Test PropertyList and clone the properties
  auto propList = make_unique<PropertyList>();
  propList->updateProperty(boolProp.clone());
  propList->updateProperty(intProp.clone());
  propList->updateProperty(floatProp.clone());
  propList->updateProperty(stringProp.clone());

  // Try moving the list
  unique_ptr<PropertyList> propList2( std::move(propList) );

  // Find a property from the list
  auto prop = propList2->find("StringProp");
  assert(prop);

  // Test property data
  auto cloneStringProp = dynamic_cast<const ana::StringProperty*>(prop);
  assert(cloneStringProp);
  assert(cloneStringProp->value() == stringProp.value());

  return 0;
}

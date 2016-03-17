#include "AsgConfig/Property.h"

namespace ana
{

  //---------------------------------------------------------------------------
  // Construct a property
  //---------------------------------------------------------------------------
  PropertyVal::PropertyVal(const std::string& name)
    : m_name(name)
  {}

  //---------------------------------------------------------------------------
  // Clone a property
  //---------------------------------------------------------------------------
  //std::unique_ptr<PropertyVal> PropertyVal::clone() const
  //{
  //  auto p = CxxUtils::make_unique<PropertyVal>(*this);
  //  return std::move(p);
  //}

  //---------------------------------------------------------------------------
  // Retrieve the property name
  //---------------------------------------------------------------------------
  const std::string& PropertyVal::name() const
  { return m_name; }
  //const std::type_info& PropertyVal::type() const
  //{ return typeid(void); }

  //---------------------------------------------------------------------------
  // PropertyValList copy constructor
  //---------------------------------------------------------------------------
  PropertyValList::PropertyValList(const PropertyValList& otherList)
  {
    // Deep copy the properties
    m_props.reserve(otherList.m_props.size());
    for(auto otherProp : otherList) {
      m_props.push_back( otherProp->clone().release() );
    }
  }

  //---------------------------------------------------------------------------
  // PropertyValList copy assignment
  //---------------------------------------------------------------------------
  PropertyValList& PropertyValList::operator=(const PropertyValList& otherList)
  {
    // Use the copy constructor and the move assignment
    PropertyValList tempProp(otherList);
    *this = std::move(tempProp);
    return *this;
  }

  //---------------------------------------------------------------------------
  // PropertyValList move assignment
  //---------------------------------------------------------------------------
  PropertyValList& PropertyValList::operator=(PropertyValList&& otherList)
  {
    if(this != &otherList){
      clear();
      m_props = std::move( otherList.m_props );
    }
    return *this;
  }

  //---------------------------------------------------------------------------
  // List iterations
  //---------------------------------------------------------------------------
  PropertyValList::iterator PropertyValList::begin()
  { return m_props.begin(); }
  PropertyValList::iterator PropertyValList::end()
  { return m_props.end(); }
  PropertyValList::const_iterator PropertyValList::begin() const
  { return m_props.begin(); }
  PropertyValList::const_iterator PropertyValList::end() const
  { return m_props.end(); }

  //---------------------------------------------------------------------------
  // Size of the property list
  //---------------------------------------------------------------------------
  std::size_t PropertyValList::size() const
  { return m_props.size(); }

  //---------------------------------------------------------------------------
  // Clear property list
  //---------------------------------------------------------------------------
  void PropertyValList::clear()
  {
    // Clean up my memory manually
    for(auto prop : m_props) delete prop;
    m_props.clear();
  }

  //---------------------------------------------------------------------------
  // Find property in list by name
  //---------------------------------------------------------------------------
  const PropertyVal* PropertyValList::find(const std::string& name) const
  {
    for(auto prop : m_props) {
      if(prop->name() == name) return prop;
    }
    return nullptr;
  }

  //---------------------------------------------------------------------------
  // Update a property in the list
  //---------------------------------------------------------------------------
  void PropertyValList::updateProperty(std::unique_ptr<PropertyVal> prop)
  {
    // Check if the property already exists
    for(auto propItr = m_props.begin(); propItr != m_props.end(); ++propItr) {
      auto oldProp = *propItr;
      if(oldProp->name() == prop->name()) {
        // Replace and delete
        *propItr = prop.release();
        delete oldProp;
        return;
      }
    }
    // Add the new property to the list
    m_props.push_back( prop.release() );
  }

} // namespace ana

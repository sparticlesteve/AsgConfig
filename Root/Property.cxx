#include "AsgConfig/Property.h"

namespace ana
{

  //---------------------------------------------------------------------------
  // Construct a property
  //---------------------------------------------------------------------------
  Property::Property()
    : m_source(SOURCE_UNKNOWN)
  {}
  //---------------------------------------------------------------------------
  Property::Property(const std::string& name, Source source)
    : m_name(name), m_source(source)
  {}

  //---------------------------------------------------------------------------
  // Clone a property
  //---------------------------------------------------------------------------
  std::unique_ptr<Property> Property::clone() const
  {
    auto p = CxxUtils::make_unique<Property>(*this);
    return std::move(p);
  }

  //---------------------------------------------------------------------------
  // Retrieve the property fields: name, value, source
  //---------------------------------------------------------------------------
  const std::string& Property::name() const
  { return m_name; }
  const std::type_info& Property::type() const
  { return typeid(void); }
  const Property::Source& Property::source() const
  { return m_source; }


  //---------------------------------------------------------------------------
  // PropertyList copy constructor
  //---------------------------------------------------------------------------
  PropertyList::PropertyList(const PropertyList& otherList)
  {
    // Deep copy the properties
    m_props.reserve(otherList.m_props.size());
    for(auto otherProp : otherList) {
      m_props.push_back( otherProp->clone().release() );
    }
  }

  //---------------------------------------------------------------------------
  // PropertyList copy assignment
  //---------------------------------------------------------------------------
  PropertyList& PropertyList::operator=(const PropertyList& otherList)
  {
    // Use the copy constructor and the move assignment
    PropertyList tempProp(otherList);
    *this = std::move(tempProp);
    return *this;
  }

  //---------------------------------------------------------------------------
  // PropertyList move assignment
  //---------------------------------------------------------------------------
  PropertyList& PropertyList::operator=(PropertyList&& otherList)
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
  PropertyList::iterator PropertyList::begin()
  { return m_props.begin(); }
  PropertyList::iterator PropertyList::end()
  { return m_props.end(); }
  PropertyList::const_iterator PropertyList::begin() const
  { return m_props.begin(); }
  PropertyList::const_iterator PropertyList::end() const
  { return m_props.end(); }

  //---------------------------------------------------------------------------
  // Clear property list
  //---------------------------------------------------------------------------
  void PropertyList::clear()
  {
    // Clean up my memory manually
    for(auto prop : m_props) delete prop;
    m_props.clear();
  }

  //---------------------------------------------------------------------------
  // Find property in list by name
  //---------------------------------------------------------------------------
  const Property* PropertyList::find(const std::string& name) const
  {
    for(auto prop : m_props) {
      if(prop->name() == name) return prop;
    }
    return nullptr;
  }

  //---------------------------------------------------------------------------
  // Update a property in the list
  //---------------------------------------------------------------------------
  void PropertyList::updateProperty(std::unique_ptr<Property> prop)
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

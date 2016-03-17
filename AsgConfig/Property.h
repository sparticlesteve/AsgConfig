#ifndef ASGCONFIG_PROPERTY_H
#define ASGCONFIG_PROPERTY_H

// STL includes
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

// Infrastructure
#include "AsgTools/StatusCode.h"
#include "AsgTools/PropertyMgr.h"


namespace ana
{

  /// @class PropertyVal
  /// @brief Wraps a property value for storage in a catalog.
  ///
  /// Wraps a configuration option (a property) which can be stored in a
  /// property catalog and applied to tools. In Gaudi, the standard Property
  /// class can own its own value, which allows to use the same class in the
  /// catalog as is used in the tools' property managers. In standalone,
  /// however, the Property class is non-owning, so I introduce this class to
  /// provide the extra missing functionality. This could thus be removed if
  /// the Property class is updated.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class PropertyVal
  {
    public:

      /// Constructor taking a name
      PropertyVal(const std::string& name);
      /// Destructor
      virtual ~PropertyVal() {};

      /// Get property name
      const std::string& name() const;

      /// Polymorphic cloning
      virtual std::unique_ptr<PropertyVal> clone() const = 0;

      /// Get property type
      virtual const std::type_info& type() const = 0;

      /// Assign value to a property manager
      virtual StatusCode applyProperty(PropertyMgr*) const = 0;

      /// Get a Property object to use for assignment.
      /// Something like this could be added and used to assign a property
      /// to a tool, but it requires an interface update to the standalone
      /// PropertyMgr.
      //virtual asg::Property getProperty() const = 0;

    private:

      /// Name of the property
      std::string m_name;

  }; // class PropertyVal


  /// @class PropertyTVal
  /// @brief Templated PropertyVal which actually stores the value.
  ///
  /// There is introduces a dependency on PropertyMgr which could go away with
  /// an update to the PropertyMgr's interface in RootCore.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  template<class T>
  class PropertyTVal : public PropertyVal
  {
    public:
      /// Default constructor
      PropertyTVal();
      /// Template constructor
      PropertyTVal(const std::string& name, const T& val);
      /// Polymorphic cloning
      virtual std::unique_ptr<PropertyVal> clone() const override final;
      /// Retrieve the value
      const T& value() const;
      /// Get the type of the value
      virtual const std::type_info& type() const override final;
      /// Assign property value to a property manager
      virtual StatusCode applyProperty(PropertyMgr*) const override final;

    private:
      T m_val;
  }; // class PropertyTVal


  /// Convenience typedefs
  typedef PropertyTVal<bool> BoolProperty;
  typedef PropertyTVal<int> IntProperty;
  typedef PropertyTVal<float> FloatProperty;
  typedef PropertyTVal<std::string> StringProperty;


  /// @class PropertyValList
  /// @brief A container of owned property values for one client.
  ///
  /// I would really prefer to use unique_ptr here, but there's no
  /// easy way to make that streamable in ROOT.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class PropertyValList
  {

    public:

      /// Default constructor
      PropertyValList() {};
      /// Copy constructor
      PropertyValList(const PropertyValList&);
      /// Move constructor
      PropertyValList(PropertyValList&&) = default;
      /// Destructor
      ~PropertyValList() { clear(); }
      /// Copy assignment
      PropertyValList& operator=(const PropertyValList&);
      /// Move assignment
      PropertyValList& operator=(PropertyValList&&);

      /// Convenience aliases
      using ListType = std::vector<ana::PropertyVal*>;
      using iterator = ListType::iterator;
      using const_iterator = ListType::const_iterator;

      /// Iterator begin method
      iterator begin();
      /// Iterator end method
      iterator end();
      /// Iterator cbegin method
      const_iterator begin() const;
      /// Iterator cend method
      const_iterator end() const;

      /// Size of the property list
      std::size_t size() const;

      /// Clear properties
      void clear();

      /// Find property by name
      const PropertyVal* find(const std::string& name) const;

      /// Update a property in the list.
      /// If it already exists, the old property is replaced.
      /// Maybe this method should just make a copy.
      void updateProperty(std::unique_ptr<PropertyVal> prop);

    private:

      /// The wrapped list of owned properties
      std::vector<ana::PropertyVal*> m_props;

  }; // class PropertyValList

} // namespace ana

#include <AsgConfig/Property.icc>

#endif

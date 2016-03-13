#ifndef QUICK_ANA__PROPERTY_H
#define QUICK_ANA__PROPERTY_H

// STL includes
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

namespace ana
{

  /// @class Property
  /// @brief Tool property representation.
  ///
  /// Represents a configuration option of a tool.
  /// The motivations for having our own custom Property class rather than use
  /// the existing solutions are that we can possibly use this in both Athena
  /// and in RootCore and we can add a flag which represents the source of the
  /// property, e.g. config file or user.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class Property
  {
    public:
      /// Enumerates the possible sources of properties
      enum Source {
        SOURCE_UNKNOWN = -1,
        CONFIG_FILE,
        USER,
        SOURCE_N
      };

      /// Default constructor
      Property();
      /// Constructor taking a name, type, and source
      Property(const std::string& name, Source source=SOURCE_UNKNOWN);
      /// Destructor
      virtual ~Property() {};
      /// Polymorphic cloning
      virtual std::unique_ptr<Property> clone() const;

      /// Get property name
      const std::string& name() const;
      /// Get property type
      virtual const std::type_info& type() const;
      /// Get property source
      const Source& source() const;

    private:
      /// Property fields
      std::string m_name;
      Source m_source;

  }; // class Property


  /// @class PropertyT
  /// @brief Templated property with a value.
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  template<class T>
  class PropertyT : public Property
  {
    public:
      /// Default constructor
      PropertyT();
      /// Template constructor
      PropertyT(const std::string& name, const T& val,
                Source source=SOURCE_UNKNOWN);
      /// Polymorphic cloning
      virtual std::unique_ptr<Property> clone() const override;
      /// Retrieve the value
      const T& value() const;
      /// Get the type of the value
      const std::type_info& type() const override;
    private:
      T m_val;
  }; // class PropertyT


  /// Convenience typedefs
  typedef PropertyT<bool> BoolProperty;
  typedef PropertyT<int> IntProperty;
  typedef PropertyT<float> FloatProperty;
  typedef PropertyT<std::string> StringProperty;


  /// @class PropertyList
  /// @brief A container of owned properties for one client.
  /// I would really prefer to use unique_ptr here, but there's no
  /// easy way to make that streamable in ROOT.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class PropertyList
  {

    public:

      /// Default constructor
      PropertyList() {};
      /// Copy constructor
      PropertyList(const PropertyList&);
      /// Move constructor
      PropertyList(PropertyList&&) = default;
      /// Destructor
      ~PropertyList() { clear(); }
      /// Copy assignment
      PropertyList& operator=(const PropertyList&);
      /// Move assignment
      PropertyList& operator=(PropertyList&&);

      /// Convenience aliases
      using ListType = std::vector<ana::Property*>;
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

      /// Clear properties
      void clear();

      /// Find property by name
      const Property* find(const std::string& name) const;

      /// @brief Update a property in the list.
      /// If it already exists, the old property is replaced.
      /// Maybe this method should just make a copy.
      void updateProperty(std::unique_ptr<Property> prop);

    private:

      /// The wrapped list of owned properties
      std::vector<ana::Property*> m_props;

  }; // class PropertyList

} // namespace ana

#include <AsgConfig/Property.icc>

#endif

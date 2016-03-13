#ifndef QUICK_ANA__PROPERTY_UTIL_H
#define QUICK_ANA__PROPERTY_UTIL_H

/// @file PropertyUtil.h
/// Contains some helper functions for applying properties to tools.
/// This code may get moved to a different place in the future.
///
/// @author Steve Farrell <Steven.Farrell@cern.ch>
///

// Framework includes
#include "AsgTools/StatusCode.h"
#include "AsgTools/MessageCheck.h"

ANA_MSG_HEADER(msgPropUtil)

// Forward declaration of AsgTool
namespace asg
{
  class AsgTool;
}

namespace ana
{

  /// Forward declaration of property class
  class Property;

  /// @brief Apply a Property to an AsgTool.
  /// Internall this will call a template function based on the saved type.
  /// A failure code is returned in the event of a failure in casting or in
  /// assigning the property value to the tool.
  ///
  StatusCode applyProperty(const ana::Property* prop, asg::AsgTool* tool);

} // namespace ana

#endif

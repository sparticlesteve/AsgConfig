#ifndef ASGCONFIG_IASGSERVICE_H
#define ASGCONFIG_IASGSERVICE_H

#include <string>

#include "AsgTools/StatusCode.h"

namespace asg
{

  /// @class IAsgService
  /// @brief Abstract interface for standalone ASG services.
  ///
  /// This interface is for classes that should be shared across the
  /// application outside of Athena. I'm just calling this a "service" for lack
  /// of a better term. I certainly don't want to cause confusion with the
  /// Athena concept of a Service, though there are certainly some parallels.
  ///
  /// I'm currently just kind of guessing at what methods will be needed here.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class IAsgService
  {
    public:
      /// Virtual destructor
      virtual ~IAsgService() {}

      /// Initialize the service
      //virtual StatusCode initialize() = 0;

      /// Return the name of the service
      virtual const std::string& name() const = 0;

  }; // class IAsgService

} // namespace asg

#endif

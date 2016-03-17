#ifndef ASGCONFIG_SERVICESTORE_H
#define ASGCONFIG_SERVICESTORE_H

#include <memory>
#include <string>

#include "AsgConfig/IAsgService.h"
#include "AsgTools/StatusCode.h"

namespace asg
{

  /// @class ServiceStore
  ///
  /// @brief A registry for sharing IAsgServices in a RootCore-based
  /// application.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class ServiceStore
  {

    public:

      /// Store a service from a shared pointer
      static StatusCode put( const std::shared_ptr<IAsgService>& svc );

      /// @brief Retrieve a shared service.
      ///
      /// If the service isn't found in the store, or if the object has expired
      /// due to release by all clients, then the pointer is null.
      static std::shared_ptr<IAsgService> get( const std::string& name );

      /// @brief Retrieve a shared service cast to the requested interface.
      ///
      /// The returned pointer is null if the
      /// - service isn't found in the store
      /// - object has expired and was deleted by client depletion
      /// - object failed cast to requested interface
      template<class T>
      static std::shared_ptr<T> get( const std::string& name )
      {
        return std::dynamic_pointer_cast<T>( get(name) );
      }

  }; // class ServiceStore

} // namespace asg

#endif

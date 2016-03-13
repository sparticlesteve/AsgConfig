#ifndef QUICK_ANA__ASGTOOL_SVC_H
#define QUICK_ANA__ASGTOOL_SVC_H

// Should only be compiled outside of Athena
#ifdef ROOTCORE

// System includes
#include <memory>
#include <string>
#include <unordered_map>

// Framework includes
#include "AsgTools/AsgMessaging.h"
#include "AsgTools/AsgTool.h"

namespace ana
{

  /// @class AsgToolSvc
  /// @brief A service for constructing and configuring AsgTools.
  ///
  /// This design is likely to change.
  ///
  /// @author Steve Farrell <Steven.Farrell@cern.ch>
  ///
  class AsgToolSvc : public asg::AsgMessaging
  {

    public:

      /// Standard constructor
      AsgToolSvc(const std::string& name);

      /// @brief Retrieve a tool by type and name.
      /// This method will check for an already-existing tool and return it.
      /// If the tool doesn't already exist, it will be constructed and
      /// configured according to the contents of the ConfigSvc.
      asg::AsgTool* getTool(const std::string& name, const std::string& type);

    private:

      /// Construct a tool using the ROOT dictionary
      std::unique_ptr<asg::AsgTool> createTool(const std::string& name,
                                               const std::string& type);

      /// Tool storage
      std::unordered_map< std::string, std::unique_ptr<asg::AsgTool> > m_tools;

  }; // class AsgToolSvc

} // namespace ana

#endif // ROOTCORE

#endif

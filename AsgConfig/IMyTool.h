#ifndef ASGCONFIG_IMYTOOL_H
#define ASGCONFIG_IMYTOOL_H

#include "AsgTools/IAsgTool.h"

#include "xAODMuon/Muon.h"

/// Example tool inteface with muon selection
class IMyTool : virtual public asg::IAsgTool
{
    ASG_TOOL_INTERFACE(IMyTool)
  public:
    virtual StatusCode selectMuon(const xAOD::Muon& muon) const = 0;
};

#endif

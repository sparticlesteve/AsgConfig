#ifndef ASGCONFIG_MYTOOL_H
#define ASGCONFIG_MYTOOL_H

#include "AsgTools/AsgTool.h"
#include "AsgConfig/ToolHandle.h"
#include "AsgConfig/IMyTool.h"

// Forward declarations
namespace CP
{
  class IMuonSelectionTool;
}

class MyTool : public virtual IMyTool,
               public asg::AsgTool
{

    ASG_TOOL_CLASS(MyTool, IMyTool)

  public:

    MyTool(const std::string& name);

    /// Initialize tool and retrieve handle
    virtual StatusCode initialize() override final;

    /// Select a muon
    virtual StatusCode selectMuon(const xAOD::Muon& muon) const override final;

  private:

    /// ToolHandle to another tool
    dev::ToolHandle<CP::IMuonSelectionTool> m_muonSelectionTool;

};

#endif

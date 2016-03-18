#ifndef ASGCONFIG_PARENTTOOL_H
#define ASGCONFIG_PARENTTOOL_H

#include "AsgTools/AsgTool.h"
#include "AsgConfig/ToolHandle.h"
#include "AsgConfig/IMyTool.h"


class ParentTool : public virtual IMyTool,
                   public asg::AsgTool
{
  ASG_TOOL_CLASS(ParentTool, IMyTool)
  public:
    ParentTool(const std::string& name);
    virtual StatusCode initialize() override final;
    virtual StatusCode selectMuon(const xAOD::Muon& muon) const override final;
  private:
    /// ToolHandle to another tool
    dev::ToolHandle<IMyTool> m_childTool;
};

#endif

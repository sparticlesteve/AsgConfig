#ifndef ASGCONFIG_CHILDTOOL_H
#define ASGCONFIG_CHILDTOOL_H

#include "AsgTools/AsgTool.h"

#include "AsgConfig/IMyTool.h"

class ChildTool : public virtual IMyTool,
                  public asg::AsgTool
{
  ASG_TOOL_CLASS(ChildTool, IMyTool)
  public:
    ChildTool(const std::string& name);
    virtual StatusCode initialize() override final;
    virtual StatusCode selectMuon(const xAOD::Muon& muon) const override final;
  private:
    /// Muon PT cut
    float m_muPtMin;
    /// Arbitrary string property
    std::string m_stringProp;
    /// Arbitrary bool property
    bool m_boolProp;
};

#endif

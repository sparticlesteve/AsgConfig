#include "AsgConfig/ChildTool.h"

//-----------------------------------------------------------------------------
ChildTool::ChildTool(const std::string& name)
  : asg::AsgTool(name),
    m_muPtMin(10.f),
    m_stringProp(""),
    m_boolProp(false)
{
  declareProperty("MuonPtMin", m_muPtMin);
  declareProperty("StringProp", m_stringProp);
  declareProperty("BoolProp", m_boolProp);
}

//-----------------------------------------------------------------------------
StatusCode ChildTool::initialize()
{
  ATH_MSG_DEBUG("Initializing " << name());
  ATH_MSG_DEBUG("Muon PT min: " << m_muPtMin);
  ATH_MSG_DEBUG("String prop: " << m_stringProp);
  ATH_MSG_DEBUG("Bool prop:   " << m_boolProp);
  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------
StatusCode ChildTool::selectMuon(const xAOD::Muon& muon) const
{
  if(muon.pt() > m_muPtMin) {
    ATH_MSG_DEBUG("Muon above PT threshold: " << muon.pt()*.001);
  }
  return StatusCode::SUCCESS;
}

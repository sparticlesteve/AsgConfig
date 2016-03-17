#include "AsgConfig/MyTool.h"
#include "MuonSelectorTools/IMuonSelectionTool.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
MyTool::MyTool(const std::string& name)
  : asg::AsgTool(name),
    m_muonSelectionTool("CP::MuonSelectionTool/MyCPMuonTool", this)
{
  declareProperty("MuonSelectionTool", m_muonSelectionTool);
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
StatusCode MyTool::initialize()
{
  // Retrieve the CP tool
  ATH_CHECK( m_muonSelectionTool.retrieve() );
  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------
// Select a muon
//-----------------------------------------------------------------------------
StatusCode MyTool::selectMuon(const xAOD::Muon& muon) const
{
  if(m_muonSelectionTool->accept(muon)) {
    ATH_MSG_INFO("Muon was accepted");
  }
  else {
    ATH_MSG_INFO("Muon was rejected");
  }
  return StatusCode::SUCCESS;
}

#include "AsgConfig/ParentTool.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
ParentTool::ParentTool(const std::string& name)
  : asg::AsgTool(name),
    m_childTool("ChildTool", this)
{
  declareProperty("ChildTool", m_childTool);
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
StatusCode ParentTool::initialize()
{
  // Retrieve the child tool
  ATH_CHECK( m_childTool.retrieve() );
  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------
// Select a muon
//-----------------------------------------------------------------------------
StatusCode ParentTool::selectMuon(const xAOD::Muon& muon) const
{
  ATH_CHECK( m_childTool->selectMuon(muon) );
  return StatusCode::SUCCESS;
}

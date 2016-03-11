#include "TestAlgorithm.h"

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
TestAlgorithm::TestAlgorithm( const std::string& name, ISvcLocator* pSvcLocator )
  : AthAlgorithm( name, pSvcLocator )
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
TestAlgorithm::~TestAlgorithm() {}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
StatusCode TestAlgorithm::initialize()
{
  ATH_MSG_INFO ("Initializing " << name() << "...");

  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
StatusCode TestAlgorithm::finalize()
{
  ATH_MSG_INFO ("Finalizing " << name() << "...");

  return StatusCode::SUCCESS;
}

//-----------------------------------------------------------------------------
// Initialize
//-----------------------------------------------------------------------------
StatusCode TestAlgorithm::execute()
{
  ATH_MSG_DEBUG ("Executing " << name() << "...");

  return StatusCode::SUCCESS;
}

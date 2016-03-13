#include "xAODRootAccess/Init.h"
#include "AsgConfig/AsgToolSvc.h"

/// @file ut_tool_svc.cxx
/// Defines a unit test for the AsgToolSvc.
/// We will ask the svc to construct and return a tool.

int main()
{
  // Initialize the xAOD infrastructure for dictionary loading
  if(xAOD::Init("ut_tool_svc").isFailure()) return 1;

  // Construct a tool service
  ana::AsgToolSvc toolSvc("AsgToolSvc");

  // Try to retrieve a tool
  const std::string toolName = "MuonSelectionToolTest";
  const std::string toolType = "CP::MuonSelectionTool";
  auto tool = toolSvc.getTool(toolName, toolType);
  if(!tool) return 1;

  return 0;
}

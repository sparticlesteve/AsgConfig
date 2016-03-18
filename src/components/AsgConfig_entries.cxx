#include "GaudiKernel/DeclareFactoryEntries.h"

#include "../TestAlgorithm.h"
#include "AsgConfig/ParentTool.h"
#include "AsgConfig/ChildTool.h"

DECLARE_ALGORITHM_FACTORY( TestAlgorithm )
DECLARE_TOOL_FACTORY( ParentTool )
DECLARE_TOOL_FACTORY( ChildTool )

DECLARE_FACTORY_ENTRIES( TheAsgConfig ) 
{
  DECLARE_ALGORITHM( TestAlgorithm );
  DECLARE_TOOL( ParentTool );
  DECLARE_TOOL( ChildTool );
}

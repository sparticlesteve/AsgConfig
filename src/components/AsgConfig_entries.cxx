#include "GaudiKernel/DeclareFactoryEntries.h"

#include "../TestAlgorithm.h"

DECLARE_ALGORITHM_FACTORY( TestAlgorithm )

DECLARE_FACTORY_ENTRIES( TheAsgConfig ) 
{
  DECLARE_ALGORITHM( TestAlgorithm );
}

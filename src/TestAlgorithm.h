#ifndef THEASGCONFIG_TESTALGORITHM_H
#define THEASGCONFIG_TESTALGORITHM_H 1

#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/ToolHandle.h"


class TestAlgorithm: public AthAlgorithm
{
 public:
  TestAlgorithm( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~TestAlgorithm();

  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();

 private:

};

#endif //> !THEASGCONFIG_TESTALGORITHM_H

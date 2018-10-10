#ifndef UserCode_L1RpcTriggerAnalysis_AnaMuonDistribution_H
#define UserCode_L1RpcTriggerAnalysis_AnaMuonDistribution_H


class TObjArray;
class MuonObj;
class GenObj;
namespace edm {class ParameterSet;}

class AnaMuonDistribution {
public:
  AnaMuonDistribution (const edm::ParameterSet&);
  void init(TObjArray& histos);
  bool filter(const MuonObj* muon);
  void run(const MuonObj* muon);
  bool filter(const GenObj* muon);
  void run(const GenObj* muon);  

private:
  double ptMin, etaMax, chi2Norm;
  unsigned int  minNumberOfMatchedStations, minNumberTkHits, minNumberRpcHits, minNumberDtCscHits, minNumberRpcDtCscHits;
  bool requireUnique, requireGlobal, requireInner, requireOuter;
  bool requireLoose, requireMedium, requireTight;
  bool requireTkIso, requirePFIso;
};
#endif

#ifndef OmtfTreeAnalysis_gen_H
#define OmtfTreeAnalysis_gen_H

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TObjArray.h"

class AnaEvent;
class AnaEff;
class AnaMuonDistribution;
class AnaDataEmul;
class AnaDiMu;
class AnaMenu;
class AnaSecMuSelector;
class AnaTime;
class AnaSynch;

namespace edm { class Event; class EventSetup; }

class OmtfTreeAnalysis_gen : public edm::EDAnalyzer {
public:
  OmtfTreeAnalysis_gen(const edm::ParameterSet & cfg);
  virtual ~OmtfTreeAnalysis_gen(){}
  virtual void beginJob();
  virtual void beginRun(const edm::Run&,  const edm::EventSetup& es);
  virtual void analyze(const edm::Event&, const edm::EventSetup& es);
  virtual void endJob();

private:
  TObjArray theHistos;
  edm::ParameterSet theConfig;

  AnaEvent            *theAnaEvent;
  AnaMuonDistribution *theAnaMuonDistribution;
  AnaMenu             *theAnaMenu;
  AnaDataEmul         *theAnaDataEmul;
  AnaEff              *theAnaEff;
  AnaSecMuSelector    *theAnaSecMu;
  AnaTime             *theAnaTime;
  AnaSynch            *theAnaSynch;
  AnaDiMu             *theAnaDiMu;


}; 

#endif

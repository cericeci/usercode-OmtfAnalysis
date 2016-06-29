#ifndef MenuInspector_H
#define MenuInspector_H

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Provenance/interface/ParameterSetID.h"

#include <vector>
#include <string>

namespace edm {class ParameterSet; class Event; class EventSetup; class Run; }

class MenuInspector :  public edm::EDFilter {
public:
  explicit MenuInspector(const edm::ParameterSet&, edm::ConsumesCollector&& cColl);
  virtual ~MenuInspector();

  const std::vector<std::string> & namesAlgoHLT() const { return theNamesAlgoHLT; }
  const std::vector<std::string> & namesAlgoL1() const { return theNamesAlgoL1; }
  std::vector<unsigned int> firedAlgosHLT(const edm::Event&, const edm::EventSetup&) ;
  std::vector<unsigned int> firedAlgosL1(const edm::Event&, const edm::EventSetup&) ;

  virtual bool checkRun(const edm::Run&, const edm::EventSetup &es);

private:
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual bool beginRun(edm::Run& r, const edm::EventSetup & es) { return checkRun(r,es); }
  virtual bool filterL1(edm::Event&, const edm::EventSetup&);
  virtual bool filterHLT(edm::Event&, const edm::EventSetup&);

  unsigned int theCounterIN, theCounterL1, theCounterHLT;

  HLTConfigProvider theHltConfig;
  edm::ParameterSetID theTriggerParSetID;
  bool theWarnNoColl;

  std::vector<std::string> theNamesAlgoHLT, theNamesAlgoL1;

};
#endif


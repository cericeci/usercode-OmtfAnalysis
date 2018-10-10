#include "UserCode/OmtfAnalysis/interface/AnaTime.h"

#include "TObjArray.h"
#include "TH1D.h"
#include "TH2D.h"
#include "UserCode/OmtfDataFormats/interface/TrackObj.h"
#include "UserCode/OmtfDataFormats/interface/MuonObj.h"
#include "UserCode/OmtfDataFormats/interface/MuonObjColl.h"
#include "UserCode/OmtfDataFormats/interface/GenObj.h"
#include "UserCode/OmtfDataFormats/interface/GenObjColl.h"
#include "UserCode/OmtfDataFormats/interface/EventObj.h"
#include "UserCode/OmtfDataFormats/interface/L1ObjColl.h"
#include "UserCode/OmtfAnalysis/interface/Utilities.h"
#include "DataFormats/Math/interface/deltaR.h"


#include <ostream>
#include <iostream>
#include <cmath>

namespace { 
  TH1D *hTimeOmtfAll, *hTimeBmtfAll, *hTimeEmtfAll;  
  TH1D *hTimeOmtfQ, *hTimeBmtfQ, *hTimeEmtfQ;  
  TH1D *hTimeOmtf, *hTimeBmtf, *hTimeEmtf;  
  TH1D *hTimeOmtfAll_E, *hTimeOmtfQ_E, *hTimeOmtf_E;

  TH2D *hTimeBmtfOmtf, *hTimeOmtfEmtf, *hTimeOmtfOmtf_E;

  TH2D *hTimeOmtfTrackDPhiT, *hTimeOmtfTrackDPhiM, *hTimeOmtfTrackDEtaT, *hTimeOmtfTrackDEtaM;
  TH1D *hTimeOmtfTrackDRM;

  TH2D *hTimeOmtfTrackBXT, *hTimeOmtfTrackBXM;
  TH1D *hTimeOmtfTrackBX0, *hTimeOmtfTrackBX1;
  TH2D *hTimeOmtfDrTrackMuon;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

}

AnaTime::AnaTime(const edm::ParameterSet& cfg)
  : debug(false), theCfg (cfg)
{}

void AnaTime::init(TObjArray& histos)
{
  hTimeBmtf = new TH1D("hTimeBmtf","hTimeBmtf",5,-2.5,2.5); histos.Add(hTimeBmtf); 
  hTimeOmtf = new TH1D("hTimeOmtf","hTimeOmtf",5,-2.5,2.5); histos.Add(hTimeOmtf); 
  hTimeEmtf = new TH1D("hTimeEmtf","hTimeEmtf",5,-2.5,2.5); histos.Add(hTimeEmtf); 

  hTimeBmtfQ = new TH1D("hTimeBmtfQ","hTimeBmtfQ",5,-2.5,2.5); histos.Add(hTimeBmtfQ); 
  hTimeOmtfQ = new TH1D("hTimeOmtfQ","hTimeOmtfQ",5,-2.5,2.5); histos.Add(hTimeOmtfQ); 
  hTimeEmtfQ = new TH1D("hTimeEmtfQ","hTimeEmtfQ",5,-2.5,2.5); histos.Add(hTimeEmtfQ); 

  hTimeBmtfAll = new TH1D("hTimeBmtfAll","hTimeBmtfAll",5,-2.5,2.5); histos.Add(hTimeBmtfAll); 
  hTimeOmtfAll = new TH1D("hTimeOmtfAll","hTimeOmtfAll",5,-2.5,2.5); histos.Add(hTimeOmtfAll); 
  hTimeEmtfAll = new TH1D("hTimeEmtfAll","hTimeEmtfAll",5,-2.5,2.5); histos.Add(hTimeEmtfAll); 

  hTimeOmtf_E = new TH1D("hTimeOmtf_E","hTimeOmtf_E",5,-2.5,2.5); histos.Add(hTimeOmtf_E); 
  hTimeOmtfQ_E = new TH1D("hTimeOmtfQ_E","hTimeOmtfQ_E",5,-2.5,2.5); histos.Add(hTimeOmtfQ_E); 
  hTimeOmtfAll_E = new TH1D("hTimeOmtfAll_E","hTimeOmtfAll_E",5,-2.5,2.5); histos.Add(hTimeOmtfAll_E); 

  hTimeBmtfOmtf = new TH2D("hTimeBmtfOmtf","hTimeBmtfOmtf",5,-2.5,2.5, 5,-2.5,2.5); histos.Add(hTimeBmtfOmtf);
  hTimeOmtfEmtf = new TH2D("hTimeOmtfEmtf","hTimeOmtfEmtf",5,-2.5,2.5, 5,-2.5,2.5); histos.Add(hTimeOmtfEmtf);
  hTimeOmtfOmtf_E= new TH2D("hTimeOmtfOmtf_E","hTimeOmtfOmtf_E",5,-2.5,2.5, 5,-2.5,2.5); histos.Add(hTimeOmtfOmtf_E);

  hTimeOmtfTrackDPhiT = new TH2D("hTimeOmtfTrackDPhiT","hTimeOmtfTrackDPhiT",50,0.,25., 50, -1.,1.); histos.Add(hTimeOmtfTrackDPhiT);
  hTimeOmtfTrackDPhiM = new TH2D("hTimeOmtfTrackDPhiM","hTimeOmtfTrackDPhiM",50,0.,25., 50, -1.,1.); histos.Add(hTimeOmtfTrackDPhiM);
  hTimeOmtfTrackDEtaT = new TH2D("hTimeOmtfTrackDEtaT","hTimeOmtfTrackDEtaT",50,0.,25., 50, -1.,1.); histos.Add(hTimeOmtfTrackDEtaT);
  hTimeOmtfTrackDEtaM = new TH2D("hTimeOmtfTrackDEtaM","hTimeOmtfTrackDEtaM",50,0.,25., 50, -1.,1.); histos.Add(hTimeOmtfTrackDEtaM);
//  hTimeOmtfTrackDRM   = new TH2D("hTimeOmtfTrackDRM",  "hTimeOmtfTrackDRM",  50,0.,25., 50, -1.,1.); histos.Add(hTimeOmtfTrackDRM);
  hTimeOmtfTrackDRM   = new TH1D("hTimeOmtfTrackDRM",  "hTimeOmtfTrackDRM",  50, 0.,2.); histos.Add(hTimeOmtfTrackDRM);
  hTimeOmtfTrackBXT = new TH2D("hTimeOmtfTrackBXT", "hTimeOmtfTrackBXT", 50,0.,25.,4, -1.,3.); histos.Add(hTimeOmtfTrackBXT);
  hTimeOmtfTrackBXM = new TH2D("hTimeOmtfTrackBXM", "hTimeOmtfTrackBXM", 50,0.,25.,4, -1.,3.); histos.Add(hTimeOmtfTrackBXM);
  hTimeOmtfTrackBX0 = new TH1D("hTimeOmtfTrackBX0", "hTimeOmtfTrackBX0", 50,0.,25.); histos.Add(hTimeOmtfTrackBX0);
  hTimeOmtfTrackBX1 = new TH1D("hTimeOmtfTrackBX1", "hTimeOmtfTrackBX1", 50,0.,25.); histos.Add(hTimeOmtfTrackBX1);
  hTimeOmtfDrTrackMuon = new TH2D("hTimeOmtfDrTrackMuon","hTimeOmtfDrTrackMuon",50,0.,25.,50, -1.,1.); histos.Add(hTimeOmtfDrTrackMuon);
}

void AnaTime::run(const EventObj* ev, const MuonObjColl *muonColl, const TrackObj* track, const L1ObjColl * l1Objs)
{
  std::vector<L1Obj::TYPE> mtfs= {L1Obj::BMTF, L1Obj::OMTF, L1Obj::EMTF, L1Obj::OMTF_emu};
  //
  // all triggers
  //
  const std::vector<L1Obj> & l1mtfs = *l1Objs;
  const std::vector<MuonObj> & muons = *muonColl;
  for (const auto & l1mtf : l1mtfs) {
    bool matched = false;
    for (const auto & muon : muons) { 
      if (!muon.isValid()) continue;
      double deltaR = reco::deltaR( l1mtf.etaValue(), l1mtf.phiValue(), muon.l1Eta, muon.l1Phi);
      if (deltaR < 0.4) matched=true;
    }
    bool qualOK = (l1mtf.q >= 12);
    TH1D *h,*hQ,*hAll; 
    h=hQ=hAll=0; 
    switch (l1mtf.type) {
        case (L1Obj::BMTF) : h=hTimeBmtf; hQ=hTimeBmtfQ; hAll=hTimeBmtfAll; break;
        case (L1Obj::OMTF) : h=hTimeOmtf; hQ=hTimeOmtfQ; hAll=hTimeOmtfAll; break;
        case (L1Obj::EMTF) : h=hTimeEmtf; hQ=hTimeEmtfQ; hAll=hTimeEmtfAll; break;
        case (L1Obj::OMTF_emu) : h=hTimeOmtf_E; hQ=hTimeOmtfQ_E; hAll=hTimeOmtfAll_E; break;
        default: ;
    }
    if (hAll) hAll->Fill(l1mtf.bx); 
    if (hQ && qualOK) hQ->Fill(l1mtf.bx); 
    if (h && qualOK && matched) h->Fill(l1mtf.bx);  
    //if (h && matched) h->Fill(l1mtf.bx);  
    }

  // coincidence between triggers.
  //
  for (const auto & l1mtf_1 : l1mtfs) {
    for (const auto & l1mtf_2 : l1mtfs) {
      double deltaEta = l1mtf_1.etaValue()-l1mtf_2.etaValue();
      double deltaPhi = reco::deltaPhi( l1mtf_1.phiValue(),  l1mtf_2.phiValue());

      if ( (fabs(deltaEta) > 0.2) || (fabs(deltaPhi >0.05)) ) continue;
      if (l1mtf_1.type==L1Obj::BMTF && l1mtf_2.type ==  L1Obj::OMTF) {
         hTimeBmtfOmtf->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
      if (l1mtf_1.type==L1Obj::OMTF && l1mtf_2.type ==  L1Obj::EMTF) {
         hTimeOmtfEmtf->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
      if (l1mtf_1.type==L1Obj::OMTF && l1mtf_2.type ==  L1Obj::OMTF_emu) {
         hTimeOmtfOmtf_E->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
    }
  }
}

void AnaTime::run(const EventObj* ev, const GenObjColl *genColl, const TrackObj* track, const L1ObjColl * l1Objs)
{
  std::vector<L1Obj::TYPE> mtfs= {L1Obj::BMTF, L1Obj::OMTF, L1Obj::EMTF, L1Obj::OMTF_emu};
  //
  // all triggers
  //
  const std::vector<L1Obj> & l1mtfs = *l1Objs;
  const std::vector<GenObj> & muons = *genColl;
  for (const auto & l1mtf : l1mtfs) {
    bool matched = false;
    for (const auto & muon : muons) { 
      if (!muon.isValid()) continue;
      double deltaR = reco::deltaR( l1mtf.etaValue(), l1mtf.phiValue(), muon.eta, muon.phi);
      if (deltaR < 0.4) matched=true;
    }
    bool qualOK = (l1mtf.q >= 12);
    TH1D *h,*hQ,*hAll; 
    h=hQ=hAll=0; 
    switch (l1mtf.type) {
        case (L1Obj::BMTF) : h=hTimeBmtf; hQ=hTimeBmtfQ; hAll=hTimeBmtfAll; break;
        case (L1Obj::OMTF) : h=hTimeOmtf; hQ=hTimeOmtfQ; hAll=hTimeOmtfAll; break;
        case (L1Obj::EMTF) : h=hTimeEmtf; hQ=hTimeEmtfQ; hAll=hTimeEmtfAll; break;
        case (L1Obj::OMTF_emu) : h=hTimeOmtf_E; hQ=hTimeOmtfQ_E; hAll=hTimeOmtfAll_E; break;
        default: ;
    }
    if (hAll) hAll->Fill(l1mtf.bx); 
    if (hQ && qualOK) hQ->Fill(l1mtf.bx); 
    if (h && qualOK && matched) h->Fill(l1mtf.bx);  
    //if (h && matched) h->Fill(l1mtf.bx);  
    }

  // coincidence between triggers.
  //
  for (const auto & l1mtf_1 : l1mtfs) {
    for (const auto & l1mtf_2 : l1mtfs) {
      double deltaEta = l1mtf_1.etaValue()-l1mtf_2.etaValue();
      double deltaPhi = reco::deltaPhi( l1mtf_1.phiValue(),  l1mtf_2.phiValue());

      if ( (fabs(deltaEta) > 0.2) || (fabs(deltaPhi >0.05)) ) continue;
      if (l1mtf_1.type==L1Obj::BMTF && l1mtf_2.type ==  L1Obj::OMTF) {
         hTimeBmtfOmtf->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
      if (l1mtf_1.type==L1Obj::OMTF && l1mtf_2.type ==  L1Obj::EMTF) {
         hTimeOmtfEmtf->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
      if (l1mtf_1.type==L1Obj::OMTF && l1mtf_2.type ==  L1Obj::OMTF_emu) {
         hTimeOmtfOmtf_E->Fill(l1mtf_1.bx,l1mtf_2.bx);
      }
    }
  }
}

#include "UserCode/OmtfAnalysis/interface/AnaEff.h"
#include "TProfile.h"
#include "TObjArray.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"

#include "UserCode/OmtfDataFormats/interface/EventObj.h"
#include "UserCode/OmtfDataFormats/interface/MuonObj.h"
#include "UserCode/OmtfDataFormats/interface/L1Obj.h"
#include "UserCode/OmtfDataFormats/interface/L1ObjColl.h"
#include "UserCode/OmtfAnalysis/interface/Utilities.h"
#include "DataFormats/Math/interface/deltaR.h"

#include <cmath>
#include <vector>
#include <sstream>

namespace {
  TH1D  *hEffEtaOMTFn, *hEffEtaOMTFn_D, *hEffEtaOMTFp, *hEffEtaOMTFp_D;
  TH1D  *hEffEtaAll, *hEffEtaAll_D;
}


/*
const double AnaEff::ptCuts[ AnaEff::nPtCuts] ={0., 0.1, 
						1.5, 2., 2.5, 3., 3.5, 4., 4.5, 5., 6., 7., 8., 
						10., 12., 14., 16., 18., 20., 25., 30., 35., 40., 45., 
						50., 60., 70., 80., 90., 100.};


std::string reg[5]={"_Bar","_Int","_End","_Qeq0","_Qgt0"};
*/

void AnaEff::resume(TObjArray& histos)
{
  TGraphErrors * hGraphRun = new TGraphErrors();
  hGraphRun->SetName("hGraphEffRun");
  histos.Add(hGraphRun);
  std::vector<unsigned int> runs = theRunMap.runs();
  hGraphRun->Set(runs.size());
  for (unsigned int iPoint = 0; iPoint < runs.size(); iPoint++) {
    unsigned int run = runs[iPoint];
    hGraphRun->SetPoint(iPoint, run, theRunMap.eff(run));
    hGraphRun->SetPointError(iPoint, 0., theRunMap.effErr(run));
  }
   
/*
  for( auto const & run : theRunMap) {
    double eff=0.;
    double effErr=0.;
    unsigned int nEventsN = run.second.second; 
    unsigned int nEventsD = run.second.first;
    if (nEventsD !=0 ) {
      eff = static_cast<double>(nEventsN) / nEventsD;
      effErr = sqrt( static_cast<double>(nEventsN)) / nEventsD;
    }
    std::cout <<" RUN: "<<run.first <<" eff: "<< eff<<" +/- "<<effErr<<std::endl;
    hGraphRun->SetPoint(iPoint, run.first , eff);
    hGraphRun->SetPointError(iPoint, 0., effErr);
    iPoint++;
  }
*/
}


void AnaEff::init(TObjArray& histos)
{
  int nBins = 60;
  double omin = 0.75;
  double omax = 1.35;
  hEffEtaOMTFn   = new TH1D("hEffEtaOMTFn",  "hEffEtaOMTFn",   nBins, -omax, -omin); histos.Add(hEffEtaOMTFn);
  hEffEtaOMTFn_D = new TH1D("hEffEtaOMTFn_D","hEffEtaOMTFn_D", nBins, -omax, -omin); histos.Add(hEffEtaOMTFn_D);
  hEffEtaOMTFp   = new TH1D("hEffEtaOMTFp",  "hEffEtaOMTFp",   nBins,  omin, omax); histos.Add(hEffEtaOMTFp);
  hEffEtaOMTFp_D = new TH1D("hEffEtaOMTFp_D","hEffEtaOMTFp_D", nBins,  omin, omax); histos.Add(hEffEtaOMTFp_D);

  hEffEtaAll     =  new TH1D("hEffEtaAll",    "hEffEtaAll",   96,   -2.4, 2.4); histos.Add(hEffEtaAll); 
  hEffEtaAll_D   =  new TH1D("hEffEtaAll_D",  "hEffEtaAll_D", 96,   -2.4, 2.4); histos.Add(hEffEtaAll_D); 

/*
  hEfficMuPt_D = new TH1D("hEfficMuPt_D","hEfficMuPt_D", L1PtScale::nPtBins, L1PtScale::ptBins); histos.Add(hEfficMuPt_D);
  hEfficRpcNoCut_N = new TH1D("hEfficRpcNoCut_N","hEfficRpcNoCut_N", L1PtScale::nPtBins, L1PtScale::ptBins);  histos.Add(hEfficRpcNoCut_N);
  hEfficRpcPtCut_N = new TH1D("hEfficRpcPtCut_N","hEfficRpcPtCut_N", L1PtScale::nPtBins, L1PtScale::ptBins);  histos.Add(hEfficRpcPtCut_N);

  std::string  base("hEff");
  std::string opt[4]={"_RpcPtCut","_OthPtCut","_GmtPtCut","_OtfPtCut"};
  for (unsigned int ir=0; ir<5; ++ir) {
    std::string name=base+"_PtDenom"+reg[ir];
    TH1D *h= new TH1D(name.c_str(),name.c_str(), L1PtScale::nPtBins, L1PtScale::ptBins);
    histos.Add(h); hm[name]=h;
    for (unsigned int iopt=0; iopt<4; ++iopt) {
    if (iopt >0 && ir >2) continue;
    for (unsigned int icut=0; icut<AnaEff::nPtCuts; ++icut) {
      std::stringstream str;
      str << base << opt[iopt] << ptCuts[icut]<<reg[ir];
      TH1D *h= new TH1D(str.str().c_str(),str.str().c_str(), L1PtScale::nPtBins, L1PtScale::ptBins);
      h->SetXTitle("muon p_{T} [GeV/c]  "); h->SetYTitle("events");
      histos.Add(h); hm[str.str()]=h;
    }
    }
  }
  for (unsigned int icut=0; icut<AnaEff::nPtCuts; ++icut) {
      std::stringstream strEtaDenom; strEtaDenom << base << "_EtaDenom"<< ptCuts[icut];
      TH1D *hD = new TH1D(strEtaDenom.str().c_str(),strEtaDenom.str().c_str(), L1RpcEtaScale::nEtaBins, L1RpcEtaScale::etaBins);
      hD->SetXTitle("muon pseudorapidity"); hD->SetYTitle("events"); histos.Add(hD); hm[strEtaDenom.str()]=hD;
      std::stringstream strEtaCut  ; strEtaCut << base << "_EtaCut"<< ptCuts[icut];
      TH1D *hN = new TH1D(strEtaCut.str().c_str(),strEtaCut.str().c_str(), L1RpcEtaScale::nEtaBins, L1RpcEtaScale::etaBins);
      hN->SetXTitle("muon pseudorapidity"); hN->SetYTitle("events"); histos.Add(hN); hm[strEtaCut.str()]=hN;
  }

*/
}

/*
double AnaEff::maxPt(const std::vector<L1Obj> & l1Objs) const
{
  double result = -1.;
  for (unsigned int i=0; i<l1Objs.size(); i++) if (l1Objs[i].pt > result) result = l1Objs[i].pt;
  return result; 
}
*/

void AnaEff::run(  const EventObj* event, const MuonObj* muon, const L1ObjColl *l1Coll)
{
  if (!muon) return;
  double etaMu = muon->eta();
  double ptMu  = muon->pt();  
//  if (!muon->isGlobal()) return;

//  std::cout <<" MUON: " << *muon << std::endl;
  TH1D* h_N = (etaMu > 0 ) ? hEffEtaOMTFp : hEffEtaOMTFn; 
  TH1D* h_D = (etaMu > 0 ) ? hEffEtaOMTFp_D : hEffEtaOMTFn_D; 

  std::vector<L1Obj> l1Omtfs = l1Coll->selectByType(L1Obj::OMTF);
  bool fired = false;
  for (auto l1Omtf : l1Omtfs) {
    double deltaR = reco::deltaR( l1Omtf.etaValue(),l1Omtf.phiValue(), muon->eta(),muon->phi() );
    std::cout << "deltaR: " << deltaR << std::endl;
    if (deltaR < 0.5) fired = true;
  }
  if (ptMu > 7.) {
    h_D->Fill(etaMu);
    if (fired) h_N->Fill(etaMu);
  }

/* 
  if (ptMu > 7.) {
    hEffEtaAll_D->Fill(etaMu);
    if (firedAll) hEffEtaAll->Fill(etaMu);
  }

  std::vector<L1Obj> l1oths = (l1Coll->selectByType(L1Obj::BMTF)+l1Coll->selectByType(L1Obj::EMTF));
  bool firedOther = false;
  for (auto l1oth : l1oths)
    double deltaR = reco::deltaR( reco::deltaR(l1oth.etaValue(),l1oth.phiValue(),muon->eta(),muon.phi() );
    if (deltaR < 0.5) firedOther = true;
  }
*/


  //
  // OMTF efficiency history 
  //
  if ( ptMu > 7. && fabs(etaMu) < 1.15 && fabs(etaMu) > 0.9) theRunMap.addEvent(event->run, fired); 



/*
  static double matchingdR = theConfig.getParameter<double>("maxDR");
  std::vector<L1Obj> l1Rpcs = l1Coll->l1RpcColl().selectByBx().selectByDeltaR( matchingdR);
  std::vector<L1Obj> l1Oths = l1Coll->l1OthColl().selectByBx().selectByDeltaR( matchingdR).selectByEta();
  std::vector<L1Obj> l1Gmts = l1Coll->selectByType(L1Obj::GMT).selectByBx().selectByQuality(4,7).selectByDeltaR( matchingdR).selectByEta();
  std::vector<L1Obj> l1Otfs = l1Coll->selectByType(L1Obj::OTF);

  hEfficMuPt_D->Fill(ptMu); 
  if (maxPt(l1Rpcs) > 0.) hEfficRpcNoCut_N->Fill(ptMu);
  if (maxPt(l1Rpcs) >= 15.999) hEfficRpcPtCut_N->Fill(ptMu);

  unsigned int iregion;
  if (etaMu < 0.83) iregion = 0;
  else if (etaMu < 1.24) iregion = 1;
  else iregion = 2;
//  std::string reg[3]={"_Bar","_Int","_End"};

  hm["hEff_PtDenom"+reg[iregion]]->Fill(ptMu);
  double epsilon=1.e-5;
  for (unsigned int icut=0; icut < AnaEff::nPtCuts; icut++) { 
    double threshold = AnaEff::ptCuts[icut];
    std::stringstream strEtaDenom;  strEtaDenom  << "hEff_EtaDenom"<<  ptCuts[icut];
    if (ptMu >= threshold) hm[strEtaDenom.str()]->Fill(muon->eta()); 
    if (maxPt(l1Rpcs)+epsilon > threshold) {
       std::stringstream strPt;  strPt  << "hEff_RpcPtCut"<<  ptCuts[icut]<<reg[iregion];
       hm[strPt.str()]->Fill(ptMu);
       std::stringstream strEtaCut;  strEtaCut  << "hEff_EtaCut"<<  ptCuts[icut];
       if (ptMu >= threshold) hm[strEtaCut.str()]->Fill(muon->eta()); 
    }
    if (maxPt(l1Oths)+epsilon > threshold) {
       std::stringstream strPt;  strPt  << "hEff_OthPtCut"<<  ptCuts[icut]<<reg[iregion];
       hm[strPt.str()]->Fill(ptMu);
    }
    if (maxPt(l1Gmts)+epsilon > threshold) {
       std::stringstream strPt;  strPt  << "hEff_GmtPtCut"<<  ptCuts[icut]<<reg[iregion];
       hm[strPt.str()]->Fill(ptMu);
    }
    if (maxPt(l1Otfs)+epsilon > threshold) {
       std::stringstream strPt;  strPt  << "hEff_OtfPtCut"<<  ptCuts[icut]<<reg[iregion];
       hm[strPt.str()]->Fill(ptMu);
    }
  }
  

//
// check performance for q=0 and q>0 in 0.7 < |eta| < 1.1
//
  if (etaMu > 0.7 && etaMu < 1.1) {
    for (unsigned int ir=3; ir <=4; ++ir) {
      hm["hEff_PtDenom"+reg[ir]]->Fill(ptMu);
      std::vector<L1Obj> l1RpcsQ;
      L1ObjColl l1RpcCollQ = l1Coll->l1RpcColl().selectByDeltaR( matchingdR).selectByBx();
      if (ir==3) l1RpcsQ = l1RpcCollQ.selectByQuality(0,0).getL1Objs();
      if (ir==4) l1RpcsQ = l1RpcCollQ.selectByQuality(1,7).getL1Objs();
      double epsilon=1.e-5;
      for (unsigned int icut=0; icut < AnaEff::nPtCuts; icut++) {
        double threshold = AnaEff::ptCuts[icut];
        if (maxPt(l1RpcsQ)+epsilon > threshold) {
          std::stringstream strPt;  strPt  << "hEff_RpcPtCut"<<  ptCuts[icut]<<reg[ir];
          hm[strPt.str()]->Fill(ptMu);
        }
      }
    }
  }

*/
}	


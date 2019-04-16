import FWCore.ParameterSet.Config as cms
import commands
import os

#from Configuration.StandardSequences.Eras import eras
#process = cms.Process('OmtfTree',eras.Run2_2016)

process = cms.Process('OmtfTree')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#
# For processing single files insert lines with 'file:/PATH/FILE.root'
# alernatively one can use 'root://xrootd.unl.edu//store/express/Run2015A.....root'
# or                       '/store/express/Run2015A/ExpressPhysics/FEVT/...root'
# (there is 255 file limit though). Can be empty for crab.
#
process.source = cms.Source("PoolSource", 
fileNames = cms.untracked.vstring(
#'file:///afs/cern.ch/work/c/cericeci/private/OMTF_2019/CMSSW_10_1_7/src/UserCode/OmtfAnalysis/test/54C9CCAA-AA3A-E811-BEB7-06480E0002BB.root'
"/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/42461A41-343F-E811-B8AE-0CC47A4DED04.root",
#'/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/202D9635-5B42-E811-8C8B-A0369FD0B1F2.root',
#'/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/6801504C-1942-E811-8E71-A0369FD0B1F2.root',
#'/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/92488BEA-1843-E811-8DF7-A0369FD0B3FA.root',
#'/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/FE54D6E5-0A42-E811-8FD4-48D539F3863E.root',
#'/store/mc/PhaseIIFall17D/SingleMu_FlatPt-2to100/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/00000/9826D881-5B42-E811-8026-A0369FD0B1F2.root'
#'/store/mc/PhaseIIFall17D/SingleNeutrino/GEN-SIM-DIGI-RAW/L1TPU200_93X_upgrade2023_realistic_v5-v1/80000/4EC89858-6B5C-E811-BF31-0025905C95F8.root'
),
inputCommands=cms.untracked.vstring(
        'keep *',
        'drop l1tEMTFHit2016Extras_simEmtfDigis_CSC_HLT',
        'drop l1tEMTFHit2016Extras_simEmtfDigis_RPC_HLT',
        'drop l1tEMTFHit2016s_simEmtfDigis__HLT',
        'drop l1tEMTFTrack2016Extras_simEmtfDigis__HLT',
        'drop l1tEMTFTrack2016s_simEmtfDigis__HLT')
)

#
# import of standard configurations
#
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
#process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.Geometry.GeometryExtended2017Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('EventFilter.L1TRawToDigi.bmtfDigis_cfi')
process.load('EventFilter.L1TRawToDigi.emtfStage2Digis_cfi')
process.load('EventFilter.L1TRawToDigi.gmtStage2Digis_cfi')
process.load('EventFilter.L1TXRawToDigi.twinMuxStage2Digis_cfi')
process.load('EventFilter.L1TRawToDigi.omtfStage2Digis_cfi')
#process.load('EventFilter.L1TRawToDigi.omtfStage2Raw_cfi')
#process.load('EventFilter.L1TRawToDigi.caloLayer1Digis_cfi')
process.load('EventFilter.L1TRawToDigi.caloStage2Digis_cfi')
#process.load("CondTools/RPC/RPCLinkMap_sqlite_cff")


#
# set proper GlobalTag
#
#process.GlobalTag.globaltag = 'FT_R_53_V10::All' #rereco 2012ABC
#process.GlobalTag.globaltag = 'FT_R_53_V18::All' #rereco 2012ABC
#process.GlobalTag.globaltag = 'FT_R_53_V21::All' #rereco 2012D
#process.GlobalTag.globaltag  = 'GR_E_V46::All' #rereco
#process.GlobalTag.globaltag  = 'GR_P_V50::All' #rereco
#process.GlobalTag.globaltag  = 'GR_P_V54::All' #rereco
#process.GlobalTag.globaltag  = 'GR_P_V56::All' #rereco
#process.GlobalTag.globaltag  = '74X_dataRun2_Prompt_v0'
#process.GlobalTag.globaltag  = '74X_dataRun2_Express_v0'
#process.GlobalTag.globaltag  = 'auto:run2_data'
#process.GlobalTag.globaltag  = '80X_dataRun2_Prompt_v8'
from Configuration.AlCa.GlobalTag import GlobalTag
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
#process.GlobalTag.globaltag  = '92X_dataRun2_Prompt_v4'
#process.GlobalTag.globaltag = '100X_dataRun2_v1'
#process.GlobalTag.globaltag = '100X_dataRun2_Express_v3'
#process.GlobalTag.globaltag = '101X_dataRun2_Express_v8'9
#process.GlobalTag.globaltag = '93X_upgrade2023_realistic_v5'
process.GlobalTag.globaltag = '100X_upgrade2023_realistic_Candidate_2018_07_26_10_13_24'
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_mcRun2_asymptotic_v3', 'MuonSystemAging_3000fbm1,MuonSystemAgingRcd,sqlite_file:./MuonSystemAging.db')
#
# message logger
#
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.MessageLogger.cerr.threshold = cms.untracked.string('DEBUG')
#process.MessageLogger.debugModules.append('muonRPCDigis')
#process.MessageLogger.debugModules.append('omtfStage2Digis')
#process.MessageLogger.debugModules.append('omtfStage2Raw')
#process.MessageLogger.debugModules.append('omtfStage2Digis2')
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1)
process.MessageLogger.suppressWarning  = cms.untracked.vstring('Geometry', 'AfterSource','L1T','L1GlobalTriggerRawToDigi')
process.options = cms.untracked.PSet( wantSummary=cms.untracked.bool(False))

##Trigger Primitives
print "Load "
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfigFromDB_cff")

#Age the DTs
from SimMuon.DTDigitizer.dtChamberMasker_cfi import dtChamberMasker as _dtChamberMasker
process.preSimDtTriggerDigis = _dtChamberMasker.clone()

print vars(_dtChamberMasker)

print "SetDT"
process.preSimDtTriggerDigis.digiTag = cms.InputTag("simMuonDTDigis")

#This is needed for the random dropping 
process.RandomNumberGeneratorService = cms.Service(
                "RandomNumberGeneratorService",
  		preSimDtTriggerDigis = cms.PSet(
    		initialSeed = cms.untracked.uint32(431284653),
    		engineName = cms.untracked.string('TRandom3')
  		)
)
print "EMULATOR"
#  - DT TP emulator
from L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi import *
import L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi
process.simDtTriggerPrimitiveDigis = L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi.dtTriggerPrimitiveDigis.clone(
    digiTag = 'preSimDtTriggerDigis'
)
#simDtTriggerPrimitiveDigis.debug = cms.untracked.bool(True)

# - CSC TP emulator
from L1Trigger.CSCCommonTrigger.CSCCommonTrigger_cfi import *
import L1Trigger.CSCTriggerPrimitives.cscTriggerPrimitiveDigis_cfi
process.simCscTriggerPrimitiveDigis = L1Trigger.CSCTriggerPrimitives.cscTriggerPrimitiveDigis_cfi.cscTriggerPrimitiveDigis.clone(
    CSCComparatorDigiProducer = 'simMuonCSCDigis:MuonCSCComparatorDigi',
    CSCWireDigiProducer       = 'simMuonCSCDigis:MuonCSCWireDigi'
)

print "TP Emulator"

process.SimL1TMuonCommon = cms.Sequence(process.preSimDtTriggerDigis+process.simDtTriggerPrimitiveDigis + process.simCscTriggerPrimitiveDigis)

#
###OMTF emulator configuration
#
#OMTF ESProducer. Fills CondFormats from XML files.
process.load('L1Trigger.L1TMuonBayes.fakeOmtfParams_cff')
process.esProd = cms.EDAnalyzer("EventSetupRecordDataGetter",
   toGet = cms.VPSet(
      cms.PSet(record = cms.string('L1TMuonOverlapParamsRcd'),
               data = cms.vstring('L1TMuonOverlapParams'))
                   ),
   verbose = cms.untracked.bool(False)
)

#Now with the new emulator
import L1Trigger.L1TMuonBayes.simOmtfDigis_cfi

process.omtfEmulator=L1Trigger.L1TMuonBayes.simOmtfDigis_cfi.simOmtfDigis.clone() 
process.omtfEmulator.dumpResultToXML = cms.bool(True)
process.omtfEmulator.srcDTPh = cms.InputTag('simDtTriggerPrimitiveDigis')
process.omtfEmulator.srcDTTh = cms.InputTag('simDtTriggerPrimitiveDigis')

#process.bxMin = cms.int32(0) #For the moment let's restrict ourselves to this
#process.bxMax = cms.int32(0)

print "Reemulate GMT"
#
# reemulate GMT, with changed OMTF
#
process.emulGmtCaloSumDigis = cms.EDProducer('L1TMuonCaloSumProducer',
    caloStage2Layer2Label = cms.InputTag("caloStage2Digis",'CaloTower'),
)
process.emulGmtStage2Digis = cms.EDProducer('L1TMuonProducer',
    barrelTFInput  = cms.InputTag("gmtStage2Digis", "BMTF"),
    overlapTFInput = cms.InputTag("omtfEmulator", "OMTF"),
    forwardTFInput = cms.InputTag("gmtStage2Digis", "EMTF"),
    triggerTowerInput = cms.InputTag("emulGmtCaloSumDigis", "TriggerTowerSums"),
    autoBxRange = cms.bool(True), # if True the output BX range is calculated from the inputs and 'bxMin' and 'bxMax' are ignored
    bxMin = cms.int32(-3),
    bxMax = cms.int32(4),
    autoCancelMode = cms.bool(False), # if True the cancel out methods are configured depending on the FW version number and 'emtfCancelMode' is ignored
    emtfCancelMode = cms.string("coordinate"), # 'tracks' or 'coordinate'
    runPhase2 = cms.bool(True)
)
print "Steps"
process.TP_step = cms.Path(process.SimL1TMuonCommon)
process.raw2digi_step = cms.Path(process.muonRPCDigis+process.csctfDigis+process.bmtfDigis+process.emtfStage2Digis+process.twinMuxStage2Digis+process.gmtStage2Digis+process.caloStage2Digis)
process.omtf_step = cms.Path(process.omtfStage2Digis+process.esProd+process.omtfEmulator+process.emulGmtCaloSumDigis+process.emulGmtStage2Digis)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.schedule = cms.Schedule(process.TP_step,process.raw2digi_step, process.omtf_step, process.endjob_step)
print "OMTF Analyzer"
#
# OMTF tree 
#
process.omtfTree = cms.EDAnalyzer("OmtfTreeMaker",
  histoFileName = cms.string("omtfHelper.root"),
  treeFileName = cms.string("omtfTree.root"),

  menuInspector = cms.PSet(
    namesCheckHltMuMatch = cms.vstring(
      "HLT_IsoMu20_v","HLT_IsoMu24_v","HLT_IsoMu27_v"
    ),
  ),

   linkSynchroGrabber = cms.PSet(
     rawSynchroTag = cms.InputTag("muonRPCDigis"),
     writeHistograms = cms.untracked.bool(True),
     deltaR_MuonToDetUnit_cutoff = cms.double(0.3),
     checkInside = cms.bool(True),
     linkMonitorPSet = cms.PSet(
       useFirstHitOnly = cms.untracked.bool(True),
       dumpDelays = cms.untracked.bool(True) # set to True for LB delay plots
     ),
     synchroSelector = cms.PSet(
       checkRpcDetMatching_minPropagationQuality = cms.int32(0),
       checkRpcDetMatching_matchingScaleValue = cms.double(3),
       checkRpcDetMatching_matchingScaleAuto  = cms.bool(True),
       checkUniqueRecHitMatching_maxPull = cms.double(2.),
       checkUniqueRecHitMatching_maxDist = cms.double(5.)
     )
   ),
  
  l1ObjMaker = cms.PSet(
    omtfEmulSrc = cms.InputTag('omtfEmulator','OMTF',"OmtfTree"),
    omtfDataSrc = cms.InputTag('omtfStage2Digis'),
    emtfDataSrc = cms.InputTag('gmtStage2Digis','EMTF'),
    bmtfDataSrc = cms.InputTag('gmtStage2Digis','BMTF'),
    gmtDataSrc = cms.InputTag('gmtStage2Digis','Muon'),
    gmtEmulSrc = cms.InputTag('emulGmtStage2Digis',''),
  ),
  genObjectFinder = cms.PSet(
    genColl = cms.InputTag("genParticles")
  ),                                 
  closestTrackFinder = cms.PSet(
    trackColl = cms.InputTag("generalTracks")
  ),

  onlyBestMuEvents = cms.bool(False),
  bestMuonFinder = cms.PSet(
    muonColl = cms.InputTag("muons"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    requireInnerTrack = cms.bool(False),
    requireOuterTrack = cms.bool(False),
    requireGlobalTrack = cms.bool(False),
    requireLoose       = cms.bool(False),
    minPt = cms.double(3.),
    maxTIP = cms.double(0.2),
    maxAbsEta = cms.double(2.4),
    minNumberTrackerHits = cms.int32(6),
    minNumberRpcHits = cms.int32(0),
    minNumberDtCscHits = cms.int32(0),
    minNumberOfMatchedStations = cms.int32(0),
    cutTkIsoRel = cms.double(0.1),
    cutPFIsoRel = cms.double(0.15),
    deltaPhiUnique = cms.double(1.0),
    deltaEtaUnique = cms.double(0.5),
    minPtUnique = cms.double(2.0),
    looseUnique = cms.bool(True)
  ),
)

#
# refit Muon
#
#process.load("TrackingTools.RecoGeometry.RecoGeometries_cff")
#process.load("TrackingTools.TrackRefitter.TracksToTrajectories_cff")
#process.load("TrackingTools.TrackRefitter.globalMuonTrajectories_cff")
#import TrackingTools.TrackRefitter.globalMuonTrajectories_cff
#process.refittedMuons = TrackingTools.TrackRefitter.globalMuonTrajectories_cff.globalMuons.clone()
#process.refittedMuons*
print "Add all"
process.OmtfTree = cms.Path(process.omtfTree)
process.schedule.append(process.OmtfTree)
print process.schedule


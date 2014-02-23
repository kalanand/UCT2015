import FWCore.ParameterSet.Config as cms

maxEvents  = -1
outputFile = "uct_rate_trees.root"
inputFiles = 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/'

['dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/288CC105-8E08-E211-AF35-001D09F251FE.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/2AEC9704-8E08-E211-BC9B-001D09F24399.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/481B120E-9008-E211-AA5F-001D09F2A690.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/50D31C04-8E08-E211-817C-001D09F23D1D.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/58811A38-8D08-E211-8729-001D09F241B9.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/82EA319F-8F08-E211-BF62-0019B9F581C9.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/9CE9BE09-8E08-E211-B1D9-001D09F242EF.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/B0AF0C05-8E08-E211-A3A3-001D09F27067.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/D69FFB04-8E08-E211-92AC-001D09F24EE3.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/DA1CF39E-8F08-E211-9B6C-001D09F2905B.root'
 'dcache:/pnfs/cms/WAX/11/store/data/Run2012C/ZeroBias3/RAW/v1/000/203/742/F440FA05-8E08-E211-AC3C-0015C5FDE067.root']

process = cms.Process("L1UCTRates")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_H_V28::All'
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_COND_31X_GLOBALTAG'
process.GlobalTag.pfnPrefix = cms.untracked.string('frontier://FrontierProd/')

# UNCOMMENT THIS LINE TO RUN ON SETTINGS FROM THE DATABASE
# process.es_prefer_GlobalTag = cms.ESPrefer('PoolDBESSource', 'GlobalTag')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxEvents)
)

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(inputFiles)
)

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(outputFile)
)

# Load emulation and RECO sequences
process.load("L1Trigger.UCT2015.emulation_cfi")

## ...
## If running on MinBias samples:
## Trigger bit requirement to use only zero bias triggered events
## ...

# Define the tree producers
#
# tau
process.tauL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("l1extraParticles", "Tau")),
    isUCT = cms.bool(False),
)
process.rlxTauUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedTauUnpacked")),
    isUCT = cms.bool(True),
)
process.isoTauUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "IsolatedTauUnpacked")),
    isUCT = cms.bool(True),
)

#
# EG iso
#
process.isoEGL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("l1extraParticles", "Isolated")),
    isUCT = cms.bool(False),
)
process.isoEGUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "IsolatedEGUnpacked")),
    isUCT = cms.bool(True),
)

#
# EG rlx
#
process.rlxEGL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(
        cms.InputTag("l1extraParticles", "NonIsolated"),
        cms.InputTag("l1extraParticles", "Isolated")
    ),
    isUCT = cms.bool(False),
)
process.rlxEGUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "RelaxedEGUnpacked")),
    isUCT = cms.bool(True),
)

#
# Jets
#
process.jetL1Rate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(
        # Combine central and forward
        cms.InputTag("l1extraParticles", "Central"),
        cms.InputTag("l1extraParticles", "Forward"),
    ),
    isUCT = cms.bool(False),
)
process.jetUCTRate = cms.EDAnalyzer(
    "RateTree",
    src = cms.VInputTag(cms.InputTag("UCT2015Producer", "JetUnpacked")),
    isUCT = cms.bool(True),
)

process.p1 = cms.Path(
    process.emulationSequence *
    process.tauL1Rate *
    process.rlxTauUCTRate *
    process.isoTauUCTRate *
    process.isoEGL1Rate *
    process.isoEGUCTRate *
    process.rlxEGL1Rate *
    process.rlxEGUCTRate *
    process.jetL1Rate *
    process.jetUCTRate
)

# Make the framework shut up.
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Spit out filter efficiency at the end.
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

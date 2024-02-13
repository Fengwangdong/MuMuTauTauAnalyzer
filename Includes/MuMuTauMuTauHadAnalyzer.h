//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 14:19:21 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTauTauTreelization.root
//////////////////////////////////////////////////////////

#ifndef MuMuTauMuTauHadAnalyzer_h
#define MuMuTauMuTauHadAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Histomutau.h"

class MuMuTauMuTauHadAnalyzer : public Histomutau {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *recoMuonPt;
   vector<float>   *recoMuonEta;
   vector<float>   *recoMuonPhi;
   vector<float>   *recoMuonEnergy;
   vector<int>     *recoMuonPDGId;
   vector<float>   *recoMuonIsolation;
   vector<float>   *recoMuonDXY;
   vector<float>   *recoMuonDZ;
   vector<int>     *recoMuonNTrackerLayers;
   vector<int>     *recoMuonTriggerFlag;
   vector<int>     *recoMuonRefToElectron;
   vector<int>     *recoMuonRefToTau;
   vector<int>     *recoMuonIdLoose;
   vector<int>     *recoMuonIdMedium;
   vector<int>     *recoMuonIdTight;
   vector<float>   *recoTauMuonCleanedPt;
   vector<float>   *recoTauMuonCleanedEta;
   vector<float>   *recoTauMuonCleanedPhi;
   vector<float>   *recoTauMuonCleanedEnergy;
   vector<int>     *recoTauMuonCleanedPDGId;
   vector<float>   *recoTauMuonCleanedDecayMode;
   vector<float>   *recoTauMuonCleanedDecayModeFinding;
   vector<float>   *recoTauMuonCleanedDecayModeFindingNewDMs;
   vector<int>     *recoTauMuonCleanedRefToMuon;
   vector<int>     *recoTauMuonCleanedRefToElectron;
   vector<float>   *recoTauMuonCleanedDeepVSeraw;
   vector<float>   *recoTauMuonCleanedDeepVSjetraw;
   vector<float>   *recoTauMuonCleanedDeepVSmuraw;
   vector<float>   *recoTauMuonCleanedDeepVSeLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetLoose;
   vector<float>   *recoTauMuonCleanedDeepVSmuLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeMedium;
   vector<float>   *recoTauMuonCleanedDeepVSjetMedium;
   vector<float>   *recoTauMuonCleanedDeepVSmuMedium;
   vector<float>   *recoTauMuonCleanedDeepVSeTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetTight;
   vector<float>   *recoTauMuonCleanedDeepVSmuTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSmuVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeVTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetVTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeVVTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVArawValue;
   vector<float>   *recoTauMuonCleanedIsoMVAVVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVAVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVALoose;
   vector<float>   *recoTauMuonCleanedIsoMVAMedium;
   vector<float>   *recoTauMuonCleanedIsoMVATight;
   vector<float>   *recoTauMuonCleanedIsoMVAVTight;
   vector<float>   *recoTauMuonCleanedIsoMVAVVTight;
   vector<float>   *recoTauMuonCleanedAntiMuMVALoose;
   vector<float>   *recoTauMuonCleanedAntiMuMVATight;
   vector<float>   *recoTauMuonCleanedAntiEleMVArawValue;
   vector<float>   *recoTauMuonCleanedAntiEleMVAVLoose;
   vector<float>   *recoTauMuonCleanedAntiEleMVALoose;
   vector<float>   *recoTauMuonCleanedAntiEleMVAMedium;
   vector<float>   *recoTauMuonCleanedAntiEleMVATight;
   vector<float>   *recoTauMuonCleanedAntiEleMVAVTight;
   vector<float>   *recoJetPt;
   vector<float>   *recoJetEta;
   vector<float>   *recoJetPhi;
   vector<float>   *recoJetEnergy;
   vector<float>   *recoJetCSV;
   vector<float>   *recoMET;
   vector<float>   *recoMETPhi;
   vector<float>   *recoMETPx;
   vector<float>   *recoMETPy;
   Int_t           recoNPrimaryVertex;
   Int_t           eventID;
   vector<float>   *genMuonPt;
   vector<float>   *genMuonEta;
   vector<float>   *genMuonPhi;
   vector<float>   *genMuonMass;
   vector<int>     *genMuonPDGId;
   vector<int>     *genMuonMotherPDGId;
   vector<float>   *genTauMuPt;
   vector<float>   *genTauMuEta;
   vector<float>   *genTauMuPhi;
   vector<float>   *genTauMuMass;
   vector<int>     *genTauMuPDGId;
   vector<int>     *genTauMuMotherPDGId;
   vector<float>   *genTauMuVisPt;
   vector<float>   *genTauMuVisMass;
   vector<float>   *genTauHadPt;
   vector<float>   *genTauHadEta;
   vector<float>   *genTauHadPhi;
   vector<float>   *genTauHadMass;
   vector<int>     *genTauHadPDGId;
   vector<int>     *genTauHadMotherPDGId;
   vector<float>   *genTauHadVisPt;
   vector<float>   *genTauHadVisMass;
   vector<int>     *genTauHadNPionZero;
   vector<int>     *genTauHadNChargedHadrons;
   Int_t           recoNPU;
   Int_t           trueNInteraction;
   Float_t         genEventWeight;

   // List of branches
   TBranch        *b_recoMuonPt;   //!
   TBranch        *b_recoMuonEta;   //!
   TBranch        *b_recoMuonPhi;   //!
   TBranch        *b_recoMuonEnergy;   //!
   TBranch        *b_recoMuonPDGId;   //!
   TBranch        *b_recoMuonIsolation;   //!
   TBranch        *b_recoMuonDXY;   //!
   TBranch        *b_recoMuonDZ;   //!
   TBranch        *b_recoMuonNTrackerLayers;   //!
   TBranch        *b_recoMuonTriggerFlag;   //!
   TBranch        *b_recoMuonRefToElectron;   //!
   TBranch        *b_recoMuonRefToTau;   //!
   TBranch        *b_recoMuonIdLoose;   //!
   TBranch        *b_recoMuonIdMedium;   //!
   TBranch        *b_recoMuonIdTight;   //!
   TBranch        *b_recoTauMuonCleanedPt;   //!
   TBranch        *b_recoTauMuonCleanedEta;   //!
   TBranch        *b_recoTauMuonCleanedPhi;   //!
   TBranch        *b_recoTauMuonCleanedEnergy;   //!
   TBranch        *b_recoTauMuonCleanedPDGId;   //!
   TBranch        *b_recoTauMuonCleanedDecayMode;   //!
   TBranch        *b_recoTauMuonCleanedDecayModeFinding;   //!
   TBranch        *b_recoTauMuonCleanedDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauMuonCleanedRefToMuon;   //!
   TBranch        *b_recoTauMuonCleanedRefToElectron;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVArawValue;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAMedium;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVATight;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVTight;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVVTight;   //!
   TBranch        *b_recoTauMuonCleanedAntiMuMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiMuMVATight;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVArawValue;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAMedium;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVATight;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAVTight;   //!
   TBranch        *b_recoJetPt;   //!
   TBranch        *b_recoJetEta;   //!
   TBranch        *b_recoJetPhi;   //!
   TBranch        *b_recoJetEnergy;   //!
   TBranch        *b_recoJetCSV;   //!
   TBranch        *b_recoMET;   //!
   TBranch        *b_recoMETPhi;   //!
   TBranch        *b_recoMETPx;   //!
   TBranch        *b_recoMETPy;   //!
   TBranch        *b_recoNPrimaryVertex;   //!
   TBranch        *b_eventID;   //!
   TBranch        *b_genMuonPt;   //!
   TBranch        *b_genMuonEta;   //!
   TBranch        *b_genMuonPhi;   //!
   TBranch        *b_genMuonMass;   //!
   TBranch        *b_genMuonPDGId;   //!
   TBranch        *b_genMuonMotherPDGId;   //!
   TBranch        *b_genTauMuPt;   //!
   TBranch        *b_genTauMuEta;   //!
   TBranch        *b_genTauMuPhi;   //!
   TBranch        *b_genTauMuMass;   //!
   TBranch        *b_genTauMuPDGId;   //!
   TBranch        *b_genTauMuMotherPDGId;   //!
   TBranch        *b_genTauMuVisPt;   //!
   TBranch        *b_genTauMuVisMass;   //!
   TBranch        *b_genTauHadPt;   //!
   TBranch        *b_genTauHadEta;   //!
   TBranch        *b_genTauHadPhi;   //!
   TBranch        *b_genTauHadMass;   //!
   TBranch        *b_genTauHadPDGId;   //!
   TBranch        *b_genTauHadMotherPDGId;   //!
   TBranch        *b_genTauHadVisPt;   //!
   TBranch        *b_genTauHadVisMass;   //!
   TBranch        *b_genTauHadNPionZero;   //!
   TBranch        *b_genTauHadNChargedHadrons;   //!
   TBranch        *b_recoNPU;   //!
   TBranch        *b_trueNInteraction;   //!
   TBranch        *b_genEventWeight;   //!

   TString fileName;
   TString outputDir;
   Long_t  nMaxEvents;
   float lumiScale;
   float summedWeights; // these two factors contribute to the MC normalization
   bool isMC;
   bool invertedMu2Iso;
   bool invertedTauIso;
   double Mu1IsoThreshold;
   double Mu2IsoThreshold;
   double MuIsoUpperBound;
   TString MuonId;
   double diMuonMassLowThreshold;
   double diMuonMassHighThreshold;
   bool tauMVAIsoRawORWP;
   double tauMVAIsoRawThreshold;
   TString tauMVAIsoWP;
   TString tauAntiMuDisc;
   TString tauAntiEleDisc;
   bool deepTauID;
   TString deepTauVSele;
   TString deepTauVSmu;
   TString deepTauVSjet;
   double tauDecayModeThreshold;
   int muonScaleSyst;
   double tauScaleCorr;
   TString rochesterFile;
   bool jpsiCont;

   MuMuTauMuTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, bool invertedMu2Iso_ = false, bool invertedTauIso_ = false, double Mu1IsoThreshold_ = 0.25, double Mu2IsoThreshold_ = 0.25, double MuIsoUpperBound_ = 0.4, TString MuonId_ = "LOOSE", double diMuonMassLowThreshold_ = 0, double diMuonMassHighThreshold_ = 25.0, bool tauMVAIsoRawORWP_ = false, double tauMVAIsoRawThreshold_ = -0.5, TString tauMVAIsoWP_ = "MEDIUM", TString tauAntiMuDisc_ = "NULL", TString tauAntiEleDisc_ = "NULL", bool deepTauID_ = false, TString deepTauVSele_ = "LOOSE", TString deepTauVSmu_ = "LOOSE", TString deepTauVSjet_ = "MEDIUM", double tauDecayModeThreshold_ = -1, int muonScaleSyst_ = 0, double tauScaleCorr_ = 1.0, TString rochesterFile_ = "", bool jpsiCont_ = false);
   string createOutputFileName();
   virtual ~MuMuTauMuTauHadAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MuMuTauMuTauHadAnalyzer_cxx
MuMuTauMuTauHadAnalyzer::MuMuTauMuTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, bool invertedMu2Iso_, bool invertedTauIso_, double Mu1IsoThreshold_, double Mu2IsoThreshold_, double MuIsoUpperBound_, TString MuonId_, double diMuonMassLowThreshold_, double diMuonMassHighThreshold_, bool tauMVAIsoRawORWP_, double tauMVAIsoRawThreshold_, TString tauMVAIsoWP_, TString tauAntiMuDisc_, TString tauAntiEleDisc_, bool deepTauID_, TString deepTauVSele_, TString deepTauVSmu_, TString deepTauVSjet_, double tauDecayModeThreshold_, int muonScaleSyst_, double tauScaleCorr_, TString rochesterFile_, bool jpsiCont_) : Histomutau() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    invertedMu2Iso = invertedMu2Iso_;
    invertedTauIso = invertedTauIso_;
    Mu1IsoThreshold = Mu1IsoThreshold_;
    Mu2IsoThreshold = Mu2IsoThreshold_;
    MuIsoUpperBound = MuIsoUpperBound_;
    MuonId = MuonId_;
    diMuonMassLowThreshold = diMuonMassLowThreshold_;
    diMuonMassHighThreshold = diMuonMassHighThreshold_;
    tauMVAIsoRawORWP = tauMVAIsoRawORWP_;
    tauMVAIsoRawThreshold = tauMVAIsoRawThreshold_;
    tauMVAIsoWP = tauMVAIsoWP_;
    tauAntiMuDisc = tauAntiMuDisc_;
    tauAntiEleDisc = tauAntiEleDisc_;
    deepTauID = deepTauID_;
    deepTauVSele = deepTauVSele_;
    deepTauVSmu = deepTauVSmu_;
    deepTauVSjet = deepTauVSjet_;
    tauDecayModeThreshold = tauDecayModeThreshold_;
    muonScaleSyst = muonScaleSyst_;
    tauScaleCorr = tauScaleCorr_;
    rochesterFile = rochesterFile_;
    jpsiCont = jpsiCont_;
    invMassMu1Mu2->SetBins(20, diMuonMassLowThreshold, diMuonMassHighThreshold);

    //--- Create output directory if necessary ---
    if (nMaxEvents > 0) {
        outputDir.Remove(TString::kTrailing, '/');
        outputDir += TString::Format("_%ldevts/", nMaxEvents);
        cout << "Output directory has been changed to " << outputDir << endl;
    }

    TString command = "mkdir -p " + outputDir;
    system(command);

    TChain *chain = new TChain("", "");
    TString treePath = fileName + "/DiMuDiTauAnalyzer/objectTree";
    chain->Add(treePath);
    fChain = chain;
    Init();
}

string MuMuTauMuTauHadAnalyzer::createOutputFileName()
{
    ostringstream outputName;
    fileName.Replace(0, fileName.Last('/'), "");
    fileName.ReplaceAll(".root","");
    outputName << outputDir;
    outputName << "/";
    outputName << fileName;
    outputName << "_histogram";
    outputName << ".root";
    return outputName.str();
}

MuMuTauMuTauHadAnalyzer::~MuMuTauMuTauHadAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MuMuTauMuTauHadAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MuMuTauMuTauHadAnalyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MuMuTauMuTauHadAnalyzer::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   recoMuonPt = 0;
   recoMuonEta = 0;
   recoMuonPhi = 0;
   recoMuonEnergy = 0;
   recoMuonPDGId = 0;
   recoMuonIsolation = 0;
   recoMuonDXY = 0;
   recoMuonDZ = 0;
   recoMuonNTrackerLayers = 0;
   recoMuonTriggerFlag = 0;
   recoMuonRefToElectron = 0;
   recoMuonRefToTau = 0;
   recoMuonIdLoose = 0;
   recoMuonIdMedium = 0;
   recoMuonIdTight = 0;
   recoTauMuonCleanedPt = 0;
   recoTauMuonCleanedEta = 0;
   recoTauMuonCleanedPhi = 0;
   recoTauMuonCleanedEnergy = 0;
   recoTauMuonCleanedPDGId = 0;
   recoTauMuonCleanedDecayMode = 0;
   recoTauMuonCleanedDecayModeFinding = 0;
   recoTauMuonCleanedDecayModeFindingNewDMs = 0;
   recoTauMuonCleanedRefToMuon = 0;
   recoTauMuonCleanedRefToElectron = 0;
   recoTauMuonCleanedDeepVSeraw = 0;
   recoTauMuonCleanedDeepVSjetraw = 0;
   recoTauMuonCleanedDeepVSmuraw = 0;
   recoTauMuonCleanedDeepVSeLoose = 0;
   recoTauMuonCleanedDeepVSjetLoose = 0;
   recoTauMuonCleanedDeepVSmuLoose = 0;
   recoTauMuonCleanedDeepVSeMedium = 0;
   recoTauMuonCleanedDeepVSjetMedium = 0;
   recoTauMuonCleanedDeepVSmuMedium = 0;
   recoTauMuonCleanedDeepVSeTight = 0;
   recoTauMuonCleanedDeepVSjetTight = 0;
   recoTauMuonCleanedDeepVSmuTight = 0;
   recoTauMuonCleanedDeepVSeVLoose = 0;
   recoTauMuonCleanedDeepVSjetVLoose = 0;
   recoTauMuonCleanedDeepVSmuVLoose = 0;
   recoTauMuonCleanedDeepVSeVTight = 0;
   recoTauMuonCleanedDeepVSjetVTight = 0;
   recoTauMuonCleanedDeepVSeVVLoose = 0;
   recoTauMuonCleanedDeepVSjetVVLoose = 0;
   recoTauMuonCleanedDeepVSeVVTight = 0;
   recoTauMuonCleanedDeepVSjetVVTight = 0;
   recoTauMuonCleanedDeepVSeVVVLoose = 0;
   recoTauMuonCleanedDeepVSjetVVVLoose = 0;
   recoTauMuonCleanedIsoMVArawValue = 0;
   recoTauMuonCleanedIsoMVAVVLoose = 0;
   recoTauMuonCleanedIsoMVAVLoose = 0;
   recoTauMuonCleanedIsoMVALoose = 0;
   recoTauMuonCleanedIsoMVAMedium = 0;
   recoTauMuonCleanedIsoMVATight = 0;
   recoTauMuonCleanedIsoMVAVTight = 0;
   recoTauMuonCleanedIsoMVAVVTight = 0;
   recoTauMuonCleanedAntiMuMVALoose = 0;
   recoTauMuonCleanedAntiMuMVATight = 0;
   recoTauMuonCleanedAntiEleMVArawValue = 0;
   recoTauMuonCleanedAntiEleMVAVLoose = 0;
   recoTauMuonCleanedAntiEleMVALoose = 0;
   recoTauMuonCleanedAntiEleMVAMedium = 0;
   recoTauMuonCleanedAntiEleMVATight = 0;
   recoTauMuonCleanedAntiEleMVAVTight = 0;
   recoJetPt = 0;
   recoJetEta = 0;
   recoJetPhi = 0;
   recoJetEnergy = 0;
   recoJetCSV = 0;
   recoMET = 0;
   recoMETPhi = 0;
   recoMETPx = 0;
   recoMETPy = 0;
   genMuonPt = 0;
   genMuonEta = 0;
   genMuonPhi = 0;
   genMuonMass = 0;
   genMuonPDGId = 0;
   genMuonMotherPDGId = 0;
   genTauMuPt = 0;
   genTauMuEta = 0;
   genTauMuPhi = 0;
   genTauMuMass = 0;
   genTauMuPDGId = 0;
   genTauMuMotherPDGId = 0;
   genTauMuVisPt = 0;
   genTauMuVisMass = 0;
   genTauHadPt = 0;
   genTauHadEta = 0;
   genTauHadPhi = 0;
   genTauHadMass = 0;
   genTauHadPDGId = 0;
   genTauHadMotherPDGId = 0;
   genTauHadVisPt = 0;
   genTauHadVisMass = 0;
   genTauHadNPionZero = 0;
   genTauHadNChargedHadrons = 0;
   // Set branch addresses and branch pointers
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("recoMuonPt", &recoMuonPt, &b_recoMuonPt);
   fChain->SetBranchAddress("recoMuonEta", &recoMuonEta, &b_recoMuonEta);
   fChain->SetBranchAddress("recoMuonPhi", &recoMuonPhi, &b_recoMuonPhi);
   fChain->SetBranchAddress("recoMuonEnergy", &recoMuonEnergy, &b_recoMuonEnergy);
   fChain->SetBranchAddress("recoMuonPDGId", &recoMuonPDGId, &b_recoMuonPDGId);
   fChain->SetBranchAddress("recoMuonIsolation", &recoMuonIsolation, &b_recoMuonIsolation);
   fChain->SetBranchAddress("recoMuonDXY", &recoMuonDXY, &b_recoMuonDXY);
   fChain->SetBranchAddress("recoMuonDZ", &recoMuonDZ, &b_recoMuonDZ);
   fChain->SetBranchAddress("recoMuonNTrackerLayers", &recoMuonNTrackerLayers, &b_recoMuonNTrackerLayers);
   fChain->SetBranchAddress("recoMuonTriggerFlag", &recoMuonTriggerFlag, &b_recoMuonTriggerFlag);
   fChain->SetBranchAddress("recoMuonRefToElectron", &recoMuonRefToElectron, &b_recoMuonRefToElectron);
   fChain->SetBranchAddress("recoMuonRefToTau", &recoMuonRefToTau, &b_recoMuonRefToTau);
   fChain->SetBranchAddress("recoMuonIdLoose", &recoMuonIdLoose, &b_recoMuonIdLoose);
   fChain->SetBranchAddress("recoMuonIdMedium", &recoMuonIdMedium, &b_recoMuonIdMedium);
   fChain->SetBranchAddress("recoMuonIdTight", &recoMuonIdTight, &b_recoMuonIdTight);
   fChain->SetBranchAddress("recoTauMuonCleanedPt", &recoTauMuonCleanedPt, &b_recoTauMuonCleanedPt);
   fChain->SetBranchAddress("recoTauMuonCleanedEta", &recoTauMuonCleanedEta, &b_recoTauMuonCleanedEta);
   fChain->SetBranchAddress("recoTauMuonCleanedPhi", &recoTauMuonCleanedPhi, &b_recoTauMuonCleanedPhi);
   fChain->SetBranchAddress("recoTauMuonCleanedEnergy", &recoTauMuonCleanedEnergy, &b_recoTauMuonCleanedEnergy);
   fChain->SetBranchAddress("recoTauMuonCleanedPDGId", &recoTauMuonCleanedPDGId, &b_recoTauMuonCleanedPDGId);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayMode", &recoTauMuonCleanedDecayMode, &b_recoTauMuonCleanedDecayMode);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayModeFinding", &recoTauMuonCleanedDecayModeFinding, &b_recoTauMuonCleanedDecayModeFinding);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayModeFindingNewDMs", &recoTauMuonCleanedDecayModeFindingNewDMs, &b_recoTauMuonCleanedDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauMuonCleanedRefToMuon", &recoTauMuonCleanedRefToMuon, &b_recoTauMuonCleanedRefToMuon);
   fChain->SetBranchAddress("recoTauMuonCleanedRefToElectron", &recoTauMuonCleanedRefToElectron, &b_recoTauMuonCleanedRefToElectron);
   
   if (deepTauID)
   {
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeraw", &recoTauMuonCleanedDeepVSeraw, &b_recoTauMuonCleanedDeepVSeraw);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetraw", &recoTauMuonCleanedDeepVSjetraw, &b_recoTauMuonCleanedDeepVSjetraw);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuraw", &recoTauMuonCleanedDeepVSmuraw, &b_recoTauMuonCleanedDeepVSmuraw);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeLoose", &recoTauMuonCleanedDeepVSeLoose, &b_recoTauMuonCleanedDeepVSeLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetLoose", &recoTauMuonCleanedDeepVSjetLoose, &b_recoTauMuonCleanedDeepVSjetLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuLoose", &recoTauMuonCleanedDeepVSmuLoose, &b_recoTauMuonCleanedDeepVSmuLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeMedium", &recoTauMuonCleanedDeepVSeMedium, &b_recoTauMuonCleanedDeepVSeMedium);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetMedium", &recoTauMuonCleanedDeepVSjetMedium, &b_recoTauMuonCleanedDeepVSjetMedium);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuMedium", &recoTauMuonCleanedDeepVSmuMedium, &b_recoTauMuonCleanedDeepVSmuMedium);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeTight", &recoTauMuonCleanedDeepVSeTight, &b_recoTauMuonCleanedDeepVSeTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetTight", &recoTauMuonCleanedDeepVSjetTight, &b_recoTauMuonCleanedDeepVSjetTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuTight", &recoTauMuonCleanedDeepVSmuTight, &b_recoTauMuonCleanedDeepVSmuTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVLoose", &recoTauMuonCleanedDeepVSeVLoose, &b_recoTauMuonCleanedDeepVSeVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVLoose", &recoTauMuonCleanedDeepVSjetVLoose, &b_recoTauMuonCleanedDeepVSjetVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuVLoose", &recoTauMuonCleanedDeepVSmuVLoose, &b_recoTauMuonCleanedDeepVSmuVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVTight", &recoTauMuonCleanedDeepVSeVTight, &b_recoTauMuonCleanedDeepVSeVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVTight", &recoTauMuonCleanedDeepVSjetVTight, &b_recoTauMuonCleanedDeepVSjetVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVLoose", &recoTauMuonCleanedDeepVSeVVLoose, &b_recoTauMuonCleanedDeepVSeVVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVLoose", &recoTauMuonCleanedDeepVSjetVVLoose, &b_recoTauMuonCleanedDeepVSjetVVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVTight", &recoTauMuonCleanedDeepVSeVVTight, &b_recoTauMuonCleanedDeepVSeVVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVTight", &recoTauMuonCleanedDeepVSjetVVTight, &b_recoTauMuonCleanedDeepVSjetVVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVVLoose", &recoTauMuonCleanedDeepVSeVVVLoose, &b_recoTauMuonCleanedDeepVSeVVVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVVLoose", &recoTauMuonCleanedDeepVSjetVVVLoose, &b_recoTauMuonCleanedDeepVSjetVVVLoose);
   } // end if deepTauID

   else{
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVArawValue", &recoTauMuonCleanedIsoMVArawValue, &b_recoTauMuonCleanedIsoMVArawValue);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVVLoose", &recoTauMuonCleanedIsoMVAVVLoose, &b_recoTauMuonCleanedIsoMVAVVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVLoose", &recoTauMuonCleanedIsoMVAVLoose, &b_recoTauMuonCleanedIsoMVAVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVALoose", &recoTauMuonCleanedIsoMVALoose, &b_recoTauMuonCleanedIsoMVALoose);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAMedium", &recoTauMuonCleanedIsoMVAMedium, &b_recoTauMuonCleanedIsoMVAMedium);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVATight", &recoTauMuonCleanedIsoMVATight, &b_recoTauMuonCleanedIsoMVATight);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVTight", &recoTauMuonCleanedIsoMVAVTight, &b_recoTauMuonCleanedIsoMVAVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVVTight", &recoTauMuonCleanedIsoMVAVVTight, &b_recoTauMuonCleanedIsoMVAVVTight);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiMuMVALoose", &recoTauMuonCleanedAntiMuMVALoose, &b_recoTauMuonCleanedAntiMuMVALoose);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiMuMVATight", &recoTauMuonCleanedAntiMuMVATight, &b_recoTauMuonCleanedAntiMuMVATight);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVArawValue", &recoTauMuonCleanedAntiEleMVArawValue, &b_recoTauMuonCleanedAntiEleMVArawValue);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAVLoose", &recoTauMuonCleanedAntiEleMVAVLoose, &b_recoTauMuonCleanedAntiEleMVAVLoose);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVALoose", &recoTauMuonCleanedAntiEleMVALoose, &b_recoTauMuonCleanedAntiEleMVALoose);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAMedium", &recoTauMuonCleanedAntiEleMVAMedium, &b_recoTauMuonCleanedAntiEleMVAMedium);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVATight", &recoTauMuonCleanedAntiEleMVATight, &b_recoTauMuonCleanedAntiEleMVATight);
       fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAVTight", &recoTauMuonCleanedAntiEleMVAVTight, &b_recoTauMuonCleanedAntiEleMVAVTight);
   } // end if not deepTauID

   fChain->SetBranchAddress("recoJetPt", &recoJetPt, &b_recoJetPt);
   fChain->SetBranchAddress("recoJetEta", &recoJetEta, &b_recoJetEta);
   fChain->SetBranchAddress("recoJetPhi", &recoJetPhi, &b_recoJetPhi);
   fChain->SetBranchAddress("recoJetEnergy", &recoJetEnergy, &b_recoJetEnergy);
   fChain->SetBranchAddress("recoJetCSV", &recoJetCSV, &b_recoJetCSV);
   fChain->SetBranchAddress("recoMET", &recoMET, &b_recoMET);
   fChain->SetBranchAddress("recoMETPhi", &recoMETPhi, &b_recoMETPhi);
   fChain->SetBranchAddress("recoMETPx", &recoMETPx, &b_recoMETPx);
   fChain->SetBranchAddress("recoMETPy", &recoMETPy, &b_recoMETPy);
   fChain->SetBranchAddress("recoNPrimaryVertex", &recoNPrimaryVertex, &b_recoNPrimaryVertex);
   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   if (isMC) 
   {
       fChain->SetBranchAddress("genMuonPt", &genMuonPt, &b_genMuonPt);
       fChain->SetBranchAddress("genMuonEta", &genMuonEta, &b_genMuonEta);
       fChain->SetBranchAddress("genMuonPhi", &genMuonPhi, &b_genMuonPhi);
       fChain->SetBranchAddress("genMuonMass", &genMuonMass, &b_genMuonMass);
       fChain->SetBranchAddress("genMuonPDGId", &genMuonPDGId, &b_genMuonPDGId);
       fChain->SetBranchAddress("genMuonMotherPDGId", &genMuonMotherPDGId, &b_genMuonMotherPDGId);
       fChain->SetBranchAddress("genTauMuPt", &genTauMuPt, &b_genTauMuPt);
       fChain->SetBranchAddress("genTauMuEta", &genTauMuEta, &b_genTauMuEta);
       fChain->SetBranchAddress("genTauMuPhi", &genTauMuPhi, &b_genTauMuPhi);
       fChain->SetBranchAddress("genTauMuMass", &genTauMuMass, &b_genTauMuMass);
       fChain->SetBranchAddress("genTauMuPDGId", &genTauMuPDGId, &b_genTauMuPDGId);
       fChain->SetBranchAddress("genTauMuMotherPDGId", &genTauMuMotherPDGId, &b_genTauMuMotherPDGId);
       fChain->SetBranchAddress("genTauMuVisPt", &genTauMuVisPt, &b_genTauMuVisPt);
       fChain->SetBranchAddress("genTauMuVisMass", &genTauMuVisMass, &b_genTauMuVisMass);
       fChain->SetBranchAddress("genTauHadPt", &genTauHadPt, &b_genTauHadPt);
       fChain->SetBranchAddress("genTauHadEta", &genTauHadEta, &b_genTauHadEta);
       fChain->SetBranchAddress("genTauHadPhi", &genTauHadPhi, &b_genTauHadPhi);
       fChain->SetBranchAddress("genTauHadMass", &genTauHadMass, &b_genTauHadMass);
       fChain->SetBranchAddress("genTauHadPDGId", &genTauHadPDGId, &b_genTauHadPDGId);
       fChain->SetBranchAddress("genTauHadMotherPDGId", &genTauHadMotherPDGId, &b_genTauHadMotherPDGId);
       fChain->SetBranchAddress("genTauHadVisPt", &genTauHadVisPt, &b_genTauHadVisPt);
       fChain->SetBranchAddress("genTauHadVisMass", &genTauHadVisMass, &b_genTauHadVisMass);
       fChain->SetBranchAddress("genTauHadNPionZero", &genTauHadNPionZero, &b_genTauHadNPionZero);
       fChain->SetBranchAddress("genTauHadNChargedHadrons", &genTauHadNChargedHadrons, &b_genTauHadNChargedHadrons);
       fChain->SetBranchAddress("recoNPU", &recoNPU, &b_recoNPU);
       fChain->SetBranchAddress("trueNInteraction", &trueNInteraction, &b_trueNInteraction);
       fChain->SetBranchAddress("genEventWeight", &genEventWeight, &b_genEventWeight);
   } // end if isMC
   Notify();
}

Bool_t MuMuTauMuTauHadAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MuMuTauMuTauHadAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MuMuTauMuTauHadAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MuMuTauMuTauHadAnalyzer_cxx

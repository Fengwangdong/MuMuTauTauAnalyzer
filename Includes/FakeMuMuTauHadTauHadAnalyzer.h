//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  6 17:46:43 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTreelization.root
//////////////////////////////////////////////////////////

#ifndef FakeMuMuTauHadTauHadAnalyzer_h
#define FakeMuMuTauHadTauHadAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "HistoZmumu.h"

class FakeMuMuTauHadTauHadAnalyzer : public HistoZmumu {
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
   vector<float>   *recoTauBoostedPt;
   vector<float>   *recoTauBoostedEta;
   vector<float>   *recoTauBoostedPhi;
   vector<float>   *recoTauBoostedEnergy;
   vector<int>     *recoTauBoostedPDGId;
   vector<float>   *recoTauBoostedDecayMode;
   vector<float>   *recoTauBoostedDecayModeFinding;
   vector<float>   *recoTauBoostedDecayModeFindingNewDMs;
   vector<int>     *recoTauBoostedRefToMuon;
   vector<int>     *recoTauBoostedRefToElectron;
   vector<float>   *recoTauBoostedDeepVSeraw;
   vector<float>   *recoTauBoostedDeepVSjetraw;
   vector<float>   *recoTauBoostedDeepVSmuraw;
   vector<float>   *recoTauBoostedDeepVSeLoose;
   vector<float>   *recoTauBoostedDeepVSjetLoose;
   vector<float>   *recoTauBoostedDeepVSmuLoose;
   vector<float>   *recoTauBoostedDeepVSeMedium;
   vector<float>   *recoTauBoostedDeepVSjetMedium;
   vector<float>   *recoTauBoostedDeepVSmuMedium;
   vector<float>   *recoTauBoostedDeepVSeTight;
   vector<float>   *recoTauBoostedDeepVSjetTight;
   vector<float>   *recoTauBoostedDeepVSmuTight;
   vector<float>   *recoTauBoostedDeepVSeVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVLoose;
   vector<float>   *recoTauBoostedDeepVSmuVLoose;
   vector<float>   *recoTauBoostedDeepVSeVTight;
   vector<float>   *recoTauBoostedDeepVSjetVTight;
   vector<float>   *recoTauBoostedDeepVSeVVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVVLoose;
   vector<float>   *recoTauBoostedDeepVSeVVTight;
   vector<float>   *recoTauBoostedDeepVSjetVVTight;
   vector<float>   *recoTauBoostedDeepVSeVVVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVVVLoose;
   vector<float>   *recoTauBoostedIsoMVArawValue;
   vector<float>   *recoTauBoostedIsoMVAVVLoose;
   vector<float>   *recoTauBoostedIsoMVAVLoose;
   vector<float>   *recoTauBoostedIsoMVALoose;
   vector<float>   *recoTauBoostedIsoMVAMedium;
   vector<float>   *recoTauBoostedIsoMVATight;
   vector<float>   *recoTauBoostedIsoMVAVTight;
   vector<float>   *recoTauBoostedIsoMVAVVTight;
   vector<float>   *recoTauBoostedAntiMuMVALoose;
   vector<float>   *recoTauBoostedAntiMuMVATight;
   vector<float>   *recoTauBoostedAntiEleMVArawValue;
   vector<float>   *recoTauBoostedAntiEleMVAVLoose;
   vector<float>   *recoTauBoostedAntiEleMVALoose;
   vector<float>   *recoTauBoostedAntiEleMVAMedium;
   vector<float>   *recoTauBoostedAntiEleMVATight;
   vector<float>   *recoTauBoostedAntiEleMVAVTight;
   vector<float>   *recoJetPt;
   vector<float>   *recoJetEta;
   vector<float>   *recoJetPhi;
   vector<float>   *recoJetEnergy;
   vector<float>   *recoJetCSV;
   vector<float>   *recoJetDeepDiTauValuev1;
   vector<float>   *recoJetDeepDiTauValueMDv1;
   vector<float>   *recoJetDeepDiTauValuev2;
   vector<float>   *recoJetDeepDiTauValueMDv2;
   vector<int>     *recoJetIdLoose;
   vector<int>     *recoJetIdTight;
   vector<int>     *recoJetIdTightLepVeto;
   vector<int>     *recoJetIdPileUp;
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
   TBranch        *b_recoTauBoostedPt;   //!
   TBranch        *b_recoTauBoostedEta;   //!
   TBranch        *b_recoTauBoostedPhi;   //!
   TBranch        *b_recoTauBoostedEnergy;   //!
   TBranch        *b_recoTauBoostedPDGId;   //!
   TBranch        *b_recoTauBoostedDecayMode;   //!
   TBranch        *b_recoTauBoostedDecayModeFinding;   //!
   TBranch        *b_recoTauBoostedDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauBoostedRefToMuon;   //!
   TBranch        *b_recoTauBoostedRefToElectron;   //!
   TBranch        *b_recoTauBoostedDeepVSeraw;   //!
   TBranch        *b_recoTauBoostedDeepVSjetraw;   //!
   TBranch        *b_recoTauBoostedDeepVSmuraw;   //!
   TBranch        *b_recoTauBoostedDeepVSeLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSmuLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSjetMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSmuMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSeTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetTight;   //!
   TBranch        *b_recoTauBoostedDeepVSmuTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSmuVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVArawValue;   //!
   TBranch        *b_recoTauBoostedIsoMVAVVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVAVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVALoose;   //!
   TBranch        *b_recoTauBoostedIsoMVAMedium;   //!
   TBranch        *b_recoTauBoostedIsoMVATight;   //!
   TBranch        *b_recoTauBoostedIsoMVAVTight;   //!
   TBranch        *b_recoTauBoostedIsoMVAVVTight;   //!
   TBranch        *b_recoTauBoostedAntiMuMVALoose;   //!
   TBranch        *b_recoTauBoostedAntiMuMVATight;   //!
   TBranch        *b_recoTauBoostedAntiEleMVArawValue;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauBoostedAntiEleMVALoose;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAMedium;   //!
   TBranch        *b_recoTauBoostedAntiEleMVATight;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAVTight;   //!
   TBranch        *b_recoJetPt;   //!
   TBranch        *b_recoJetEta;   //!
   TBranch        *b_recoJetPhi;   //!
   TBranch        *b_recoJetEnergy;   //!
   TBranch        *b_recoJetCSV;   //!
   TBranch        *b_recoJetDeepDiTauValuev1;   //!
   TBranch        *b_recoJetDeepDiTauValueMDv1;   //!
   TBranch        *b_recoJetDeepDiTauValuev2;   //!
   TBranch        *b_recoJetDeepDiTauValueMDv2;   //!
   TBranch        *b_recoJetIdLoose;   //!
   TBranch        *b_recoJetIdTight;   //!
   TBranch        *b_recoJetIdTightLepVeto;   //!
   TBranch        *b_recoJetIdPileUp;   //!
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
   double Mu1IsoThreshold;
   double Mu2IsoThreshold;
   TString MuonId;
   bool boostDiTauOpt;
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
   TString JetId;
   bool massDecorrelation;
   double deepDiTauRawThreshold;
   bool matchRecGen;
   TString rochesterFile;

   FakeMuMuTauHadTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, double Mu1IsoThreshold_ = 0.25, double Mu2IsoThreshold_ = 0.25, TString MuonId_ = "LOOSE", bool boostDiTauOpt_ = false, bool tauMVAIsoRawORWP_ = false, double tauMVAIsoRawThreshold_ = -0.5, TString tauMVAIsoWP_ = "MEDIUM", TString tauAntiMuDisc_ = "NULL", TString tauAntiEleDisc_ = "LOOSE", bool deepTauID_ = false, TString deepTauVSele_ = "LOOSE", TString deepTauVSmu_ = "LOOSE", TString deepTauVSjet_ = "MEDIUM", double tauDecayModeThreshold_ = -1, TString JetId_ = "TIGHT", bool massDecorrelation_ = false, double deepDiTauRawThreshold_ = 0.5, bool matchRecGen_ = false, TString rochesterFile_ = "");
   string createOutputFileName();
   virtual ~FakeMuMuTauHadTauHadAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FakeMuMuTauHadTauHadAnalyzer_cxx
FakeMuMuTauHadTauHadAnalyzer::FakeMuMuTauHadTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, double Mu1IsoThreshold_, double Mu2IsoThreshold_, TString MuonId_, bool boostDiTauOpt_, bool tauMVAIsoRawORWP_, double tauMVAIsoRawThreshold_, TString tauMVAIsoWP_, TString tauAntiMuDisc_, TString tauAntiEleDisc_, bool deepTauID_, TString deepTauVSele_, TString deepTauVSmu_, TString deepTauVSjet_, double tauDecayModeThreshold_, TString JetId_, bool massDecorrelation_, double deepDiTauRawThreshold_, bool matchRecGen_, TString rochesterFile_) : HistoZmumu() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    Mu1IsoThreshold = Mu1IsoThreshold_;
    Mu2IsoThreshold = Mu2IsoThreshold_;
    MuonId = MuonId_;
    boostDiTauOpt = boostDiTauOpt_;
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
    JetId = JetId_;
    massDecorrelation = massDecorrelation_;
    deepDiTauRawThreshold = deepDiTauRawThreshold_;
    matchRecGen = matchRecGen_;
    rochesterFile = rochesterFile_;

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

string FakeMuMuTauHadTauHadAnalyzer::createOutputFileName()
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

FakeMuMuTauHadTauHadAnalyzer::~FakeMuMuTauHadTauHadAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FakeMuMuTauHadTauHadAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FakeMuMuTauHadTauHadAnalyzer::LoadTree(Long64_t entry)
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

void FakeMuMuTauHadTauHadAnalyzer::Init()
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
   recoTauBoostedPt = 0;
   recoTauBoostedEta = 0;
   recoTauBoostedPhi = 0;
   recoTauBoostedEnergy = 0;
   recoTauBoostedPDGId = 0;
   recoTauBoostedDecayMode = 0;
   recoTauBoostedDecayModeFinding = 0;
   recoTauBoostedDecayModeFindingNewDMs = 0;
   recoTauBoostedRefToMuon = 0;
   recoTauBoostedRefToElectron = 0;
   recoTauBoostedDeepVSeraw = 0;
   recoTauBoostedDeepVSjetraw = 0;
   recoTauBoostedDeepVSmuraw = 0;
   recoTauBoostedDeepVSeLoose = 0;
   recoTauBoostedDeepVSjetLoose = 0;
   recoTauBoostedDeepVSmuLoose = 0;
   recoTauBoostedDeepVSeMedium = 0;
   recoTauBoostedDeepVSjetMedium = 0;
   recoTauBoostedDeepVSmuMedium = 0;
   recoTauBoostedDeepVSeTight = 0;
   recoTauBoostedDeepVSjetTight = 0;
   recoTauBoostedDeepVSmuTight = 0;
   recoTauBoostedDeepVSeVLoose = 0;
   recoTauBoostedDeepVSjetVLoose = 0;
   recoTauBoostedDeepVSmuVLoose = 0;
   recoTauBoostedDeepVSeVTight = 0;
   recoTauBoostedDeepVSjetVTight = 0;
   recoTauBoostedDeepVSeVVLoose = 0;
   recoTauBoostedDeepVSjetVVLoose = 0;
   recoTauBoostedDeepVSeVVTight = 0;
   recoTauBoostedDeepVSjetVVTight = 0;
   recoTauBoostedDeepVSeVVVLoose = 0;
   recoTauBoostedDeepVSjetVVVLoose = 0;
   recoTauBoostedIsoMVArawValue = 0;
   recoTauBoostedIsoMVAVVLoose = 0;
   recoTauBoostedIsoMVAVLoose = 0;
   recoTauBoostedIsoMVALoose = 0;
   recoTauBoostedIsoMVAMedium = 0;
   recoTauBoostedIsoMVATight = 0;
   recoTauBoostedIsoMVAVTight = 0;
   recoTauBoostedIsoMVAVVTight = 0;
   recoTauBoostedAntiMuMVALoose = 0;
   recoTauBoostedAntiMuMVATight = 0;
   recoTauBoostedAntiEleMVArawValue = 0;
   recoTauBoostedAntiEleMVAVLoose = 0;
   recoTauBoostedAntiEleMVALoose = 0;
   recoTauBoostedAntiEleMVAMedium = 0;
   recoTauBoostedAntiEleMVATight = 0;
   recoTauBoostedAntiEleMVAVTight = 0;
   recoJetPt = 0;
   recoJetEta = 0;
   recoJetPhi = 0;
   recoJetEnergy = 0;
   recoJetCSV = 0;
   recoJetDeepDiTauValuev1 = 0;
   recoJetDeepDiTauValueMDv1 = 0;
   recoJetDeepDiTauValuev2 = 0;
   recoJetDeepDiTauValueMDv2 = 0;
   recoJetIdLoose = 0;
   recoJetIdTight = 0;
   recoJetIdTightLepVeto = 0;
   recoJetIdPileUp = 0;
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
   fChain->SetBranchAddress("recoTauBoostedPt", &recoTauBoostedPt, &b_recoTauBoostedPt);
   fChain->SetBranchAddress("recoTauBoostedEta", &recoTauBoostedEta, &b_recoTauBoostedEta);
   fChain->SetBranchAddress("recoTauBoostedPhi", &recoTauBoostedPhi, &b_recoTauBoostedPhi);
   fChain->SetBranchAddress("recoTauBoostedEnergy", &recoTauBoostedEnergy, &b_recoTauBoostedEnergy);
   fChain->SetBranchAddress("recoTauBoostedPDGId", &recoTauBoostedPDGId, &b_recoTauBoostedPDGId);
   fChain->SetBranchAddress("recoTauBoostedDecayMode", &recoTauBoostedDecayMode, &b_recoTauBoostedDecayMode);
   fChain->SetBranchAddress("recoTauBoostedDecayModeFinding", &recoTauBoostedDecayModeFinding, &b_recoTauBoostedDecayModeFinding);
   fChain->SetBranchAddress("recoTauBoostedDecayModeFindingNewDMs", &recoTauBoostedDecayModeFindingNewDMs, &b_recoTauBoostedDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauBoostedRefToMuon", &recoTauBoostedRefToMuon, &b_recoTauBoostedRefToMuon);
   fChain->SetBranchAddress("recoTauBoostedRefToElectron", &recoTauBoostedRefToElectron, &b_recoTauBoostedRefToElectron);
   
   if (deepTauID)
   {
       fChain->SetBranchAddress("recoTauBoostedDeepVSeraw", &recoTauBoostedDeepVSeraw, &b_recoTauBoostedDeepVSeraw);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetraw", &recoTauBoostedDeepVSjetraw, &b_recoTauBoostedDeepVSjetraw);
       fChain->SetBranchAddress("recoTauBoostedDeepVSmuraw", &recoTauBoostedDeepVSmuraw, &b_recoTauBoostedDeepVSmuraw);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeLoose", &recoTauBoostedDeepVSeLoose, &b_recoTauBoostedDeepVSeLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetLoose", &recoTauBoostedDeepVSjetLoose, &b_recoTauBoostedDeepVSjetLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSmuLoose", &recoTauBoostedDeepVSmuLoose, &b_recoTauBoostedDeepVSmuLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeMedium", &recoTauBoostedDeepVSeMedium, &b_recoTauBoostedDeepVSeMedium);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetMedium", &recoTauBoostedDeepVSjetMedium, &b_recoTauBoostedDeepVSjetMedium);
       fChain->SetBranchAddress("recoTauBoostedDeepVSmuMedium", &recoTauBoostedDeepVSmuMedium, &b_recoTauBoostedDeepVSmuMedium);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeTight", &recoTauBoostedDeepVSeTight, &b_recoTauBoostedDeepVSeTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetTight", &recoTauBoostedDeepVSjetTight, &b_recoTauBoostedDeepVSjetTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSmuTight", &recoTauBoostedDeepVSmuTight, &b_recoTauBoostedDeepVSmuTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeVLoose", &recoTauBoostedDeepVSeVLoose, &b_recoTauBoostedDeepVSeVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetVLoose", &recoTauBoostedDeepVSjetVLoose, &b_recoTauBoostedDeepVSjetVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSmuVLoose", &recoTauBoostedDeepVSmuVLoose, &b_recoTauBoostedDeepVSmuVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeVTight", &recoTauBoostedDeepVSeVTight, &b_recoTauBoostedDeepVSeVTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetVTight", &recoTauBoostedDeepVSjetVTight, &b_recoTauBoostedDeepVSjetVTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeVVLoose", &recoTauBoostedDeepVSeVVLoose, &b_recoTauBoostedDeepVSeVVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVLoose", &recoTauBoostedDeepVSjetVVLoose, &b_recoTauBoostedDeepVSjetVVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeVVTight", &recoTauBoostedDeepVSeVVTight, &b_recoTauBoostedDeepVSeVVTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVTight", &recoTauBoostedDeepVSjetVVTight, &b_recoTauBoostedDeepVSjetVVTight);
       fChain->SetBranchAddress("recoTauBoostedDeepVSeVVVLoose", &recoTauBoostedDeepVSeVVVLoose, &b_recoTauBoostedDeepVSeVVVLoose);
       fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVVLoose", &recoTauBoostedDeepVSjetVVVLoose, &b_recoTauBoostedDeepVSjetVVVLoose);
   } // end if deepTauID

   else{
       fChain->SetBranchAddress("recoTauBoostedIsoMVArawValue", &recoTauBoostedIsoMVArawValue, &b_recoTauBoostedIsoMVArawValue);
       fChain->SetBranchAddress("recoTauBoostedIsoMVAVVLoose", &recoTauBoostedIsoMVAVVLoose, &b_recoTauBoostedIsoMVAVVLoose);
       fChain->SetBranchAddress("recoTauBoostedIsoMVAVLoose", &recoTauBoostedIsoMVAVLoose, &b_recoTauBoostedIsoMVAVLoose);
       fChain->SetBranchAddress("recoTauBoostedIsoMVALoose", &recoTauBoostedIsoMVALoose, &b_recoTauBoostedIsoMVALoose);
       fChain->SetBranchAddress("recoTauBoostedIsoMVAMedium", &recoTauBoostedIsoMVAMedium, &b_recoTauBoostedIsoMVAMedium);
       fChain->SetBranchAddress("recoTauBoostedIsoMVATight", &recoTauBoostedIsoMVATight, &b_recoTauBoostedIsoMVATight);
       fChain->SetBranchAddress("recoTauBoostedIsoMVAVTight", &recoTauBoostedIsoMVAVTight, &b_recoTauBoostedIsoMVAVTight);
       fChain->SetBranchAddress("recoTauBoostedIsoMVAVVTight", &recoTauBoostedIsoMVAVVTight, &b_recoTauBoostedIsoMVAVVTight);
       fChain->SetBranchAddress("recoTauBoostedAntiMuMVALoose", &recoTauBoostedAntiMuMVALoose, &b_recoTauBoostedAntiMuMVALoose);
       fChain->SetBranchAddress("recoTauBoostedAntiMuMVATight", &recoTauBoostedAntiMuMVATight, &b_recoTauBoostedAntiMuMVATight);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVArawValue", &recoTauBoostedAntiEleMVArawValue, &b_recoTauBoostedAntiEleMVArawValue);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVAVLoose", &recoTauBoostedAntiEleMVAVLoose, &b_recoTauBoostedAntiEleMVAVLoose);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVALoose", &recoTauBoostedAntiEleMVALoose, &b_recoTauBoostedAntiEleMVALoose);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVAMedium", &recoTauBoostedAntiEleMVAMedium, &b_recoTauBoostedAntiEleMVAMedium);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVATight", &recoTauBoostedAntiEleMVATight, &b_recoTauBoostedAntiEleMVATight);
       fChain->SetBranchAddress("recoTauBoostedAntiEleMVAVTight", &recoTauBoostedAntiEleMVAVTight, &b_recoTauBoostedAntiEleMVAVTight);
   } // end if not deepTauID

   fChain->SetBranchAddress("recoJetPt", &recoJetPt, &b_recoJetPt);
   fChain->SetBranchAddress("recoJetEta", &recoJetEta, &b_recoJetEta);
   fChain->SetBranchAddress("recoJetPhi", &recoJetPhi, &b_recoJetPhi);
   fChain->SetBranchAddress("recoJetEnergy", &recoJetEnergy, &b_recoJetEnergy);
   fChain->SetBranchAddress("recoJetCSV", &recoJetCSV, &b_recoJetCSV);
   fChain->SetBranchAddress("recoJetDeepDiTauValuev1", &recoJetDeepDiTauValuev1, &b_recoJetDeepDiTauValuev1);
   fChain->SetBranchAddress("recoJetDeepDiTauValueMDv1", &recoJetDeepDiTauValueMDv1, &b_recoJetDeepDiTauValueMDv1);
   fChain->SetBranchAddress("recoJetDeepDiTauValuev2", &recoJetDeepDiTauValuev2, &b_recoJetDeepDiTauValuev2);
   fChain->SetBranchAddress("recoJetDeepDiTauValueMDv2", &recoJetDeepDiTauValueMDv2, &b_recoJetDeepDiTauValueMDv2);
   fChain->SetBranchAddress("recoJetIdLoose", &recoJetIdLoose, &b_recoJetIdLoose);
   fChain->SetBranchAddress("recoJetIdTight", &recoJetIdTight, &b_recoJetIdTight);
   fChain->SetBranchAddress("recoJetIdTightLepVeto", &recoJetIdTightLepVeto, &b_recoJetIdTightLepVeto);
   fChain->SetBranchAddress("recoJetIdPileUp", &recoJetIdPileUp, &b_recoJetIdPileUp);
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

Bool_t FakeMuMuTauHadTauHadAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FakeMuMuTauHadTauHadAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FakeMuMuTauHadTauHadAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FakeMuMuTauHadTauHadAnalyzer_cxx

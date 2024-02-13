#define MuMuTauMuTauHadAnalyzer_cxx
#include "MuMuTauMuTauHadAnalyzer.h"
#include "RoccoR.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TRandom.h>
#include <iomanip>
#include <iostream>
#include <TLorentzVector.h>
#include <math.h>
using namespace std;

void MuMuTauMuTauHadAnalyzer::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if (nMaxEvents >= 0 && nMaxEvents  < nentries) nentries = nMaxEvents;
   cout << "We will run on " << nentries << " events" << endl;

   Long64_t nbytes = 0, nb = 0;

   // ---- define the variable for rochester correction ----
   string rochesterFileName = rochesterFile.Data();
   RoccoR rc(rochesterFileName);
   double rochesterSF = 1;
   int errorMember = 0;

   if (muonScaleSyst < 0) muonScaleSyst = fabs(muonScaleSyst);
   if (muonScaleSyst > 104) muonScaleSyst = 104;
   if (muonScaleSyst > 5)
   {
       errorMember = muonScaleSyst - 5;
       muonScaleSyst = 1; // error set to statistical uncertainty replicas
   } // end if muonScaleSyst > 5

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % 1000 == 0 && jentry > 0) cout << "*** Processing #Events: " << jentry << endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      // ---- define varibles that will be used to be filled into histograms ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Mu3;
      TLorentzVector Tau;

      float Mu1Iso;
      float Mu2Iso;
      float Mu3Iso;
      float TauIso;
      float TauDM;

      float Mu1Dz;
      float Mu2Dz;

      unsigned int indexMu1 = -1;
      unsigned int indexMu2 = -1;
      // ============================================================================

      // ---- start loop on muon candidates for mu1 ----
      bool findMu1 = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          //bool passDXYDZ = jpsiCont ? (fabs(recoMuonDXY->at(iMuon)) < 0.2) : (fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5);

          //if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold && passMuonID && passDXYDZ) 
          if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold && passMuonID) 
          {
              Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              double recoMuonMass = Mu1.M();

              if (isMC)
              {
                  double rng = gRandom->Rndm();
                  rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
              } // end if isMC == true

              else{
                  rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
              } // end if isMC == false (data)

              Mu1.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
              Mu1Iso = recoMuonIsolation->at(iMuon);
              Mu1Dz = recoMuonDZ->at(iMuon);
              indexMu1 = iMuon;
              findMu1 = true;
              break;
          } // end if there is any matched Mu1 candidiate
      } // end loop for mu1

      if (!findMu1) continue;
      float smallestDR = 1.0; // dR cut between Mu1 and Mu2
      bool findMu2 = false;

      // ---- start loop on muon candidates for mu2 ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          //bool passDXYDZ = jpsiCont ? (fabs(recoMuonDXY->at(iMuon)) < 0.2) : (fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5);

          if (iMuon == indexMu1) continue;
          if (jpsiCont && recoMuonTriggerFlag->at(iMuon) != 1) continue; // the second muon matched with the trigger mu if double muon type trigger used
          //if ((!invertedMu2Iso && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
          if ((!invertedMu2Iso && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID) continue;

          TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
          Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          double recoMuonMass = Mu2Cand.M();

          if (isMC)
          {
              double rng = gRandom->Rndm();
              rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
          } // end if isMC == true

          else{
              rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
          } // end if isMC == false (data)

          Mu2Cand.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);

          if((Mu1.DeltaR(Mu2Cand) < smallestDR) && (recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)) && ((Mu1+Mu2Cand).M() > diMuonMassLowThreshold) && ((Mu1+Mu2Cand).M() < diMuonMassHighThreshold))
          {
              Mu2.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
              Mu2Iso = recoMuonIsolation->at(iMuon);
              Mu2Dz = recoMuonDZ->at(iMuon);
              smallestDR = Mu1.DeltaR(Mu2);
              indexMu2 = iMuon;
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;

      bool findMuTauPair = false;
      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauMuonCleanedPt->size(); iTau++)
      {
          if (deepTauID && recoTauMuonCleanedDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauMuonCleanedDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauMuonCleanedDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauMuonCleanedDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauMuonCleanedDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauMuonCleanedDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauMuonCleanedDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauMuonCleanedDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauMuonCleanedDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauMuonCleanedDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauMuonCleanedDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauMuonCleanedDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauMuonCleanedDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauMuonCleanedDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauMuonCleanedDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauMuonCleanedDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauMuonCleanedDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauMuonCleanedDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauMuonCleanedDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauMuonCleanedDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauMuonCleanedDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauMuonCleanedDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauMuonCleanedDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauMuonCleanedDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauMuonCleanedDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauMuonCleanedDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauMuonCleanedDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauMuonCleanedDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauMuonCleanedDeepVSjetVVVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && passCondTauDeepVSele && passCondTauDeepVSmu);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauMuonCleanedDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauMuonCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauMuonCleanedIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauMuonCleanedIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauMuonCleanedIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauMuonCleanedIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauMuonCleanedIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauMuonCleanedIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauMuonCleanedIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauMuonCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauMuonCleanedIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauMuonCleanedIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauMuonCleanedIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauMuonCleanedIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauMuonCleanedIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauMuonCleanedIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauMuonCleanedIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauMuonCleanedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauMuonCleanedAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauMuonCleanedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauMuonCleanedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauMuonCleanedAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauMuonCleanedPt->at(iTau), recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedEnergy->at(iTau));
          double recoTauMuonCleanedMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauMuonCleanedPt->at(iTau)*tauScaleCorr, recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedMass);

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8 || TauCand.Pt() < 10.0) continue;

          // ---- bjet veto for tau ---
          //bool bjetVeto = false;
          //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
          //{
          //    TLorentzVector Jet;
          //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          //    if (TauCand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
          //    {
          //        bjetVeto = true;
          //        break;
          //    } // end if bjet veto
          //} // end for loop over the reco-jets
          //if (bjetVeto) continue;

          if ((recoTauMuonCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauMuonCleanedPt->at(iTau)*tauScaleCorr, recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedMass);
          TauIso = deepTauID ? recoTauMuonCleanedDeepVSjetraw->at(iTau) : recoTauMuonCleanedIsoMVArawValue->at(iTau);
          TauDM = recoTauMuonCleanedDecayMode->at(iTau);

          float smallestDR = 0.8; // dR cut between Mu3 and tau
          bool findMu3 = false;

          for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
          {
              bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
              bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
              bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
              bool passMuonID = isLoose || isMedium || isTight;
              //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

              if (iMuon == indexMu1 || iMuon == indexMu2) continue;
              //if (!passMuonID || !passDXYDZ) continue;
              if (!passMuonID) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, tau) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              double recoMuonMass = Mu3Cand.M();

              if (isMC)
              {
                  double rng = gRandom->Rndm();
                  rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
              } // end if isMC == true

              else{
                  rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
              } // end if isMC == false (data)

              Mu3Cand.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);

              bool overlapMuTau = recoMuonRefToTau->at(iMuon) > 0 && recoTauMuonCleanedRefToMuon->at(iTau) > 0 && recoMuonRefToTau->at(iMuon) == recoTauMuonCleanedRefToMuon->at(iTau);

              //if ((Tau.DeltaR(Mu3Cand) < smallestDR) && (recoTauMuonCleanedPDGId->at(iTau)/fabs(recoTauMuonCleanedPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && ((Tau+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuTau)
              if ((Tau.DeltaR(Mu3Cand) < smallestDR) && (recoTauMuonCleanedPDGId->at(iTau)/fabs(recoTauMuonCleanedPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuTau)
              {
                  Mu3.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
                  Mu3Iso = recoMuonIsolation->at(iMuon); 
                  smallestDR = Tau.DeltaR(Mu3);
                  findMu3 = true;
              } // end if find mu3 with tau matched
          } // end loop for mu3

          if (!findMu3) continue;
          else{
              findMuTauPair = true;
              break;
          } // end if findMu3
      } // end loop for tau

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight;
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findMuTauPair)
      {
          ptMu1Mu2->Fill((Mu1+Mu2).Pt(), weight);
          dRMu1Mu2->Fill(Mu1.DeltaR(Mu2), weight);
          invMassMu1Mu2->Fill((Mu1+Mu2).M(), weight);
          dRInvMassMu1Mu2->Fill(Mu1.DeltaR(Mu2), (Mu1+Mu2).M(), weight);

          mu1Iso->Fill(Mu1Iso, weight);
          mu2Iso->Fill(Mu2Iso, weight);

          mu1Pt->Fill(Mu1.Pt(), weight);
          mu1Eta->Fill(Mu1.Eta(), weight);
          mu1Phi->Fill(Mu1.Phi(), weight);

          mu2Pt->Fill(Mu2.Pt(), weight);
          mu2Eta->Fill(Mu2.Eta(), weight);
          mu2Phi->Fill(Mu2.Phi(), weight);

          ptMu3Tau->Fill((Mu3+Tau).Pt(), weight);
          dRMu3Tau->Fill(Mu3.DeltaR(Tau), weight);
          invMassMu3Tau->Fill((Mu3+Tau).M(), weight);
          dRInvMassMu3Tau->Fill(Mu3.DeltaR(Tau), (Mu3+Tau).M(), weight);

          mu3Iso->Fill(Mu3Iso, weight);
          tauIsoMVA->Fill(TauIso, weight);
          tauDecayMode->Fill(TauDM, weight);

          mu3Pt->Fill(Mu3.Pt(), weight);
          mu3Eta->Fill(Mu3.Eta(), weight);
          mu3Phi->Fill(Mu3.Phi(), weight);

          tauPt->Fill(Tau.Pt(), weight);
          tauEta->Fill(Tau.Eta(), weight);
          tauPhi->Fill(Tau.Phi(), weight);
          tauMass->Fill(Tau.M(), weight);

          dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
          dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
          dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
          dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

          ptMuMuTauMuTauHad->Fill((Mu1+Mu2+Mu3+Tau).Pt(), weight);
          invMassMuMuTauMuTauHad->Fill((Mu1+Mu2+Mu3+Tau).M(), weight);
          dMMuMuTauTau->Fill(((Mu1+Mu2).M()-(Mu3+Tau).M())/(Mu1+Mu2).M(), weight);

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenMu3;
              TLorentzVector GenTauMu;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenMu3 = false;
              bool findMatchedRecGenTauMu = false;
              bool findMatchedRecGenTauHad = false;

              unsigned int indexGenMu1 = -1;
              unsigned int indexGenMu2 = -1;

              if (genMuonPt->size()>0)
              {
                  // --------- search for matched genMu1 for Mu1 --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu1.DeltaR(GenMuCand) <= smallestDR)
                      {
                          smallestDR = Mu1.DeltaR(GenMuCand);
                          findMatchedRecGenMu1 = true;
                          GenMu1 = GenMuCand;
                          indexGenMu1 = iGenMu;
                      } // end if Mu1.DeltaR(GenMuCand) <= smallestDR
                  } // end for loop on GenMu1

                  if (findMatchedRecGenMu1)
                  {
                      mu1PtVSGenMu1Pt->Fill(Mu1.Pt(), GenMu1.Pt(), weight);
                      mu1EtaVSGenMu1Eta->Fill(Mu1.Eta(), GenMu1.Eta(), weight);
                      mu1PhiVSGenMu1Phi->Fill(Mu1.Phi(), GenMu1.Phi(), weight);
                  } // end if findMatchedRecGenMu1 == true

                  // --------- search for matched genMu2 for Mu2 --------------
                  smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1)
                      {
                          smallestDR = Mu2.DeltaR(GenMuCand);
                          findMatchedRecGenMu2 = true;
                          GenMu2 = GenMuCand;
                          indexGenMu2 = iGenMu;
                      } // end if Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1
                  } // end for loop on GenMu2

                  if (findMatchedRecGenMu2)
                  {
                      mu2PtVSGenMu2Pt->Fill(Mu2.Pt(), GenMu2.Pt(), weight);
                      mu2EtaVSGenMu2Eta->Fill(Mu2.Eta(), GenMu2.Eta(), weight);
                      mu2PhiVSGenMu2Phi->Fill(Mu2.Phi(), GenMu2.Phi(), weight);
                  } // end if findMatchedRecGenMu2 == true

                  // --------- search for matched genMu3 for Mu3 --------------
                  smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu3.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1 && iGenMu != indexGenMu2)
                      {
                          smallestDR = Mu3.DeltaR(GenMuCand);
                          findMatchedRecGenMu3 = true;
                          GenMu3 = GenMuCand;
                      } // end if Mu3.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1 && iGenMu != indexGenMu2
                  } // end for loop on GenMu3

                  if (findMatchedRecGenMu3)
                  {
                      mu3PtVSGenMu3Pt->Fill(Mu3.Pt(), GenMu3.Pt(), weight);
                      mu3EtaVSGenMu3Eta->Fill(Mu3.Eta(), GenMu3.Eta(), weight);
                      mu3PhiVSGenMu3Phi->Fill(Mu3.Phi(), GenMu3.Phi(), weight);
                  } // end if findMatchedRecGenMu3 == true
              } // end if genMuonPt->size()>0

              if (genTauMuPt->size()>0)
              {
                  // --------- search for matched genTauMu for Mu3 --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenTauMu=0; iGenTauMu<genTauMuPt->size(); iGenTauMu++)
                  {
                      TLorentzVector GenTauMuCand;
                      GenTauMuCand.SetPtEtaPhiM(genTauMuPt->at(iGenTauMu), genTauMuEta->at(iGenTauMu), genTauMuPhi->at(iGenTauMu), genTauMuMass->at(iGenTauMu));
                      if (Mu3.DeltaR(GenTauMuCand) <= smallestDR)
                      {
                          smallestDR = Mu3.DeltaR(GenTauMuCand);
                          findMatchedRecGenTauMu = true;
                          GenTauMu = GenTauMuCand;
                      } // end if Mu3.DeltaR(GenTauMuCand) <= smallestDR
                  } // end for loop on GenTauMu

                  if (findMatchedRecGenTauMu)
                  {
                      mu3PtVSGenTauMuPt->Fill(Mu3.Pt(), GenTauMu.Pt(), weight);
                  } // end if findMatchedRecGenTauMu == true
              } // end if genTauMuPt->size()>0

              if (genTauHadPt->size()>0)
              {
                  // --------- search for matched genTauHad for Tau --------------
                  double smallestDR = 0.15;
                  double GenTauHadVisiblePt = 0;

                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand;
                      GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Tau.DeltaR(GenTauHadCand) <= smallestDR)
                      {
                          smallestDR = Tau.DeltaR(GenTauHadCand);
                          findMatchedRecGenTauHad = true;
                          GenTauHad = GenTauHadCand;
                          GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                      } // end if Tau.DeltaR(GenTauHad) <= smallestDR
                  } // end for loop on GenTauHad

                  if (findMatchedRecGenTauHad)
                  {
                      tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
                      tauEtaVSGenTauHadEta->Fill(Tau.Eta(), GenTauHad.Eta(), weight);
                      tauPhiVSGenTauHadPhi->Fill(Tau.Phi(), GenTauHad.Phi(), weight);
                      tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);
                  } // end if findMatchedRecGenTauHad == true
              } // end if genTauHadPt->size()>0

              if (findMatchedRecGenMu1 && findMatchedRecGenMu2)
              {
                  dRMu1Mu2VSGenMu1GenMu2->Fill(Mu1.DeltaR(Mu2), GenMu1.DeltaR(GenMu2), weight);
                  TLorentzVector Mu1Mu2 = Mu1 + Mu2;
                  TLorentzVector GenMu1Mu2 = GenMu1 + GenMu2;
                  invMassMu1Mu2VSGenMu1GenMu2->Fill(Mu1Mu2.M(), GenMu1Mu2.M(), weight);
              } // end if findMatchedRecGenMu1 && findMatchedRecGenMu2

              if (findMatchedRecGenMu3 && findMatchedRecGenTauHad)
              {
                  TLorentzVector Mu3Tau = Mu3 + Tau;
                  TLorentzVector GenMu3TauHad = GenMu3 + GenTauHad;
                  dRMu3TauVSGenMu3GenTauHad->Fill(Mu3.DeltaR(Tau), GenMu3.DeltaR(GenTauHad), weight);
                  invMassMu3TauVSGenMu3GenTauHad->Fill(Mu3Tau.M(), GenMu3TauHad.M(), weight);
              } // end if findMatchedRecGenMu3 && findMatchedRecGenTauHad

              if (findMatchedRecGenTauMu && findMatchedRecGenTauHad)
              {
                  TLorentzVector Mu3Tau = Mu3 + Tau;
                  TLorentzVector GenTauMuTauHad = GenTauMu + GenTauHad;
                  dRMu3TauVSGenTauMuGenTauHad->Fill(Mu3.DeltaR(Tau), GenTauMu.DeltaR(GenTauHad), weight);
                  invMassMu3TauVSGenTauMuGenTauHad->Fill(Mu3Tau.M(), GenTauMuTauHad.M(), weight);
              } // end if findMatchedRecGenTauMu && findMatchedRecGenTauHad
          } // end if isMC && matchRecGen

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          visMassTauTau = (Mu3+Tau).M();
          visMassMuMuTauTau = (Mu1+Mu2+Mu3+Tau).M();

          deltaRMuMu = Mu1.DeltaR(Mu2);
          deltaRTauTau = Mu3.DeltaR(Tau);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();
          Mu1DZ = Mu1Dz;

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();
          Mu2DZ = Mu2Dz;

          Tau1Pt = Mu3.Pt();
          Tau1Eta = Mu3.Eta();
          Tau1Isolation = Mu3Iso;

          Tau2Pt = Tau.Pt();
          Tau2Eta = Tau.Eta();
          Tau2DecayMode = TauDM;
          Tau2Isolation = TauIso;

          eventWeight = weight/summedWeights;
          if (isMC){nPileup = trueNInteraction;} 
          else {nPileup = recoNPrimaryVertex;} 
          TreeMuMuTauTau->Fill();
      } // end if findMu1 && findMu2 && findMuTauPair
   }// end loop for events

   outputFile->cd();

   int numberofhist = histColl.size();
   for(int i=0; i<numberofhist; i++){
       if (isMC) histColl[i]->Scale(lumiScale/summedWeights);
       histColl[i]->Write();
   } // end loop for writing all the histograms into the output file

   for(int j=0; j<numberofhist; j++){
       delete histColl[j];
   } // end loop for deleting all the histograms

   TreeMuMuTauTau->Write("TreeMuMuTauTau", TObject::kOverwrite);
   outputFile->Close();
}

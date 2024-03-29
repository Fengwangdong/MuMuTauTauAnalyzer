#define TauEffAnalyzer_cxx
#include "TauEffAnalyzer.h"
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

void TauEffAnalyzer::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if (nMaxEvents >= 0 && nMaxEvents  < nentries) nentries = nMaxEvents;
   cout << "We will run on " << nentries << " events" << endl;

   Long64_t nbytes = 0, nb = 0;

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
      TLorentzVector Ele;
      TLorentzVector Tau;
      TLorentzVector TauMuonCleaned;
      TLorentzVector TauElectronCleaned;

      float TauDM;
      float TauMuonCleanedDM;
      float TauElectronCleanedDM;

      TLorentzVector Jet;
      TLorentzVector GenMu1;
      TLorentzVector GenMu2;
      TLorentzVector GenTauMu;
      TLorentzVector GenTauEle;
      TLorentzVector GenTauHad;
      TLorentzVector GenTauHad2;

      unsigned int indexMu1 = 0;
      unsigned int indexMu2 = 0;

      // ---- prepare event weight info ----
      double weight = 1;
      weight *= genEventWeight;

      // =============================== gen muon =======================================
      int numGenMu = 0;
      for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
      {
          if (numGenMu == 0)
          {
              if (genMuonPt->at(iGenMu) < 26.0) continue;
              GenMu1.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
              numGenMu++;
              continue;
          } // end if numGenMu == 0

          if (numGenMu == 1)
          {
              if (genMuonPt->at(iGenMu) < 3.0) continue;
              GenMu2.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
              numGenMu++;
              break;
          } // end if numGenMu == 1
      } // end loop for gen muons

      // =============================== gen tau had =======================================
      int numGenTauHad = 0;
      for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
      {
          if (numGenMu < 2 || genTauHadPt->at(iGenTauHad) < 10.0 || fabs(genTauHadEta->at(iGenTauHad)) > 2.4) continue;
          if (numGenTauHad == 0)
          {
              GenTauHad.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
              GenTauHadPt->Fill(GenTauHad.Pt(), weight);
              numGenTauHad++;
              continue;
          } // end if numGenTauHad == 0

          if (numGenTauHad == 1)
          {
              GenTauHad2.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
              GenTauHad2Pt->Fill(GenTauHad2.Pt(), weight);
              dRGenTauHadGenTauHad->Fill(GenTauHad2.DeltaR(GenTauHad), weight);
              invMassGenTauHadGenTauHad->Fill((GenTauHad + GenTauHad2).M(), weight);
              dRInvMassGenTauHadGenTauHad->Fill(GenTauHad2.DeltaR(GenTauHad), (GenTauHad + GenTauHad2).M(), weight);
              numGenTauHad++;
              break;
          } // end if numGenTauHad > 0
      } // end for loop on GenTauHad

      // ========================= gen tau mu ==============================================
      int numGenTauMu = 0;
      for (unsigned int iGenTauMu=0; iGenTauMu<genTauMuPt->size(); iGenTauMu++)
      {
          if (numGenMu < 2 || genTauMuPt->at(iGenTauMu) < 3.0 || fabs(genTauMuEta->at(iGenTauMu)) > 2.4) continue;
          if (numGenTauHad == 1)
          {
              GenTauMu.SetPtEtaPhiM(genTauMuPt->at(iGenTauMu), genTauMuEta->at(iGenTauMu), genTauMuPhi->at(iGenTauMu), genTauMuMass->at(iGenTauMu));
              dRGenTauMuGenTauHad->Fill(GenTauMu.DeltaR(GenTauHad), weight);
              invMassGenTauMuGenTauHad->Fill((GenTauMu+GenTauHad).M(), weight);
              dRInvMassGenTauMuGenTauHad->Fill(GenTauMu.DeltaR(GenTauHad), (GenTauMu+GenTauHad).M(), weight);
              numGenTauMu++;
              break;
          } // end if numGenTauMu > 0
      } // end for loop on GenTauMu

      // ========================= gen tau e ==============================================
      int numGenTauEle = 0;
      for (unsigned int iGenTauEle=0; iGenTauEle<genTauElePt->size(); iGenTauEle++)
      {
          if (numGenMu < 2 || genTauElePt->at(iGenTauEle) < 10.0 || fabs(genTauEleEta->at(iGenTauEle)) > 2.4) continue;
          if (numGenTauHad == 1)
          {
              GenTauEle.SetPtEtaPhiM(genTauElePt->at(iGenTauEle), genTauEleEta->at(iGenTauEle), genTauElePhi->at(iGenTauEle), genTauEleMass->at(iGenTauEle));
              dRGenTauEleGenTauHad->Fill(GenTauEle.DeltaR(GenTauHad), weight);
              invMassGenTauEleGenTauHad->Fill((GenTauEle+GenTauHad).M(), weight);
              dRInvMassGenTauEleGenTauHad->Fill(GenTauEle.DeltaR(GenTauHad), (GenTauEle+GenTauHad).M(), weight);
              numGenTauEle++;
              break;
          } // end if numGenTauEle > 0
      } // end for loop on GenTauEle

      // ============================ reco muon ============================================
      // ---- start loop on muon candidates for mu1 ----
      bool findMu1 = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < 0.25 && passMuonID) 
          {
              Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              indexMu1 = iMuon;
              findMu1 = true;
              break;
          } // end if there is any matched Mu1 candidiate
      } // end loop for mu1

      bool findMu2 = false;
      // ---- start loop on muon candidates for mu2 ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;

          if (iMuon == indexMu1 || (recoMuonIsolation->at(iMuon) > 0.25) || !passMuonID) continue;
          if((recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)))
          {
              Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              indexMu2 = iMuon;
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      bool findMu3 = false;
      bool findMuTauMuonCleanedPair = false;
      bool findMuTauPair = false;
      // ============================ reco third muon ============================================
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;

          if (iMuon == indexMu1 || iMuon == indexMu2 || !passMuonID) continue;

          TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, tau) implementation
          Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));

          if (Mu3Cand.DeltaR(Mu1) < 0.4 || Mu3Cand.DeltaR(Mu2) < 0.4) continue;
          Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          findMu3 = true;

          float smallestDR = 0.8; // dR cut between Mu3 and tau
          bool findTauMuonCleaned = false;
          // ============================ reco tau muon cleaned ============================================
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

                  if (!passCondTauDeep) continue;
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

                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if (recoTauMuonCleanedPt->at(iTau) < 10.0) continue;
              if ((recoTauMuonCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              bool overlapMuTau = recoMuonRefToTau->at(iMuon) > 0 && recoTauMuonCleanedRefToMuon->at(iTau) > 0 && recoMuonRefToTau->at(iMuon) == recoTauMuonCleanedRefToMuon->at(iTau);

              TLorentzVector TauMuonCleanedCand;
              TauMuonCleanedCand.SetPtEtaPhiE(recoTauMuonCleanedPt->at(iTau), recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedEnergy->at(iTau));

              if ((TauMuonCleanedCand.DeltaR(Mu1) > 0.8) && (TauMuonCleanedCand.DeltaR(Mu2) > 0.8) && (TauMuonCleanedCand.DeltaR(Mu3) < smallestDR) && (recoTauMuonCleanedPDGId->at(iTau)/fabs(recoTauMuonCleanedPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && !overlapMuTau)
              {
                  TauMuonCleaned.SetPtEtaPhiE(recoTauMuonCleanedPt->at(iTau), recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedEnergy->at(iTau));
                  TauMuonCleanedDM = recoTauMuonCleanedDecayMode->at(iTau);
                  smallestDR = TauMuonCleaned.DeltaR(Mu3);
                  findTauMuonCleaned = true;
                  break;
              } // end if find tau with mu3 matched
          } // end loop for reco-tau muon cleaned

          smallestDR = 0.8; // dR cut between Mu3 and tau
          bool findTau = false;
          // ============================ reco tau standard ============================================
          for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
          {
              if (deepTauID && recoTauDeepVSjetraw->size() > 0)
              {
                  // -------------------------------------------------------------------------------
                  bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauDeepVSeLoose->at(iTau)>0;
                  bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau)>0;
                  bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauDeepVSmuLoose->at(iTau)>0;

                  bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauDeepVSeMedium->at(iTau)>0;
                  bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau)>0;
                  bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauDeepVSmuMedium->at(iTau)>0;

                  bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauDeepVSeTight->at(iTau)>0;
                  bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau)>0;
                  bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauDeepVSmuTight->at(iTau)>0;

                  bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauDeepVSeVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau)>0;
                  bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauDeepVSmuVLoose->at(iTau)>0;

                  bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauDeepVSeVTight->at(iTau)>0;
                  bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau)>0;

                  bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauDeepVSeVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau)>0;
                  
                  bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauDeepVSeVVTight->at(iTau)>0;
                  bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau)>0;

                  bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauDeepVSeVVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauDeepVSjetVVVLoose->at(iTau)>0;

                  bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
                  bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
                  // -------------------------------------------------------------------------------

                  bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
                  bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
                  bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

                  if (!passCondTauDeep) continue;
              } // end if deepTauID && recoTauDeepVSjetraw->size() > 0

              else{
                  bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
                  bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0;
                  bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0;
                  bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0;
                  bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0;
                  bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0;
                  bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0;
                  bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0;

                  bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau)>0;
                  bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau)>0; 
                  bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

                  bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau)>0;
                  bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau)>0;
                  bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau)>0; 
                  bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

                  bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
                  // -------------------------------------------------------------------------------------------------

                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if (recoTauPt->at(iTau) < 10.0) continue;
              if ((recoTauDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              bool overlapMuTau = recoMuonRefToTau->at(iMuon) > 0 && recoTauRefToMuon->at(iTau) > 0 && recoMuonRefToTau->at(iMuon) == recoTauRefToMuon->at(iTau);

              TLorentzVector TauCand;
              TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));

              if ((TauCand.DeltaR(Mu1) > 0.8) && (TauCand.DeltaR(Mu2) > 0.8) && (TauCand.DeltaR(Mu3) < smallestDR) && (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && !overlapMuTau)
              {
                  Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  TauDM = recoTauDecayMode->at(iTau);
                  smallestDR = Tau.DeltaR(Mu3);
                  findTau = true;
                  break;
              } // end if find tau with mu3 matched
          } // end loop for reco-tau standard

          if (findTauMuonCleaned) findMuTauMuonCleanedPair = true;
          if (findTau) findMuTauPair = true;
          if (findTauMuonCleaned || findTau) break;
      } // end loop for mu3

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findMu3)
      {
          mu3Pt->Fill(Mu3.Pt(), weight);
          if (numGenTauMu > 0 && Mu3.DeltaR(GenTauMu) < 0.15)
          {
              mu3PtVSGenTauMuPt->Fill(Mu3.Pt(), GenTauMu.Pt(), weight);
          }  // end if numGenTauMu > 0 && Mu3.DeltaR(GenTauMu) < 0.15
      } // end if findMu1 && findMu2 && findMu3

      if (findMu1 && findMu2 && findMuTauMuonCleanedPair)
      {
          dRMu3TauMuonCleaned->Fill(Mu3.DeltaR(TauMuonCleaned), weight);
          invMassMu3TauMuonCleaned->Fill((Mu3+TauMuonCleaned).M(), weight);
          tauMuonCleanedDecayMode->Fill(TauMuonCleanedDM, weight);
          tauMuonCleanedPt->Fill(TauMuonCleaned.Pt(), weight);
          dRInvMassMu3TauMuonCleaned->Fill(Mu3.DeltaR(TauMuonCleaned), (Mu3+TauMuonCleaned).M(), weight);

          if (numGenTauMu == 1 && numGenTauHad == 1 && Mu3.DeltaR(GenTauMu) < 0.15 && TauMuonCleaned.DeltaR(GenTauHad) < 0.15)
          {
              dRMu3TauMuonCleanedVSGenTauMuGenTauHad->Fill(Mu3.DeltaR(TauMuonCleaned), GenTauMu.DeltaR(GenTauHad), weight);
              invMassMu3TauMuonCleanedVSGenTauMuGenTauHad->Fill((Mu3+TauMuonCleaned).M(), (GenTauMu+GenTauHad).M(), weight);
              tauMuonCleanedPtVSGenTauHadPt->Fill(TauMuonCleaned.Pt(), GenTauHad.Pt(), weight);
          } // end if numGenTauMu == 1 && numGenTauHad == 1 && Mu3.DeltaR(GenTauMu) < 0.15 && TauMuonCleaned.DeltaR(GenTauHad) < 0.15
      } // end if findMu1 && findMu2 && findMuTauMuonCleanedPair

      if (findMu1 && findMu2 && findMuTauPair)
      {
          dRMu3Tau->Fill(Mu3.DeltaR(Tau), weight);
          invMassMu3Tau->Fill((Mu3+Tau).M(), weight);
          tauDecayMode->Fill(TauDM, weight);
          tauPt->Fill(Tau.Pt(), weight);
          dRInvMassMu3Tau->Fill(Mu3.DeltaR(Tau), (Mu3+Tau).M(), weight);

          if (numGenTauMu == 1 && numGenTauHad == 1 && Mu3.DeltaR(GenTauMu) < 0.15 && Tau.DeltaR(GenTauHad) < 0.15)
          {
              dRMu3TauVSGenTauMuGenTauHad->Fill(Mu3.DeltaR(Tau), GenTauMu.DeltaR(GenTauHad), weight);
              invMassMu3TauVSGenTauMuGenTauHad->Fill((Mu3+Tau).M(), (GenTauMu+GenTauHad).M(), weight);
              tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
          } // end if numGenTauMu == 1 && numGenTauHad == 1 && Mu3.DeltaR(GenTauMu) < 0.15 && Tau.DeltaR(GenTauHad) < 0.15
      } // end if findMu1 && findMu2 && findMuTauPair


      bool findEle = false;
      bool findEleTauElectronCleanedPair = false;
      bool findEleTauPair = false;
      // ============================ reco electron ============================================
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          bool condEleLoose = EleRelId == "LOOSE" && recoElectronIdLooseNoIso->at(iEle) > 0;
          bool condEleMedium = EleRelId == "MEDIUM" && recoElectronIdMediumNoIso->at(iEle) > 0;
          bool condEleTight = EleRelId == "TIGHT" && recoElectronIdTightNoIso->at(iEle) > 0;
          bool condEleNull = EleRelId != "LOOSE" && EleRelId != "MEDIUM" && EleRelId != "TIGHT";
          bool passCondEleId = condEleLoose || condEleMedium || condEleTight || condEleNull;

          if (!passCondEleId) continue;

          TLorentzVector EleCand; // prepare this variable for dR(Ele, tau) implementation
          double recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEcalTrkEnergyPostCorr->at(iEle) / recoElectronEnergy->at(iEle);
          EleCand.SetPtEtaPhiE(recoElectronPtCorr, recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));

          if (EleCand.Pt() < 7.0 || EleCand.DeltaR(Mu1) < 0.4 || EleCand.DeltaR(Mu2) < 0.4) continue;
          Ele.SetPtEtaPhiE(recoElectronPtCorr, recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
          findEle = true;

          float smallestDR = 0.8; // dR cut between Ele and tau
          bool findTauElectronCleaned = false;
          // ============================ reco tau electron cleaned ============================================
          for (unsigned int iTau=0; iTau<recoTauElectronCleanedPt->size(); iTau++)
          {
              if (deepTauID && recoTauElectronCleanedDeepVSjetraw->size() > 0)
              {
                  // -------------------------------------------------------------------------------
                  bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauElectronCleanedDeepVSeLoose->at(iTau)>0;
                  bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauElectronCleanedDeepVSjetLoose->at(iTau)>0;
                  bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauElectronCleanedDeepVSmuLoose->at(iTau)>0;

                  bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauElectronCleanedDeepVSeMedium->at(iTau)>0;
                  bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauElectronCleanedDeepVSjetMedium->at(iTau)>0;
                  bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauElectronCleanedDeepVSmuMedium->at(iTau)>0;

                  bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauElectronCleanedDeepVSeTight->at(iTau)>0;
                  bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauElectronCleanedDeepVSjetTight->at(iTau)>0;
                  bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauElectronCleanedDeepVSmuTight->at(iTau)>0;

                  bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauElectronCleanedDeepVSeVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauElectronCleanedDeepVSjetVLoose->at(iTau)>0;
                  bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauElectronCleanedDeepVSmuVLoose->at(iTau)>0;

                  bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauElectronCleanedDeepVSeVTight->at(iTau)>0;
                  bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauElectronCleanedDeepVSjetVTight->at(iTau)>0;

                  bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauElectronCleanedDeepVSeVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauElectronCleanedDeepVSjetVVLoose->at(iTau)>0;
                  
                  bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauElectronCleanedDeepVSeVVTight->at(iTau)>0;
                  bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauElectronCleanedDeepVSjetVVTight->at(iTau)>0;

                  bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauElectronCleanedDeepVSeVVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauElectronCleanedDeepVSjetVVVLoose->at(iTau)>0;

                  bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
                  bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
                  // -------------------------------------------------------------------------------

                  bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
                  bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
                  bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

                  if (!passCondTauDeep) continue;
              } // end if deepTauID && recoTauElectronCleanedDeepVSjetraw->size() > 0

              else{
                  bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauElectronCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
                  bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauElectronCleanedIsoMVAVVLoose->at(iTau)>0;
                  bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauElectronCleanedIsoMVAVLoose->at(iTau)>0;
                  bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauElectronCleanedIsoMVALoose->at(iTau)>0;
                  bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauElectronCleanedIsoMVAMedium->at(iTau)>0;
                  bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauElectronCleanedIsoMVATight->at(iTau)>0;
                  bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauElectronCleanedIsoMVAVTight->at(iTau)>0;
                  bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauElectronCleanedIsoMVAVVTight->at(iTau)>0;

                  bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauElectronCleanedAntiMuMVALoose->at(iTau)>0;
                  bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauElectronCleanedAntiMuMVATight->at(iTau)>0; 
                  bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

                  bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauElectronCleanedAntiEleMVALoose->at(iTau)>0;
                  bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauElectronCleanedAntiEleMVAMedium->at(iTau)>0;
                  bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauElectronCleanedAntiEleMVATight->at(iTau)>0; 
                  bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

                  bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
                  // -------------------------------------------------------------------------------------------------

                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if (recoTauElectronCleanedPt->at(iTau) < 10.0) continue;
              if ((recoTauElectronCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              bool overlapEleTau = recoElectronRefToTau->at(iEle) > 0 && recoTauElectronCleanedRefToElectron->at(iTau) > 0 && recoElectronRefToTau->at(iEle) == recoTauElectronCleanedRefToElectron->at(iTau);
             
              TLorentzVector TauElectronCleanedCand;
              TauElectronCleanedCand.SetPtEtaPhiE(recoTauElectronCleanedPt->at(iTau), recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedEnergy->at(iTau));

              if ((TauElectronCleanedCand.DeltaR(Mu1) > 0.8) && (TauElectronCleanedCand.DeltaR(Mu2) > 0.8) && (TauElectronCleanedCand.DeltaR(Ele) < smallestDR) && (recoTauElectronCleanedPDGId->at(iTau)/fabs(recoTauElectronCleanedPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && !overlapEleTau)
              {
                  TauElectronCleaned.SetPtEtaPhiE(recoTauElectronCleanedPt->at(iTau), recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedEnergy->at(iTau));
                  TauElectronCleanedDM = recoTauElectronCleanedDecayMode->at(iTau);
                  smallestDR = TauElectronCleaned.DeltaR(Ele);
                  findTauElectronCleaned = true;
                  break;
              } // end if find tau with electron matched
          } // end loop for reco-tau electron cleaned

          smallestDR = 0.8; // dR cut between Ele and tau
          bool findTau = false;
          // ============================ reco tau standard ============================================
          for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
          {
              if (deepTauID && recoTauDeepVSjetraw->size() > 0)
              {
                  // -------------------------------------------------------------------------------
                  bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauDeepVSeLoose->at(iTau)>0;
                  bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau)>0;
                  bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauDeepVSmuLoose->at(iTau)>0;

                  bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauDeepVSeMedium->at(iTau)>0;
                  bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau)>0;
                  bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauDeepVSmuMedium->at(iTau)>0;

                  bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauDeepVSeTight->at(iTau)>0;
                  bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau)>0;
                  bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauDeepVSmuTight->at(iTau)>0;

                  bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauDeepVSeVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau)>0;
                  bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauDeepVSmuVLoose->at(iTau)>0;

                  bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauDeepVSeVTight->at(iTau)>0;
                  bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau)>0;

                  bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauDeepVSeVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau)>0;
                  
                  bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauDeepVSeVVTight->at(iTau)>0;
                  bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau)>0;

                  bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauDeepVSeVVVLoose->at(iTau)>0;
                  bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauDeepVSjetVVVLoose->at(iTau)>0;

                  bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
                  bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
                  // -------------------------------------------------------------------------------

                  bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
                  bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
                  bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

                  if (!passCondTauDeep) continue;
              } // end if deepTauID && recoTauDeepVSjetraw->size() > 0

              else{
                  bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
                  bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0;
                  bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0;
                  bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0;
                  bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0;
                  bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0;
                  bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0;
                  bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0;

                  bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau)>0;
                  bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau)>0; 
                  bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

                  bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau)>0;
                  bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau)>0;
                  bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau)>0; 
                  bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

                  bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
                  // -------------------------------------------------------------------------------------------------

                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if (recoTauPt->at(iTau) < 10.0) continue;
              if ((recoTauDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              bool overlapEleTau = recoElectronRefToTau->at(iEle) > 0 && recoTauRefToElectron->at(iTau) > 0 && recoElectronRefToTau->at(iEle) == recoTauRefToElectron->at(iTau);
             
              TLorentzVector TauCand;
              TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));

              if ((TauCand.DeltaR(Mu1) > 0.8) && (TauCand.DeltaR(Mu2) > 0.8) && (TauCand.DeltaR(Ele) < smallestDR) && (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && !overlapEleTau)
              {
                  Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  TauDM = recoTauDecayMode->at(iTau);
                  smallestDR = Tau.DeltaR(Ele);
                  findTau = true;
                  break;
              } // end if find tau with electron matched
          } // end loop for reco-tau standard

          if (findTauElectronCleaned) findEleTauElectronCleanedPair = true;
          if (findTau) findEleTauPair = true;
          if (findTauElectronCleaned || findTau) break;
      } // end loop for electron

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findEle)
      {
          elePt->Fill(Ele.Pt(), weight);
          if (numGenTauEle > 0 && Ele.DeltaR(GenTauEle) < 0.15)
          {
              elePtVSGenTauElePt->Fill(Ele.Pt(), GenTauEle.Pt(), weight);
          }  // end if numGenTauEle > 0 && Ele.DeltaR(GenTauEle) < 0.15
      } // end if findMu1 && findMu2 && findEle

      if (findMu1 && findMu2 && findEleTauElectronCleanedPair)
      {
          dREleTauElectronCleaned->Fill(Ele.DeltaR(TauElectronCleaned), weight);
          invMassEleTauElectronCleaned->Fill((Ele+TauElectronCleaned).M(), weight);
          tauElectronCleanedDecayMode->Fill(TauElectronCleanedDM, weight);
          tauElectronCleanedPt->Fill(TauElectronCleaned.Pt(), weight);
          dRInvMassEleTauElectronCleaned->Fill(Ele.DeltaR(TauElectronCleaned), (Ele+TauElectronCleaned).M(), weight);

          if (numGenTauEle == 1 && numGenTauHad == 1 && Ele.DeltaR(GenTauEle) < 0.15 && TauElectronCleaned.DeltaR(GenTauHad) < 0.15)
          {
              dREleTauElectronCleanedVSGenTauEleGenTauHad->Fill(Ele.DeltaR(TauElectronCleaned), GenTauEle.DeltaR(GenTauHad), weight);
              invMassEleTauElectronCleanedVSGenTauEleGenTauHad->Fill((Ele+TauElectronCleaned).M(), (GenTauEle+GenTauHad).M(), weight);
              tauElectronCleanedPtVSGenTauHadPt->Fill(TauElectronCleaned.Pt(), GenTauHad.Pt(), weight);
          } // end if numGenTauEle == 1 && numGenTauHad == 1 && Ele.DeltaR(GenTauEle) < 0.15 && TauElectronCleaned.DeltaR(GenTauHad) < 0.15
      } // end if findMu1 && findMu2 && findEleTauElectronCleanedPair

      if (findMu1 && findMu2 && findEleTauPair)
      {
          dREleTau->Fill(Ele.DeltaR(Tau), weight);
          invMassEleTau->Fill((Ele+Tau).M(), weight);
          tauDecayMode->Fill(TauDM, weight);
          tauPt->Fill(Tau.Pt(), weight);
          dRInvMassEleTau->Fill(Ele.DeltaR(Tau), (Ele+Tau).M(), weight);

          if (numGenTauEle == 1 && numGenTauHad == 1 && Ele.DeltaR(GenTauEle) < 0.15 && Tau.DeltaR(GenTauHad) < 0.15)
          {
              dREleTauVSGenTauEleGenTauHad->Fill(Ele.DeltaR(Tau), GenTauEle.DeltaR(GenTauHad), weight);
              invMassEleTauVSGenTauEleGenTauHad->Fill((Ele+Tau).M(), (GenTauEle+GenTauHad).M(), weight);
              tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
          } // end if numGenTauEle == 1 && numGenTauHad == 1 && Ele.DeltaR(GenTauEle) < 0.15 && Tau.DeltaR(GenTauHad) < 0.15
      } // end if findMu1 && findMu2 && findEleTauPair


      // ============================ reco jet ============================================
      int numJets = 0;
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (numGenTauHad < 2) break;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;
          if (!passCondJetId) continue;

          if (numJets == 0 && recoJetDeepDiTauValuev1->at(iJet) < deepDiTauRawThreshold) continue;
          if (numJets == 1 && recoJetDeepDiTauValuev1->at(iJet) < 0.688) continue;

          if (numJets == 0)
          {
              Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
              if (Jet.Pt() < 10.0 || fabs(Jet.Eta()) > 2.5) continue;
              numJets++;
              continue;
          } // end if numJets == 0
          
          if (numJets == 1)
          {
              TLorentzVector Jet2;
              Jet2.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
              if (Jet2.Pt() < 10.0 || fabs(Jet2.Eta()) > 2.5) continue;
              Jet = Jet + Jet2;
              numJets++;
              break;
          } // end if numJets == 1
      } // end loop for jets containing tau candidates

      if (findMu1 && findMu2 && numJets > 0)
      {
          jetPt->Fill(Jet.Pt(), weight);
          invMassJet->Fill(Jet.M(), weight);
      } // end if numJets > 0

      if (numGenTauHad == 2 && findMu1 && findMu2 && numJets > 0 && (Jet.DeltaR(GenTauHad) < 0.15 || Jet.DeltaR(GenTauHad2) < 0.15))
      {
          invMassJetVSGenTauHadGenTauHad->Fill(Jet.M(), (GenTauHad + GenTauHad2).M(), weight);
          jetPtVSGenTauHad2Pt->Fill(Jet.Pt(), (GenTauHad + GenTauHad2).Pt(), weight);
      } // end of Jet.DeltaR(GenTauHad) < 0.15
   }// end loop for events

   outputFile->cd();

   int numberofhist = histColl.size();
   for(int i=0; i<numberofhist; i++){
       histColl[i]->Scale(lumiScale/summedWeights);
       histColl[i]->Write();
   } // end loop for writing all the histograms into the output file

   for(int j=0; j<numberofhist; j++){
       delete histColl[j];
   } // end loop for deleting all the histograms

   outputFile->Close();
}

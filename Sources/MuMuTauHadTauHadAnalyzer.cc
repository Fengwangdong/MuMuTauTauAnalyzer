#define MuMuTauHadTauHadAnalyzer_cxx
#include "MuMuTauHadTauHadAnalyzer.h"
#include "RoccoR.h"
#include "functions.h"
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

void MuMuTauHadTauHadAnalyzer::Loop()
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
      TLorentzVector Tau;
      TLorentzVector Tau2;

      float Mu1Iso;
      float Mu2Iso;
      float TauIso;
      float TauDM;
      float Tau2Iso;
      float Tau2DM;

      unsigned int indexMu1 = -1;
      unsigned int indexMu2 = -1;
      unsigned int indexJ1 = -1;
      // =============================================================================

      // ---- start loop on muon candidates for mu1 ----
      bool findMu1 = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

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
          //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

          if (iMuon == indexMu1) continue;
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
              smallestDR = Mu1.DeltaR(Mu2);
              findMu2 = true;
              indexMu2 = iMuon;
          } // end if pair candidates
      } // end loop for mu2
          
      if (!findMu2) continue;
      bool findTauTauPair = false;
      double highestPt = 0;

      // ------- veto more muons and/or electrons ---------
      bool findThirdMuon = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool passMuonID = recoMuonIdLoose->at(iMuon) > 0;
          if (iMuon == indexMu1 || iMuon == indexMu2) continue;
          if (!passMuonID) continue;

          findThirdMuon = true;
          break;
      } // end for loop on muon veto

      if (findThirdMuon) continue;

      bool findElectron = false;
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          bool passCondEleId = recoElectronIdLooseNoIso->at(iEle) > 0;
          if (!passCondEleId) continue;

          TLorentzVector EleCand;
          EleCand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));

          if ((EleCand.DeltaR(Mu1) < 0.2) || (EleCand.DeltaR(Mu2) < 0.2)) continue;
          findElectron = true;
          break;
      } // end for loop over electron veto
      
      if (findElectron) continue;

      // ------- start loop on jet (di-tau_h) candidates -------
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (boostDiTauOpt) break;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (!passCondJetId) continue;
          if (recoJetCSV->at(iJet) > 0.5426) continue; // bjet veto

          bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawThreshold) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawThreshold);
          bool condInvertDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawLowerBound);

          if ((!invertedTauIso && !condDiTauDisc) || (invertedTauIso && !condInvertDiTauDisc)) continue;

          // ------ estimate JEC systematics ------
          table TableJESunc(jecSystFile);
          double jetEnergyCorr = 1 + jetScaleSyst * (TableJESunc.getEfficiency(recoJetPt->at(iJet), recoJetEta->at(iJet)));

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);

          if (TauCand.Pt() < 30.0 || TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;
          if (TauCand.Pt() > highestPt)
          {
              Tau.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);
              TauIso = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
              highestPt = Tau.Pt();
              findTauTauPair = true;
              indexJ1 = iJet;
          } // end if highest pt
      } // end loop for jets containing tau candidates

      bool findDiTauCandJet2 = false;
      // ------- start loop on j2 candidate (complement the first jet on the di-tau_h coverage) -------
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (boostDiTauOpt) break;
          if (iJet == indexJ1) continue;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (!passCondJetId) continue;

          bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawLowerBound);
          if (!condDiTauDisc || recoJetCSV->at(iJet) > 0.5426) continue;

          // ------ estimate JEC systematics ------
          table TableJESunc(jecSystFile);
          double jetEnergyCorr = 1 + jetScaleSyst * (TableJESunc.getEfficiency(recoJetPt->at(iJet), recoJetEta->at(iJet)));

          TLorentzVector Tau2Cand;
          Tau2Cand.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);

          if (Tau2Cand.DeltaR(Mu1) < 0.8 || Tau2Cand.DeltaR(Mu2) < 0.8 || Tau2Cand.DeltaR(Tau) > 0.8 || Tau2Cand.Pt() < 30.0 || Tau2Cand.Pt() > Tau.Pt()) continue;
          Tau2.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);
          Tau2Iso = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
          findDiTauCandJet2 = true;
          break;
      } // end loop for j2

      // ------- start loop on reconstructed tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
      {
          if (!boostDiTauOpt) break;
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

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauDeepVSjetVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSeVVVLoose = recoTauDeepVSeVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSmuVLoose = recoTauDeepVSmuVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && condInvertTauDeepVSeVVVLoose && condInvertTauDeepVSmuVLoose);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
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

              bool condInvertTauMVARaw = recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
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

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
          double recoTauMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauPt->at(iTau)*tauScaleCorr, recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauMass);

          if (TauCand.Pt() < 10.0 || TauCand.DeltaR(Mu1) < 0.4 || TauCand.DeltaR(Mu2) < 0.4) continue;
          if ((recoTauDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauPt->at(iTau)*tauScaleCorr, recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauMass);
          TauIso = deepTauID ? recoTauDeepVSjetraw->at(iTau) : recoTauIsoMVArawValue->at(iTau);
          TauDM = recoTauDecayMode->at(iTau);

          //float smallestDR = 1.0; // dR cut between tau1 and tau2
          bool findTau2 = false;

          for (unsigned int iTau2=iTau+1; iTau2<recoTauPt->size(); iTau2++)
          {
              if (deepTauID && recoTauDeepVSjetraw->size() > 0)
              {
                  bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauDeepVSeLoose->at(iTau2)>0;
                  bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau2)>0;
                  bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauDeepVSmuLoose->at(iTau2)>0;

                  bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauDeepVSeMedium->at(iTau2)>0;
                  bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau2)>0;
                  bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauDeepVSmuMedium->at(iTau2)>0;

                  bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauDeepVSeTight->at(iTau2)>0;
                  bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau2)>0;
                  bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauDeepVSmuTight->at(iTau2)>0;

                  bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauDeepVSeVLoose->at(iTau2)>0;
                  bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau2)>0;
                  bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauDeepVSmuVLoose->at(iTau2)>0;

                  bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauDeepVSeVTight->at(iTau2)>0;
                  bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau2)>0;

                  bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauDeepVSeVVLoose->at(iTau2)>0;
                  bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau2)>0;
                  
                  bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauDeepVSeVVTight->at(iTau2)>0;
                  bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau2)>0;

                  bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauDeepVSeVVVLoose->at(iTau2)>0;
                  bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauDeepVSjetVVVLoose->at(iTau2)>0;

                  bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
                  bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
                  // -------------------------------------------------------------------------------

                  bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
                  bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
                  bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

                  // -------------------- inverted deep Tau ID -----------------------------
                  bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau2)<=0;
                  bool condInvertTauDeepVSjetVVVLoose = recoTauDeepVSjetVVVLoose->at(iTau2)>0;
                  bool condInvertTauDeepVSeVVVLoose = recoTauDeepVSeVVVLoose->at(iTau2)>0;
                  bool condInvertTauDeepVSmuVLoose = recoTauDeepVSmuVLoose->at(iTau2)>0;
                  // -------------------------------------------------------------------------------

                  bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && condInvertTauDeepVSeVVVLoose && condInvertTauDeepVSmuVLoose);
                  // -------------------------------------------------------------------------------

                  if ((!invertedTau2Iso && !passCondTauDeep) || (invertedTau2Iso && !passCondInvertTauDeepVSjet)) continue;
              } // end if deepTauID && recoTauDeepVSjetraw->size() > 0

              else{
                  bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau2) > tauMVAIsoRawThreshold;
                  bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau2)>0;
                  bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau2)>0;
                  bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau2)>0;
                  bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau2)>0;
                  bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau2)>0;
                  bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau2)>0;
                  bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau2)>0;

                  bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
                  // -------------------------------------------------------------------------------------------------

                  bool condInvertTauMVARaw = recoTauIsoMVArawValue->at(iTau2) > tauMVAIsoRawThreshold;
                  bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau2)<=0;
                  bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau2)<=0;
                  bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau2)<=0;
                  bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau2)<=0;
                  bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau2)<=0;
                  bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau2)<=0;
                  bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau2)<=0;

                  // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
                  bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau2)>0;
                  bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau2)>0; 
                  bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

                  bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
                  // -------------------------------------------------------------------------------------------------

                  bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau2)>0;
                  bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau2)>0;
                  bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau2)>0; 
                  bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

                  bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
                  // -------------------------------------------------------------------------------------------------

                  if ((!invertedTau2Iso && !passCondTauMVA) || (invertedTau2Iso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if ((recoTauDecayMode->at(iTau2) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              TLorentzVector Tau2Cand; // prepare this variable for dR(tau1, tau2) implementation
              Tau2Cand.SetPtEtaPhiE(recoTauPt->at(iTau2), recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauEnergy->at(iTau2));
              double recoTauMass = Tau2Cand.M();
              Tau2Cand.SetPtEtaPhiM(recoTauPt->at(iTau2)*tauScaleCorr, recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauMass);
              if ((Tau2Cand.Pt() > 10.0) && ((Tau+Tau2Cand).M() < 60.0) && (recoTauPDGId->at(iTau) == (-1) * recoTauPDGId->at(iTau2)) && (Tau2Cand.DeltaR(Mu1) > 0.4) && (Tau2Cand.DeltaR(Mu2) > 0.4))
              {
                  Tau2.SetPtEtaPhiM(recoTauPt->at(iTau2)*tauScaleCorr, recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauMass);
                  Tau2Iso = deepTauID ? recoTauDeepVSjetraw->at(iTau2) : recoTauIsoMVArawValue->at(iTau2);
                  Tau2DM = recoTauDecayMode->at(iTau2);
                  findTau2 = true;
              } // end if find tau2 with tau1 matched
          } // end loop for tau2

          if (!findTau2) continue;
          else{
              findTauTauPair = true;
              break;
          } // end if findTau2
      } // end loop for tau

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight;
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findTauTauPair)
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

          metPt->Fill(recoMET->at(0), weight);

          if (boostDiTauOpt)
          {
              ptTauTau->Fill((Tau+Tau2).Pt(), weight);
              dRTauTau->Fill(Tau.DeltaR(Tau2), weight);
              invMassTauTau->Fill((Tau+Tau2).M(), weight);
              dRInvMassTauTau->Fill(Tau.DeltaR(Tau2), (Tau+Tau2).M(), weight);

              tauIsoMVA->Fill(TauIso, weight);
              tauDecayMode->Fill(TauDM, weight);

              tau2IsoMVA->Fill(Tau2Iso, weight);
              tau2DecayMode->Fill(Tau2DM, weight);

              tauPt->Fill(Tau.Pt(), weight);
              tauEta->Fill(Tau.Eta(), weight);
              tauPhi->Fill(Tau.Phi(), weight);
              tauMass->Fill(Tau.M(), weight);

              tau2Pt->Fill(Tau2.Pt(), weight);
              tau2Eta->Fill(Tau2.Eta(), weight);
              tau2Phi->Fill(Tau2.Phi(), weight);
              tau2Mass->Fill(Tau2.M(), weight);

              dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
              dRMu1Tau2->Fill(Mu1.DeltaR(Tau2), weight);
              dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);
              dRMu2Tau2->Fill(Mu2.DeltaR(Tau2), weight);

              ptMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau+Tau2).Pt(), weight);
              invMassMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau+Tau2).M(), weight);
              dMMuMuTauTau->Fill(((Mu1+Mu2).M()-(Tau+Tau2).M())/(Mu1+Mu2).M(), weight);
          } // end if boostDiTauOpt == true

          else{
              tau2IsoMVA->Fill(TauIso, weight);
              if (findDiTauCandJet2) tau2IsoMVA->Fill(Tau2Iso, weight);

              tau2Pt->Fill((Tau+Tau2).Pt(), weight);
              tau2Eta->Fill((Tau+Tau2).Eta(), weight);
              tau2Phi->Fill((Tau+Tau2).Phi(), weight);
              tau2Mass->Fill((Tau+Tau2).M(), weight);

              dRMu1Tau2->Fill(Mu1.DeltaR(Tau+Tau2), weight);
              dRMu2Tau2->Fill(Mu2.DeltaR(Tau+Tau2), weight);

              ptMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau+Tau2).Pt(), weight);
              invMassMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau+Tau2).M(), weight);
              dMMuMuTauTau->Fill(((Mu1+Mu2).M()-(Tau+Tau2).M())/(Mu1+Mu2).M(), weight);
              invMassTauTauMet->Fill((Tau+Tau2).M(), recoMET->at(0), weight);
              invMassMuMuTauHadTauHadMet->Fill((Mu1+Mu2+Tau+Tau2).M(), recoMET->at(0), weight);
          } // end if boostDiTauOpt == false

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenTauHad1;
              TLorentzVector GenTauHad2;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenTauHad1 = false;
              bool findMatchedRecGenTauHad2 = false;

              unsigned int indexGenMu1 = -1;
              unsigned int indexGenTau1 = -1;

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
                      } // end if Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1
                  } // end for loop on GenMu2

                  if (findMatchedRecGenMu2)
                  {
                      mu2PtVSGenMu2Pt->Fill(Mu2.Pt(), GenMu2.Pt(), weight);
                      mu2EtaVSGenMu2Eta->Fill(Mu2.Eta(), GenMu2.Eta(), weight);
                      mu2PhiVSGenMu2Phi->Fill(Mu2.Phi(), GenMu2.Phi(), weight);
                  } // end if findMatchedRecGenMu2 == true
              } // end if genMuonPt->size()>0

              double GenTauHadVisiblePt = 0;
              double GenTauHad2VisiblePt = 0;

              if (genTauHadPt->size()>0)
              {
                  // --------- search for matched genTauHad1 for reco di-Tau --------------
                  double smallestDR = 0.2;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand;
                      GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Tau.DeltaR(GenTauHadCand) <= smallestDR)
                      {
                          smallestDR = Tau.DeltaR(GenTauHadCand);
                          findMatchedRecGenTauHad1 = true;
                          GenTauHad1 = GenTauHadCand;
                          if (boostDiTauOpt) GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                          indexGenTau1 = iGenTauHad;
                      } // end if Tau.DeltaR(GenTauHad) <= smallestDR
                  } // end for loop on GenTauHad1

                  // --------- search for matched genTauHad2 for reco di-Tau --------------
                  smallestDR = 0.2;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand;
                      GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (((boostDiTauOpt && Tau2.DeltaR(GenTauHadCand) <= smallestDR) || (!boostDiTauOpt && Tau.DeltaR(GenTauHadCand) <= smallestDR)) && iGenTauHad != indexGenTau1)
                      {
                          smallestDR = boostDiTauOpt ? Tau2.DeltaR(GenTauHadCand) : Tau.DeltaR(GenTauHadCand);
                          findMatchedRecGenTauHad2 = true;
                          GenTauHad2 = GenTauHadCand;
                          if (boostDiTauOpt) GenTauHad2VisiblePt = genTauHadVisPt->at(iGenTauHad);
                      } // end if Tau.DeltaR(GenTauHadCand) <= smallestDR && iGenTauHad != indexGenTau1
                  } // end for loop on GenTauHad2
              } // end if genTauHadPt->size()>0

              if (findMatchedRecGenMu1 && findMatchedRecGenMu2)
              {
                  dRMu1Mu2VSGenMu1GenMu2->Fill(Mu1.DeltaR(Mu2), GenMu1.DeltaR(GenMu2), weight);
                  TLorentzVector Mu1Mu2 = Mu1 + Mu2;
                  TLorentzVector GenMu1Mu2 = GenMu1 + GenMu2;
                  invMassMu1Mu2VSGenMu1GenMu2->Fill(Mu1Mu2.M(), GenMu1Mu2.M(), weight);
              } // end if findMatchedRecGenMu1 && findMatchedRecGenMu2

              if (findMatchedRecGenTauHad1 && findMatchedRecGenTauHad2)
              {
                  if (boostDiTauOpt)
                  {
                      tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad1.Pt(), weight);
                      tauEtaVSGenTauHadEta->Fill(Tau.Eta(), GenTauHad1.Eta(), weight);
                      tauPhiVSGenTauHadPhi->Fill(Tau.Phi(), GenTauHad1.Phi(), weight);
                      tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);

                      tau2PtVSGenTauHad2Pt->Fill(Tau2.Pt(), GenTauHad2.Pt(), weight);
                      tau2EtaVSGenTauHad2Eta->Fill(Tau2.Eta(), GenTauHad2.Eta(), weight);
                      tau2PhiVSGenTauHad2Phi->Fill(Tau2.Phi(), GenTauHad2.Phi(), weight);
                      tau2PtVSGenTauHad2VisPt->Fill(Tau2.Pt(), GenTauHad2VisiblePt, weight);

                      TLorentzVector TauTau = Tau + Tau2;
                      TLorentzVector GenTauHadTauHad = GenTauHad1 + GenTauHad2;
                      invMassTauTauVSGenTauHadGenTauHad->Fill(TauTau.M(), GenTauHadTauHad.M(), weight);
                  } // end if boostDiTauOpt == true

                  else{
                      TLorentzVector GenDiTau = GenTauHad1 + GenTauHad2;
                      tau2PtVSGenTauHad2Pt->Fill(Tau.Pt(), GenDiTau.Pt(), weight);
                      tau2EtaVSGenTauHad2Eta->Fill(Tau.Eta(), GenDiTau.Eta(), weight);
                      tau2PhiVSGenTauHad2Phi->Fill(Tau.Phi(), GenDiTau.Phi(), weight);
                      invMassTauTauVSGenTauHadGenTauHad->Fill(Tau.M(), GenDiTau.M(), weight);
                  } // end if boostDiTauOpt == false
              } // end if findMatchedRecGenTauHad1 && findMatchedRecGenTauHad2
          } // end if isMC && matchRecGen

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          deltaRMuMu = Mu1.DeltaR(Mu2);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();

          if (boostDiTauOpt)
          {
              visMassTauTau = (Tau+Tau2).M();
              visMassMuMuTauTau = (Mu1+Mu2+Tau+Tau2).M();

              deltaRTauTau = Tau.DeltaR(Tau2);

              Tau1Pt = Tau.Pt();
              Tau1Eta = Tau.Eta();
              Tau1DecayMode = TauDM;
              Tau1Isolation = TauIso;

              Tau2Pt = Tau2.Pt();
              Tau2Eta = Tau2.Eta();
              Tau2DecayMode = Tau2DM;
              Tau2Isolation = Tau2Iso;
          } // end if boostDiTauOpt == true

          else{
              visMassTauTau = (Tau+Tau2).M();
              visMassMuMuTauTau = (Mu1+Mu2+Tau+Tau2).M();

              Tau2Pt = (Tau+Tau2).Pt();
              Tau2Eta = (Tau+Tau2).Eta();
              Tau1Isolation = TauIso;
              Tau2Isolation = Tau2Iso;
          } // end if boostDiTauOpt == false

          eventWeight = weight/summedWeights;
          if (isMC){nPileup = trueNInteraction;} 
          else {nPileup = recoNPrimaryVertex;} 
          TreeMuMuTauTau->Fill();
      } // end if findMu1 && findMu2 && findTauTauPair
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

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
          } // end if pair candidates
      } // end loop for mu2
          
      if (!findMu2) continue;
      bool findTauTauPair = false;
      double highestPt = 0;

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

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;
          if (TauCand.Pt() > highestPt)
          {
              Tau.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);
              TauIso = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
              highestPt = Tau.Pt();
              findTauTauPair = true;
          } // end if highest pt
      } // end loop for jets containing tau candidates

      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauBoostedPt->size(); iTau++)
      {
          if (!boostDiTauOpt) break;
          if (deepTauID && recoTauBoostedDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauBoostedDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauBoostedDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauBoostedDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauBoostedDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauBoostedDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauBoostedDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauBoostedDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauBoostedDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauBoostedDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauBoostedDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauBoostedDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauBoostedDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauBoostedDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauBoostedDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauBoostedDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauBoostedDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauBoostedDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauBoostedDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauBoostedDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauBoostedDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauBoostedDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauBoostedDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauBoostedDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauBoostedDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauBoostedDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauBoostedDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauBoostedDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauBoostedDeepVSjetVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSeVVVLoose = recoTauBoostedDeepVSeVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSmuVLoose = recoTauBoostedDeepVSmuVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && condInvertTauDeepVSeVVVLoose && condInvertTauDeepVSmuVLoose);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauBoostedDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauBoostedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauBoostedIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauBoostedIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauBoostedIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauBoostedIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauBoostedIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauBoostedIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauBoostedIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauBoostedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauBoostedIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauBoostedIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauBoostedIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauBoostedIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauBoostedIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauBoostedIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauBoostedIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauBoostedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauBoostedAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauBoostedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauBoostedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauBoostedAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauBoostedPt->at(iTau), recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedEnergy->at(iTau));
          double recoTauBoostedMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauBoostedPt->at(iTau)*tauScaleCorr, recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedMass);

          if (TauCand.DeltaR(Mu1) < 0.4 || TauCand.DeltaR(Mu2) < 0.4) continue;
          if ((recoTauBoostedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauBoostedPt->at(iTau)*tauScaleCorr, recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedMass);
          TauIso = deepTauID ? recoTauBoostedDeepVSjetraw->at(iTau) : recoTauBoostedIsoMVArawValue->at(iTau);
          TauDM = recoTauBoostedDecayMode->at(iTau);

          float smallestDR = 1.0; // dR cut between tau1 and tau2
          bool findTau2 = false;

          for (unsigned int iTau2=iTau+1; iTau2<recoTauBoostedPt->size(); iTau2++)
          {
              //if (iTau2 == iTau) continue;
              if (deepTauID && recoTauBoostedDeepVSjetraw->size() > 0)
              {
                  // -------------------------------------------------------------------------------
                  bool passCondTauDeepVSele = recoTauBoostedDeepVSeVLoose->at(iTau2)>0;
                  bool passCondTauDeepVSjet = recoTauBoostedDeepVSjetVLoose->at(iTau2)>0;
                  bool passCondTauDeepVSmu = recoTauBoostedDeepVSmuVLoose->at(iTau2)>0;
                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;
                  // -------------------------------------------------------------------------------

                  if (!passCondTauDeep) continue;
              } // end if deepTauID && recoTauBoostedDeepVSjetraw->size() > 0

              else{
                  bool passCondTauMVA = recoTauBoostedIsoMVAVLoose->at(iTau2)>0;
                  bool passCondTauAntiMuMVA = recoTauBoostedAntiMuMVALoose->at(iTau2)>0;
                  bool passCondTauAntiEleMVA = recoTauBoostedAntiEleMVALoose->at(iTau2)>0;
                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if ((recoTauBoostedDecayMode->at(iTau2) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              TLorentzVector Tau2Cand; // prepare this variable for dR(tau1, tau2) implementation
              Tau2Cand.SetPtEtaPhiE(recoTauBoostedPt->at(iTau2), recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedEnergy->at(iTau2));
              double recoTauBoostedMass = Tau2Cand.M();
              Tau2Cand.SetPtEtaPhiM(recoTauBoostedPt->at(iTau2)*tauScaleCorr, recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedMass);
              //if ((Tau.DeltaR(Tau2Cand) < smallestDR) && (recoTauBoostedPDGId->at(iTau) == (-1) * recoTauBoostedPDGId->at(iTau2)) && ((Tau+Tau2Cand).M() < 60.0) && (Tau2Cand.DeltaR(Mu1) > 0.8) && (Tau2Cand.DeltaR(Mu2) > 0.8))
              if ((Tau.DeltaR(Tau2Cand) < smallestDR) && (recoTauBoostedPDGId->at(iTau) == (-1) * recoTauBoostedPDGId->at(iTau2)) && (Tau2Cand.DeltaR(Mu1) > 0.4) && (Tau2Cand.DeltaR(Mu2) > 0.4))
              {
                  Tau2.SetPtEtaPhiM(recoTauBoostedPt->at(iTau2)*tauScaleCorr, recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedMass);
                  Tau2Iso = deepTauID ? recoTauBoostedDeepVSjetraw->at(iTau2) : recoTauBoostedIsoMVArawValue->at(iTau2);
                  Tau2DM = recoTauBoostedDecayMode->at(iTau2);
                  smallestDR = Tau.DeltaR(Tau2);
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
          } // end if boostDiTauOpt == true

          else{
              tau2IsoMVA->Fill(TauIso, weight);

              tau2Pt->Fill(Tau.Pt(), weight);
              tau2Eta->Fill(Tau.Eta(), weight);
              tau2Phi->Fill(Tau.Phi(), weight);
              tau2Mass->Fill(Tau.M(), weight);

              dRMu1Tau2->Fill(Mu1.DeltaR(Tau), weight);
              dRMu2Tau2->Fill(Mu2.DeltaR(Tau), weight);

              ptMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau).Pt(), weight);
              invMassMuMuTauHadTauHad->Fill((Mu1+Mu2+Tau).M(), weight);
          } // end if boostDiTauOpt == false

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
              visMassTauTau = Tau.M();
              visMassMuMuTauTau = (Mu1+Mu2+Tau).M();

              Tau2Pt = Tau.Pt();
              Tau2Eta = Tau.Eta();
              Tau2Isolation = TauIso;
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

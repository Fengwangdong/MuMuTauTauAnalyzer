#define FakeMuMuTauETauHadAnalyzer_cxx
#include "FakeMuMuTauETauHadAnalyzer.h"
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

void FakeMuMuTauETauHadAnalyzer::Loop()
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

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % 1000 == 0 && jentry > 0) cout << "*** Processing #Events: " << jentry << endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      // ---- define varibles that will be used to be filled into histograms ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Ele;
      TLorentzVector Tau;

      float Mu1Iso;
      float Mu2Iso;
      float EleIso;
      float TauIso;
      float TauDM;

      unsigned int indexMu1;
      // ============================================================================

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
                  rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, 0, 0);
              } // end if isMC == true

              else{
                  rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), 0, 0);
              } // end if isMC == false (data)

              Mu1.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
              Mu1Iso = recoMuonIsolation->at(iMuon);
              indexMu1 = iMuon;
              findMu1 = true;
              break;
          } // end if there is any matched Mu1 candidiate
      } // end loop for mu1

      if (!findMu1) continue;
      float highestPt = 0;
      float invMassLowThre = diMuonMassLowThreshold;
      float invMassHighThre = diMuonMassHighThreshold;
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
          //if ((recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || !passMuonID || !passDXYDZ) continue;
          if ((recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || !passMuonID) continue;

          TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
          Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          double recoMuonMass = Mu2Cand.M();

          if (isMC)
          {
              double rng = gRandom->Rndm();
              rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, 0, 0);
          } // end if isMC == true

          else{
              rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), 0, 0);
          } // end if isMC == false (data)

          Mu2Cand.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);

          if((Mu2Cand.Pt() > highestPt) && ((Mu1+Mu2Cand).M() > invMassLowThre) && ((Mu1+Mu2Cand).M() < invMassHighThre)
                  && (recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)))
          {
              Mu2.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
              Mu2Iso = recoMuonIsolation->at(iMuon);
              highestPt = Mu2Cand.Pt();
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;
      bool findEleTauPair = false;

      // ---- search for an additional electron and tau for fake rate study ----
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
              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauElectronCleanedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauElectronCleanedAntiMuMVATight->at(iTau)>0;
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";
              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauElectronCleanedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauElectronCleanedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauElectronCleanedAntiEleMVATight->at(iTau)>0;
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight) && (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull) && (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              if (!passCondTauMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauElectronCleanedPt->at(iTau), recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedEnergy->at(iTau));

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

          if ((recoTauElectronCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;

          Tau.SetPtEtaPhiE(recoTauElectronCleanedPt->at(iTau), recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedEnergy->at(iTau));
          TauIso = deepTauID ? recoTauElectronCleanedDeepVSjetraw->at(iTau) : recoTauElectronCleanedIsoMVArawValue->at(iTau);
          TauDM = recoTauElectronCleanedDecayMode->at(iTau);

          float smallestDR = 0.8; // dR between electron and tau
          bool findEle = false;

          for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
          {
              bool condEleLoose = EleRelId == "LOOSE" && recoElectronIdLooseNoIso->at(iEle) > 0;
              bool condEleMedium = EleRelId == "MEDIUM" && recoElectronIdMediumNoIso->at(iEle) > 0;
              bool condEleTight = EleRelId == "TIGHT" && recoElectronIdTightNoIso->at(iEle) > 0;
              bool condEleNull = EleRelId != "LOOSE" && EleRelId != "MEDIUM" && EleRelId != "TIGHT";
              bool passCondEleId = condEleLoose || condEleMedium || condEleTight || condEleNull;

              if (!passCondEleId) continue;

              TLorentzVector EleCand;
              EleCand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
              bool overlapEleTau = recoElectronRefToTau->at(iEle) > 0 && recoTauElectronCleanedRefToElectron->at(iTau) > 0 && recoElectronRefToTau->at(iEle) == recoTauElectronCleanedRefToElectron->at(iTau);
              //if ((recoTauElectronCleanedPDGId->at(iTau)/fabs(recoTauElectronCleanedPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && (Tau.DeltaR(EleCand) < smallestDR) && ((Tau+EleCand).M() < 60.0) && (EleCand.DeltaR(Mu1) > 0.4) && (EleCand.DeltaR(Mu2) > 0.4) && !overlapEleTau)
              if ((recoTauElectronCleanedPDGId->at(iTau)/fabs(recoTauElectronCleanedPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && (Tau.DeltaR(EleCand) < smallestDR) && (EleCand.DeltaR(Mu1) > 0.4) && (EleCand.DeltaR(Mu2) > 0.4) && !overlapEleTau)
              {
                  Ele.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
                  EleIso = recoElectronIsolation->at(iEle);
                  smallestDR = Tau.DeltaR(Ele);
                  findEle = true;
              } // end if find electron
          } // end for loop on electrons

          if (!findEle) continue;
          else{
              findEleTauPair = true;
              break;
          } // end if findEle
      } // end for loop on tau candidates

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight;
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findEleTauPair)
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

          dREleTau->Fill(Ele.DeltaR(Tau), weight);
          invMassEleTau->Fill((Ele+Tau).M(), weight);
          dRInvMassEleTau->Fill(Ele.DeltaR(Tau), (Ele+Tau).M(), weight);

          ele1Iso->Fill(EleIso, weight);
          tauIsoMVA->Fill(TauIso, weight);
          tauDecayMode->Fill(TauDM, weight);

          ele1Pt->Fill(Ele.Pt(), weight);
          ele1Eta->Fill(Ele.Eta(), weight);
          ele1Phi->Fill(Ele.Phi(), weight);

          tauPt->Fill(Tau.Pt(), weight);
          tauEta->Fill(Tau.Eta(), weight);
          tauPhi->Fill(Tau.Phi(), weight);
          tauMass->Fill(Tau.M(), weight);

          dRMu1Ele1->Fill(Mu1.DeltaR(Ele), weight);
          dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
          dRMu2Ele1->Fill(Mu2.DeltaR(Ele), weight);
          dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC && matchRecGen)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenEle;
              TLorentzVector GenTauEle;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenEle = false;
              bool findMatchedRecGenTauEle = false;
              bool findMatchedRecGenTauHad = false;

              unsigned int indexGenMu1 = -1;

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

              if (genElectronPt->size()>0)
              {
                  // --------- search for matched genEle for Ele --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenEle=0; iGenEle<genElectronPt->size(); iGenEle++)
                  {
                      TLorentzVector GenEleCand;
                      GenEleCand.SetPtEtaPhiM(genElectronPt->at(iGenEle), genElectronEta->at(iGenEle), genElectronPhi->at(iGenEle), genElectronMass->at(iGenEle));
                      if (Ele.DeltaR(GenEleCand) <= smallestDR)
                      {
                          smallestDR = Ele.DeltaR(GenEleCand);
                          findMatchedRecGenEle = true;
                          GenEle = GenEleCand;
                      } // end if Ele.DeltaR(GenEleCand) <= smallestDR
                  } // end for loop on GenEle

                  if (findMatchedRecGenEle)
                  {
                      elePtVSGenElePt->Fill(Ele.Pt(), GenEle.Pt(), weight);
                      eleEtaVSGenEleEta->Fill(Ele.Eta(), GenEle.Eta(), weight);
                      elePhiVSGenElePhi->Fill(Ele.Phi(), GenEle.Phi(), weight);
                  } // end if findMatchedRecGenEle == true
              } // end if genElectronPt->size()>0

              if (genTauElePt->size()>0)
              {
                  // --------- search for matched genTauEle for Tau --------------
                  double smallestDR = 0.15;
                  double GenTauEleVisiblePt = 0;

                  for (unsigned int iGenTauEle=0; iGenTauEle<genTauElePt->size(); iGenTauEle++)
                  {
                      TLorentzVector GenTauEleCand;
                      GenTauEleCand.SetPtEtaPhiM(genTauElePt->at(iGenTauEle), genTauEleEta->at(iGenTauEle), genTauElePhi->at(iGenTauEle), genTauEleMass->at(iGenTauEle));
                      if (Ele.DeltaR(GenTauEleCand) <= smallestDR)
                      {
                          smallestDR = Ele.DeltaR(GenTauEleCand);
                          findMatchedRecGenTauEle = true;
                          GenTauEle = GenTauEleCand;
                          GenTauEleVisiblePt = genTauEleVisPt->at(iGenTauEle);
                      } // end if Ele.DeltaR(GenTauEleCand) <= smallestDR
                  } // end for loop on genTauEle

                  if (findMatchedRecGenTauEle)
                  {
                      elePtVSGenTauElePt->Fill(Ele.Pt(), GenTauEle.Pt(), weight);
                      elePtVSGenTauEleVisPt->Fill(Ele.Pt(), GenTauEleVisiblePt, weight);
                  } // end if findMatchedRecGenTauEle == true
              } // end if genTauElePt->size()>0

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

              if (findMatchedRecGenEle && findMatchedRecGenTauHad)
              {
                  TLorentzVector EleTau = Ele + Tau;
                  TLorentzVector GenEleTauHad = GenEle + GenTauHad;
                  dREleTauVSGenEleGenTauHad->Fill(Ele.DeltaR(Tau), GenEle.DeltaR(GenTauHad), weight);
                  invMassEleTauVSGenEleGenTauHad->Fill(EleTau.M(), GenEleTauHad.M(), weight);
              } // end if findMatchedRecGenEle && findMatchedRecGenTauHad

              if (findMatchedRecGenTauEle && findMatchedRecGenTauHad)
              {
                  TLorentzVector EleTau = Ele + Tau;
                  TLorentzVector GenTauEleTauHad = GenTauEle + GenTauHad;
                  dREleTauVSGenTauEleGenTauHad->Fill(Ele.DeltaR(Tau), GenTauEle.DeltaR(GenTauHad), weight);
                  invMassEleTauVSGenTauEleGenTauHad->Fill(EleTau.M(), GenTauEleTauHad.M(), weight);
              } // end if findMatchedRecGenTauEle && findMatchedRecGenTauHad
          } // end if isMC && matchRecGen
      } // end if findMu1 && findMu2 && findEleTauPair
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

   outputFile->Close();
}

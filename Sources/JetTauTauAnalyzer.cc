#define JetTauTauAnalyzer_cxx
#include "JetTauTauAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

void JetTauTauAnalyzer::Loop()
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
      TLorentzVector Jet1;
      TLorentzVector Jet2;
      TLorentzVector Jet3;

      unsigned int indexJ1;
      unsigned int indexJ2;
      float Jet1DCM = -1;
      float Jet2DCM = -1;
      float Jet3DCM = -1;
      // =============================================================================

      // ---- start loop on jet candidates for j1 ----
      bool findJet1 = false;
      //bool findDiTauCandJet1 = false;
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (recoJetTriggerFlag->at(iJet) != 1 || !passCondJetId || recoJetPt->at(iJet) < 600) continue;

          //bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawThreshold) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawThreshold);
          //bool condInvertDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawLowerBound);

          //if (((!invertedTauIso && condDiTauDisc) || (invertedTauIso && condInvertDiTauDisc)) && (recoJetCSV->at(iJet) < 0.5426)) 
          //{
          //    findDiTauCandJet1 = true;
          //} // end if (!invertedTauIso && condDiTauDisc) || (invertedTauIso && condInvertDiTauDisc) 

          Jet1.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          Jet1DCM = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
          indexJ1 = iJet;
          findJet1 = true;
          break;
      } // end loop for jets for j1

      if (!findJet1) continue;

      bool findDiTauCandJet2 = false;
      // ------- start loop on j2 candidate -------
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (iJet == indexJ1) continue;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (!passCondJetId || recoJetPt->at(iJet) < 30.0) continue;

          bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawThreshold) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawThreshold);
          bool condInvertDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawLowerBound);

          //if (!findDiTauCandJet1 && ((!invertedTauIso && !condDiTauDisc) || (invertedTauIso && !condInvertDiTauDisc) || recoJetCSV->at(iJet) > 0.5426)) continue;
          if ((!invertedTauIso && !condDiTauDisc) || (invertedTauIso && !condInvertDiTauDisc) || recoJetCSV->at(iJet) > 0.5426) continue;

          Jet2.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          Jet2DCM = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
          findDiTauCandJet2 = true;
          indexJ2 = iJet;
          break;
          //if (((!invertedTauIso && condDiTauDisc) || (invertedTauIso && condInvertDiTauDisc)) && (recoJetCSV->at(iJet) < 0.5426)) findDiTauCandJet2 = true;
      } // end loop for j2

      bool findDiTauCandJet3 = false;
      // ------- start loop on j3 candidate -------
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (iJet == indexJ1 || iJet == indexJ2) continue;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (!passCondJetId || recoJetPt->at(iJet) < 30.0 || recoJetPt->at(iJet) > Jet2.Pt()) continue;

          bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValuev1->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMDv1->at(iJet) > deepDiTauRawLowerBound);
          if (!condDiTauDisc || recoJetCSV->at(iJet) > 0.5426) continue;

          TLorentzVector Jet3Cand;
          Jet3Cand.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          if (Jet3Cand.DeltaR(Jet2) > 0.8) continue;

          Jet3.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          Jet3DCM = massDecorrelation ? recoJetDeepDiTauValueMDv1->at(iJet) : recoJetDeepDiTauValuev1->at(iJet);
          findDiTauCandJet3 = true;
          break;
      } // end loop for j3

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight;
      } // end if isMC == true

      // ---- fill histograms ----
      //if (findDiTauCandJet1 || findDiTauCandJet2)
      if (findDiTauCandJet2)
      {
          float MetPt = recoMET->at(0);
          float MetPhi= recoMETPhi->at(0);
          if (MetPt < 180.0 || (Jet2+Jet3).Mt() < 90.0) continue;

          // --------------- rec-gen matching for separating ZTT, DYJ, and other backgrounds and data -------------------
          if (isMC && doWhatSample == "ZTT")
          {
              TLorentzVector GenTauHad1;
              TLorentzVector GenTauHad2;

              bool findMatchedRecJetGenTauHad = false;
              // --------- search for matched genTauHad1 for recJet --------------
              double smallestDR = 0.4;
              for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
              {
                  TLorentzVector GenTauHadCand1;
                  GenTauHadCand1.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                  //bool genTau1matchWithJ1 = findDiTauCandJet1 && Jet1.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ2 = Jet2.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ3 = findDiTauCandJet3 && Jet3.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ23 = genTau1matchWithJ2 || genTau1matchWithJ3;
                  //if (!genTau1matchWithJ1 && !genTau1matchWithJ2) continue;
                  if (!genTau1matchWithJ23) continue;

                  // --------- search for matched genTauHad2 for recJet --------------
                  for (unsigned int iGenTauHad2=iGenTauHad+1; iGenTauHad2<genTauHadPt->size(); iGenTauHad2++)
                  {
                      TLorentzVector GenTauHadCand2;
                      GenTauHadCand2.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad2), genTauHadEta->at(iGenTauHad2), genTauHadPhi->at(iGenTauHad2), genTauHadMass->at(iGenTauHad2));

                      //bool genTau2matchWithJ1 = findDiTauCandJet1 && Jet1.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ2 = Jet2.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ3 = findDiTauCandJet3 && Jet3.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ23 = genTau2matchWithJ2 || genTau2matchWithJ3;
                      //if (!genTau2matchWithJ1 && !genTau2matchWithJ2) continue;
                      //if ((genTau1matchWithJ1 && genTau2matchWithJ1) || (genTau1matchWithJ2 && genTau2matchWithJ2))
                      if (genTau1matchWithJ23 && genTau2matchWithJ23)
                      {
                          GenTauHad2 = GenTauHadCand2;
                          findMatchedRecJetGenTauHad = true;
                          break;
                      } // end if genTau1matchWithJ2 && genTau2matchWithJ2
                  } // end for loop on the second genTau

                  if (findMatchedRecJetGenTauHad)
                  {
                      GenTauHad1 = GenTauHadCand1;
                      break;
                  } // end if findMatchedRecJetGenTauHad == true
              } // end for loop on GenTauHad

              if (findMatchedRecJetGenTauHad)
              {
                  Jet1Pt->Fill(Jet1.Pt(), weight);
                  Jet1Eta->Fill(Jet1.Eta(), weight);
                  Jet1Phi->Fill(Jet1.Phi(), weight);
                  Jet1Mass->Fill(Jet1.M(), weight);
                  Jet1Disc->Fill(Jet1DCM, weight);

                  Jet2Pt->Fill((Jet2+Jet3).Pt(), weight);
                  Jet2Eta->Fill((Jet2+Jet3).Eta(), weight);
                  Jet2Phi->Fill((Jet2+Jet3).Phi(), weight);
                  Jet2Mass->Fill((Jet2+Jet3).M(), weight);
                  Jet2Mt->Fill((Jet2+Jet3).Mt(), weight);
                  Jet2Disc->Fill(Jet2DCM, weight);
                  Jet2Disc->Fill(Jet3DCM, weight);

                  dRJet1Jet2->Fill(Jet1.DeltaR(Jet2+Jet3), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  Jet1MassDisc->Fill(Jet1.M(), Jet1DCM, weight);
                  Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet2DCM, weight);
                  Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet3DCM, weight);

                  invMassGenTauHadGenTauHad->Fill((GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet1VSGenTauHadGenTauHad->Fill(Jet1.M(), (GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet2VSGenTauHadGenTauHad->Fill((Jet2+Jet3).M(), (GenTauHad1+GenTauHad2).M(), weight);
              } // end if findMatchedRecJetGenTauHad == true
          } // end if isMC && doWhatSample == "ZTT"

          if (isMC && doWhatSample == "DYJ")
          {
              TLorentzVector GenTauHad1;
              TLorentzVector GenTauHad2;

              bool findMatchedRecJetGenTauHad = false;
              // --------- search for matched genTauHad1 for recJet --------------
              double smallestDR = 0.4;
              for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
              {
                  TLorentzVector GenTauHadCand1;
                  GenTauHadCand1.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                  //bool genTau1matchWithJ1 = findDiTauCandJet1 && Jet1.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ2 = Jet2.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ3 = findDiTauCandJet3 && Jet3.DeltaR(GenTauHadCand1) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23;
                  bool genTau1matchWithJ23 = genTau1matchWithJ2 || genTau1matchWithJ3;
                  //if (!genTau1matchWithJ1 && !genTau1matchWithJ2) continue;
                  if (!genTau1matchWithJ23) continue;

                  // --------- search for matched genTauHad2 for recJet --------------
                  for (unsigned int iGenTauHad2=iGenTauHad+1; iGenTauHad2<genTauHadPt->size(); iGenTauHad2++)
                  {
                      TLorentzVector GenTauHadCand2;
                      GenTauHadCand2.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad2), genTauHadEta->at(iGenTauHad2), genTauHadPhi->at(iGenTauHad2), genTauHadMass->at(iGenTauHad2));

                      //bool genTau2matchWithJ1 = findDiTauCandJet1 && Jet1.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ2 = Jet2.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ3 = findDiTauCandJet3 && Jet3.DeltaR(GenTauHadCand2) < smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad2)) == 23;
                      bool genTau2matchWithJ23 = genTau2matchWithJ2 || genTau2matchWithJ3;
                      //if (!genTau2matchWithJ1 && !genTau2matchWithJ2) continue;
                      //if ((genTau1matchWithJ1 && genTau2matchWithJ1) || (genTau1matchWithJ2 && genTau2matchWithJ2))
                      if (genTau1matchWithJ23 && genTau2matchWithJ23)
                      {
                          findMatchedRecJetGenTauHad = true;
                          break;
                      } // end if genTau1matchWithJ2 && genTau2matchWithJ2
                  } // end for loop on the second genTau

                  if (findMatchedRecJetGenTauHad) break;
              } // end for loop on GenTauHad

              if (!findMatchedRecJetGenTauHad)
              {
                  Jet1Pt->Fill(Jet1.Pt(), weight);
                  Jet1Eta->Fill(Jet1.Eta(), weight);
                  Jet1Phi->Fill(Jet1.Phi(), weight);
                  Jet1Mass->Fill(Jet1.M(), weight);
                  Jet1Disc->Fill(Jet1DCM, weight);

                  Jet2Pt->Fill((Jet2+Jet3).Pt(), weight);
                  Jet2Eta->Fill((Jet2+Jet3).Eta(), weight);
                  Jet2Phi->Fill((Jet2+Jet3).Phi(), weight);
                  Jet2Mass->Fill((Jet2+Jet3).M(), weight);
                  Jet2Mt->Fill((Jet2+Jet3).Mt(), weight);
                  Jet2Disc->Fill(Jet2DCM, weight);
                  Jet2Disc->Fill(Jet3DCM, weight);

                  dRJet1Jet2->Fill(Jet1.DeltaR(Jet2+Jet3), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  Jet1MassDisc->Fill(Jet1.M(), Jet1DCM, weight);
                  Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet2DCM, weight);
                  Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet3DCM, weight);

                  smallestDR = 0.4;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand1;
                      GenTauHadCand1.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Jet1.DeltaR(GenTauHadCand1) < smallestDR || (Jet2+Jet3).DeltaR(GenTauHadCand1) < smallestDR)
                      {
                          GenTauHad1 = GenTauHadCand1;
                      } // end if smallestDR for GenTauHad1
                      for (unsigned int iGenTauHad2=iGenTauHad+1; iGenTauHad2<genTauHadPt->size(); iGenTauHad2++)
                      {
                          TLorentzVector GenTauHadCand2;
                          GenTauHadCand2.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad2), genTauHadEta->at(iGenTauHad2), genTauHadPhi->at(iGenTauHad2), genTauHadMass->at(iGenTauHad2));
                          if (Jet1.DeltaR(GenTauHadCand2) < smallestDR || (Jet2+Jet3).DeltaR(GenTauHadCand2) < smallestDR)
                          {
                              GenTauHad2 = GenTauHadCand2;
                          } // end if smallestDR for GenTauHad2
                      } // end if loop on iGenTauHad2
                  } // end if loop on iGenTauHad

                  invMassGenTauHadGenTauHad->Fill((GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet1VSGenTauHadGenTauHad->Fill(Jet1.M(), (GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet2VSGenTauHadGenTauHad->Fill((Jet2+Jet3).M(), (GenTauHad1+GenTauHad2).M(), weight);
              } // end if findMatchedRecJetGenTauHad == false
          } // end if isMC && doWhatSample == "DYJ"

          if (doWhatSample != "ZTT" && doWhatSample != "DYJ")
          {
              TLorentzVector GenTauHad1;
              TLorentzVector GenTauHad2;

              Jet1Pt->Fill(Jet1.Pt(), weight);
              Jet1Eta->Fill(Jet1.Eta(), weight);
              Jet1Phi->Fill(Jet1.Phi(), weight);
              Jet1Mass->Fill(Jet1.M(), weight);
              Jet1Disc->Fill(Jet1DCM, weight);

              Jet2Pt->Fill((Jet2+Jet3).Pt(), weight);
              Jet2Eta->Fill((Jet2+Jet3).Eta(), weight);
              Jet2Phi->Fill((Jet2+Jet3).Phi(), weight);
              Jet2Mass->Fill((Jet2+Jet3).M(), weight);
              Jet2Mt->Fill((Jet2+Jet3).Mt(), weight);
              Jet2Disc->Fill(Jet2DCM, weight);
              Jet2Disc->Fill(Jet3DCM, weight);

              dRJet1Jet2->Fill(Jet1.DeltaR(Jet2+Jet3), weight);

              metPt->Fill(MetPt, weight);
              metPhi->Fill(MetPhi, weight);

              Jet1MassDisc->Fill(Jet1.M(), Jet1DCM, weight);
              Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet2DCM, weight);
              Jet2MassDisc->Fill((Jet2+Jet3).M(), Jet3DCM, weight);

              if (isMC)
              {
                  double smallestDR = 0.4;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand1;
                      GenTauHadCand1.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Jet1.DeltaR(GenTauHadCand1) < smallestDR || (Jet2+Jet3).DeltaR(GenTauHadCand1) < smallestDR)
                      {
                          GenTauHad1 = GenTauHadCand1;
                      } // end if smallestDR for GenTauHad1
                      for (unsigned int iGenTauHad2=iGenTauHad+1; iGenTauHad2<genTauHadPt->size(); iGenTauHad2++)
                      {
                          TLorentzVector GenTauHadCand2;
                          GenTauHadCand2.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad2), genTauHadEta->at(iGenTauHad2), genTauHadPhi->at(iGenTauHad2), genTauHadMass->at(iGenTauHad2));
                          if (Jet1.DeltaR(GenTauHadCand2) < smallestDR || (Jet2+Jet3).DeltaR(GenTauHadCand2) < smallestDR)
                          {
                              GenTauHad2 = GenTauHadCand2;
                          } // end if smallestDR for GenTauHad2
                      } // end if loop on iGenTauHad2
                  } // end if loop on iGenTauHad

                  invMassGenTauHadGenTauHad->Fill((GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet1VSGenTauHadGenTauHad->Fill(Jet1.M(), (GenTauHad1+GenTauHad2).M(), weight);
                  invMassJet2VSGenTauHadGenTauHad->Fill((Jet2+Jet3).M(), (GenTauHad1+GenTauHad2).M(), weight);
              } // end if isMC == true
          } // end if doWhatSample != "ZTT" && doWhatSample != "DYJ"
      } // end if findDiTauCandJet2
   } // end for loop on events

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

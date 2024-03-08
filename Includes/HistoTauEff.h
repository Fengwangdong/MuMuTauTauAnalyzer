#ifndef _HistoTauEff_h_
#define _HistoTauEff_h_

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class HistoTauEff{

    public:

        vector<TH1*> histColl;

        TH1D* newTH1D(string, string, int, double*);
        TH1D* newTH1D(string, string, int, double, double);
        TH1D* newTH1D(string, string, vector<double>&);

        TH2D* newTH2D(string, string, string, int, double*, int, double*);
        TH2D* newTH2D(string, string, string, int, double*, int, double, double);
        TH2D* newTH2D(string, string, string, int, double, double, int, double*);
        TH2D* newTH2D(string, string, string, int, double, double, int, double, double);

        HistoTauEff();
        ~HistoTauEff();

        // ------ reconstructed object histograms ------
        TH1D* dRMu3Tau;
        TH1D* dRMu3TauMuonCleaned;
        TH1D* dREleTau;
        TH1D* dREleTauElectronCleaned;

        TH1D* invMassMu3Tau;
        TH1D* invMassMu3TauMuonCleaned;
        TH1D* invMassEleTau;
        TH1D* invMassEleTauElectronCleaned;
        TH1D* invMassJet;

        TH1D* mu3Pt; // NOTE: this histogram is filled with AND without a requirement of tau_h
        TH1D* elePt; // NOTE: this histogram is filled with AND without a requirement of tau_h
        TH1D* tauPt;  // NOTE: tau here and below is for standard reconstructed tau in tau_mu + tau_h channel
        TH1D* tau2Pt; // NOTE: tau2 here and below is for standard reconstructed tau in tau_e + tau_h channel
        TH1D* tauMuonCleanedPt;
        TH1D* tauElectronCleanedPt;
        TH1D* tauDecayMode;
        TH1D* tau2DecayMode;
        TH1D* tauMuonCleanedDecayMode;
        TH1D* tauElectronCleanedDecayMode;

        TH1D* jetPt;

        TH2D* dRInvMassMu3Tau;
        TH2D* dRInvMassMu3TauMuonCleaned;
        TH2D* dRInvMassEleTau;
        TH2D* dRInvMassEleTauElectronCleaned;

        // ------ generated object histograms ------
        TH1D* dRGenTauMuGenTauHad;
        TH1D* dRGenTauEleGenTauHad;
        TH1D* dRGenTauHadGenTauHad;

        TH1D* invMassGenTauMuGenTauHad;
        TH1D* invMassGenTauEleGenTauHad;
        TH1D* invMassGenTauHadGenTauHad;

        TH1D* GenTauHadPt;
        TH1D* GenTauHad2Pt;

        TH2D* dRInvMassGenTauMuGenTauHad;
        TH2D* dRInvMassGenTauEleGenTauHad;
        TH2D* dRInvMassGenTauHadGenTauHad;

        // ------ reco-gen response histograms ------
        TH2D* dRMu3TauVSGenTauMuGenTauHad;
        TH2D* dRMu3TauMuonCleanedVSGenTauMuGenTauHad;
        TH2D* dREleTauVSGenTauEleGenTauHad;
        TH2D* dREleTauElectronCleanedVSGenTauEleGenTauHad;

        TH2D* invMassMu3TauVSGenTauMuGenTauHad;
        TH2D* invMassMu3TauMuonCleanedVSGenTauMuGenTauHad;
        TH2D* invMassEleTauVSGenTauEleGenTauHad;
        TH2D* invMassEleTauElectronCleanedVSGenTauEleGenTauHad;
        TH2D* invMassJetVSGenTauHadGenTauHad;

        TH2D* mu3PtVSGenTauMuPt;
        TH2D* elePtVSGenTauElePt;
        TH2D* tauPtVSGenTauHadPt; // NOTE: tau here is for standard reconstructed tau in tau_mu + tau_h channel
        TH2D* tau2PtVSGenTauHadPt; // NOTE: tau2 here is for standard reconstructed tau in tau_e + tau_h channel
        TH2D* tauMuonCleanedPtVSGenTauHadPt;
        TH2D* tauElectronCleanedPtVSGenTauHadPt;
        TH2D* jetPtVSGenTauHad2Pt;
};

#endif

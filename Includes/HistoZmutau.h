#ifndef _HistoZmutau_h_
#define _HistoZmutau_h_

#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class HistoZmutau{

    public:

        vector<TH1*> histColl;

        TH1D* newTH1D(string, string, int, double*);
        TH1D* newTH1D(string, string, int, double, double);
        TH1D* newTH1D(string, string, vector<double>&);

        TH2D* newTH2D(string, string, string, int, double*, int, double*);
        TH2D* newTH2D(string, string, string, int, double*, int, double, double);
        TH2D* newTH2D(string, string, string, int, double, double, int, double*);
        TH2D* newTH2D(string, string, string, int, double, double, int, double, double);

        HistoZmutau();
        ~HistoZmutau();

        TH1D* nMatchedMuTauPair;
        TH1D* nUnMatchedMu;
        TH1D* nUnMatchedTau;

        TH1D* dRMuTau;
        TH1D* invMassMuTau;
        TH1D* ptMuTau;
        TH1D* mtMuMet;
        TH1D* pzeta;

        TH1D* unMatchedMuPt;
        TH1D* unMatchedMuEta;
        TH1D* unMatchedMuPhi;
        TH1D* unMatchedMuIso;

        TH1D* unMatchedTauPt;
        TH1D* unMatchedTauEta;
        TH1D* unMatchedTauPhi;
        TH1D* unMatchedTauIsoMVA;
        TH1D* unMatchedTauDecayMode;

        TH1D* muPt;
        TH1D* muEta;
        TH1D* muPhi;
        
        TH1D* tauPt;
        TH1D* tauEta;
        TH1D* tauPhi;
        TH1D* tauMass;
        TH1D* tauDecayMode;
        TH1D* tauIsoMVA;

        TH1D* metPt;
        TH1D* metPhi;

        TH2D* dRInvMassMuTau;
};

#endif
#ifndef _HistoJettautau_h_
#define _HistoJettautau_h_

#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class HistoJettautau{

    public:

        vector<TH1*> histColl;

        TH1D* newTH1D(string, string, int, double*);
        TH1D* newTH1D(string, string, int, double, double);
        TH1D* newTH1D(string, string, vector<double>&);

        TH2D* newTH2D(string, string, string, int, double*, int, double*);
        TH2D* newTH2D(string, string, string, int, double*, int, double, double);
        TH2D* newTH2D(string, string, string, int, double, double, int, double*);
        TH2D* newTH2D(string, string, string, int, double, double, int, double, double);

        HistoJettautau();
        ~HistoJettautau();

        TH1D* Jet1Pt;
        TH1D* Jet1Eta;
        TH1D* Jet1Phi;
        TH1D* Jet1Mass;
        TH1D* Jet1Disc;

        TH1D* Jet2Pt;
        TH1D* Jet2Eta;
        TH1D* Jet2Phi;
        TH1D* Jet2Mass;
        TH1D* Jet2Mt;
        TH1D* Jet2Disc;

        TH1D* metPt;
        TH1D* metPhi;

        TH1D* dRJet1Jet2;

        TH2D* Jet1MassDisc;
        TH2D* Jet2MassDisc;

        // ------ reco-gen response histograms ------
        TH1D* invMassGenTauHadGenTauHad;
        TH2D* invMassJet1VSGenTauHadGenTauHad;
        TH2D* invMassJet2VSGenTauHadGenTauHad;
};

#endif

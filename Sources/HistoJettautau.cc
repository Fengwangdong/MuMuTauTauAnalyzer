#include <TH1D.h>
#include "HistoJettautau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

// ---------- customize the axis settings of TH1D and TH2D ----------------
TH1D* HistoJettautau::newTH1D(string name, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoJettautau::newTH1D(string name, string xTitle, vector<double>& xBinsVect)
{
    int nBins = xBinsVect.size()-1;
    double *xBins = new double[xBinsVect.size()];
    std::copy(xBinsVect.begin(), xBinsVect.end(), xBins);
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    delete [] xBins;
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoJettautau::newTH1D(string name, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoJettautau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double *yBinsY){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yBinsY);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoJettautau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoJettautau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double *yBins){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoJettautau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

// --------------- customize the binning of output histograms -----------------
HistoJettautau::HistoJettautau(){

    double jetPtBin [] = {20, 30, 50, 80, 120, 170, 230, 300, 380, 500, 640, 800, 980, 1180, 1400};
    double metPtBin [] = {10, 20, 30, 50, 80, 120, 170, 230, 300, 380, 500, 640, 800, 980, 1180, 1400};

    int NBinsJetPt = sizeof(jetPtBin)/sizeof(jetPtBin[0])-1;
    int NBinsMetPt = sizeof(metPtBin)/sizeof(metPtBin[0])-1;

    dRJet1Jet2 = newTH1D("dRJet1Jet2", "#DeltaR(j_{1}j_{2})", 25, 0, 5.0);

    Jet1Pt = newTH1D("Jet1Pt", "p_{T}(j_{1}) [GeV]", NBinsJetPt, jetPtBin);
    Jet1Eta = newTH1D("Jet1Eta", "#eta(j_{1})", 25, -2.5, 2.5);
    Jet1Phi = newTH1D("Jet1Phi", "#phi(j_{1})", 20, -2.5, 2.5);
    Jet1Mass = newTH1D("Jet1Mass", "M(j_{1}) [GeV]", 25, 5, 105);
    Jet1Disc = newTH1D("Jet1Disc", "Disc(j_{1})", 20, 0, 1);

    Jet2Pt = newTH1D("Jet2Pt", "p_{T}(j_{2}) [GeV]", NBinsJetPt, jetPtBin);
    Jet2Eta = newTH1D("Jet2Eta", "#eta(j_{2})", 25, -2.5, 2.5);
    Jet2Phi = newTH1D("Jet2Phi", "#phi(j_{2})", 20, -2.5, 2.5);
    Jet2Mass = newTH1D("Jet2Mass", "M(j_{2}) [GeV]", 25, 5, 105);
    Jet2Disc = newTH1D("Jet2Disc", "Disc(j_{2})", 20, 0, 1);

    metPt = newTH1D("metPt", "#slash{E_{T}} [GeV]", NBinsMetPt, metPtBin);
    metPhi = newTH1D("metPhi", "#phi(#slash{E_{T}})", 20, -2.5, 2.5);

    Jet1MassDisc = newTH2D("Jet1MassDisc", "M(j_{1}) [GeV]", "Disc(j_{1})", 25, 5, 105, 20, 0, 1);
    Jet2MassDisc = newTH2D("Jet2MassDisc", "M(j_{2}) [GeV]", "Disc(j_{2})", 25, 5, 105, 20, 0, 1);

    // -------------- reco-gen response histograms ------------------
    invMassJet1VSGenTauHadGenTauHad = newTH2D("invMassJet1VSGenTauHadGenTauHad", "M(j_{1})[GeV]", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 25, 5, 105, 25, 10, 160);
    invMassJet2VSGenTauHadGenTauHad = newTH2D("invMassJet2VSGenTauHadGenTauHad", "M(j_{2})[GeV]", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 25, 5, 105, 25, 10, 160);
    invMassGenTauHadGenTauHad = newTH1D("invMassGenTauHadGenTauHad", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 25, 10, 160);
}

HistoJettautau::~HistoJettautau()
{}

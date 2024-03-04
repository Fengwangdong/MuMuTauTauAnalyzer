#include <TH1D.h>
#include "HistoTauEff.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

// ---------- customize the axis settings of TH1D and TH2D ----------------
TH1D* HistoTauEff::newTH1D(string name, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoTauEff::newTH1D(string name, string xTitle, vector<double>& xBinsVect)
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

TH1D* HistoTauEff::newTH1D(string name, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoTauEff::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double *yBinsY){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yBinsY);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoTauEff::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoTauEff::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double *yBins){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoTauEff::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

// --------------- customize the binning of output histograms -----------------
HistoTauEff::HistoTauEff(){

    double tauPtBin [] = {10, 20, 30, 50, 100, 200};
    double tau2PtBin [] = {10, 20, 30, 50, 80, 120, 170, 230, 300, 380, 500, 640, 800, 980, 1180, 1400};

    int NBinsTauPt = sizeof(tauPtBin)/sizeof(tauPtBin[0])-1;
    int NBinsTau2Pt = sizeof(tau2PtBin)/sizeof(tau2PtBin[0])-1;

    // ------ reconstructed object histograms ------
    dRMu3Tau = newTH1D("dRMu3Tau", "#DeltaR(#mu#tau)", 30, 0, 3);
    dRMu3TauMuonCleaned = newTH1D("dRMu3TauMuonCleaned", "#DeltaR(#mu#tau)", 30, 0, 3);
    dREleTau = newTH1D("dREleTau", "#DeltaR(e#tau)", 30, 0, 3);
    dREleTauElectronCleaned = newTH1D("dREleTauElectronCleaned", "#DeltaR(e#tau)", 30, 0, 3);

    invMassMu3Tau = newTH1D("invMassMu3Tau", "M(#mu#tau)[GeV]", 25, 0, 50);
    invMassMu3TauMuonCleaned = newTH1D("invMassMu3TauMuonCleaned", "M(#mu#tau)[GeV]", 25, 0, 50);
    invMassEleTau = newTH1D("invMassEleTau", "M(e#tau)[GeV]", 25, 0, 50);
    invMassEleTauElectronCleaned = newTH1D("invMassEleTauElectronCleaned", "M(e#tau)[GeV]", 25, 0, 50);
    invMassJet = newTH1D("invMassJet", "M(j)[GeV]", 25, 0, 50);

    tauPt = newTH1D("tauPt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tau2Pt = newTH1D("tau2Pt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tauMuonCleanedPt = newTH1D("tauMuonCleanedPt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tauElectronCleanedPt = newTH1D("tauElectronCleanedPt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tauDecayMode = newTH1D("tauDecayMode", "DecayMode(#tau)", 12, 0, 12);
    tau2DecayMode = newTH1D("tau2DecayMode", "DecayMode(#tau)", 12, 0, 12);
    tauMuonCleanedDecayMode = newTH1D("tauMuonCleanedDecayMode", "DecayMode(#tau)", 12, 0, 12);
    tauElectronCleanedDecayMode = newTH1D("tauElectronCleanedDecayMode", "DecayMode(#tau)", 12, 0, 12);

    jetPt = newTH1D("jetPt", "p_{T}(j) [GeV]", NBinsTau2Pt, tau2PtBin);

    dRInvMassMu3Tau = newTH2D("dRInvMassMu3Tau", "#DeltaR(#mu#tau)", "M(#mu#tau)[GeV]", 30, 0, 3, 25, 0, 50);
    dRInvMassMu3TauMuonCleaned = newTH2D("dRInvMassMu3TauMuonCleaned", "#DeltaR(#mu#tau)", "M(#mu#tau)[GeV]", 30, 0, 3, 25, 0, 50);
    dRInvMassEleTau = newTH2D("dRInvMassEleTau", "#DeltaR(e#tau)", "M(e#tau)[GeV]", 30, 0, 3, 25, 0, 50);
    dRInvMassEleTauElectronCleaned = newTH2D("dRInvMassEleTauElectronCleaned", "#DeltaR(e#tau)", "M(e#tau)[GeV]", 30, 0, 3, 25, 0, 50);

    // ------ generated object histograms ------
    dRGenTauMuGenTauHad = newTH1D("dRGenTauMuGenTauHad", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", 30, 0, 3);
    dRGenTauEleGenTauHad = newTH1D("dRGenTauEleGenTauHad", "#DeltaR(#tau_{e}^{gen}#tau_{h}^{gen})", 30, 0, 3);
    dRGenTauHadGenTauHad = newTH1D("dRGenTauHadGenTauHad", "#DeltaR(#tau_{h}^{gen}#tau_{h}^{gen})", 30, 0, 3);

    invMassGenTauMuGenTauHad = newTH1D("invMassGenTauMuGenTauHad", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50);
    invMassGenTauEleGenTauHad = newTH1D("invMassGenTauEleGenTauHad", "M(#tau_{e}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50);
    invMassGenTauHadGenTauHad = newTH1D("invMassGenTauHadGenTauHad", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50);

    GenTauHadPt = newTH1D("GenTauHadPt", "p_{T}(#tau_{h}^{gen}) [GeV]", NBinsTauPt, tauPtBin);
    GenTauHad2Pt = newTH1D("GenTauHad2Pt", "p_{T}(#tau_{h}^{gen}) [GeV]", NBinsTauPt, tauPtBin);

    dRInvMassGenTauMuGenTauHad = newTH2D("dRInvMassGenTauMuGenTauHad", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 30, 0, 3, 25, 0, 50);
    dRInvMassGenTauEleGenTauHad = newTH2D("dRInvMassGenTauEleGenTauHad", "#DeltaR(#tau_{e}^{gen}#tau_{h}^{gen})", "M(#tau_{e}^{gen}#tau_{h}^{gen})[GeV]", 30, 0, 3, 25, 0, 50);
    dRInvMassGenTauHadGenTauHad = newTH2D("dRInvMassGenTauHadGenTauHad", "#DeltaR(#tau_{h}^{gen}#tau_{h}^{gen})", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 30, 0, 3, 25, 0, 50);

    // -------------- reco-gen response histograms ------------------
    dRMu3TauVSGenTauMuGenTauHad = newTH2D("dRMu3TauVSGenTauMuGenTauHad", "#DeltaR(#mu^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", 30, 0, 3, 30, 0, 3);
    dRMu3TauMuonCleanedVSGenTauMuGenTauHad = newTH2D("dRMu3TauMuonCleanedVSGenTauMuGenTauHad", "#DeltaR(#mu^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", 30, 0, 3, 30, 0, 3);
    dREleTauVSGenTauEleGenTauHad = newTH2D("dREleTauVSGenTauEleGenTauHad", "#DeltaR(e^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{e}^{gen}#tau_{h}^{gen})", 30, 0, 3, 30, 0, 3);
    dREleTauElectronCleanedVSGenTauEleGenTauHad = newTH2D("dREleTauElectronCleanedVSGenTauEleGenTauHad", "#DeltaR(e^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{e}^{gen}#tau_{h}^{gen})", 30, 0, 3, 30, 0, 3);

    invMassMu3TauVSGenTauMuGenTauHad = newTH2D("invMassMu3TauVSGenTauMuGenTauHad", "M(#mu^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50, 25, 0, 50);
    invMassMu3TauMuonCleanedVSGenTauMuGenTauHad = newTH2D("invMassMu3TauMuonCleanedVSGenTauMuGenTauHad", "M(#mu^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50, 25, 0, 50);
    invMassEleTauVSGenTauEleGenTauHad = newTH2D("invMassEleTauVSGenTauEleGenTauHad", "M(e^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{e}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50, 25, 0, 50);
    invMassEleTauElectronCleanedVSGenTauEleGenTauHad = newTH2D("invMassEleTauElectronCleanedVSGenTauEleGenTauHad", "M(e^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{e}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50, 25, 0, 50);
    invMassJetVSGenTauHadGenTauHad = newTH2D("invMassJetVSGenTauHadGenTauHad", "M(j^{rec})[GeV]", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 50, 25, 0, 50);

    tauPtVSGenTauHadPt = newTH2D("tauPtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    tau2PtVSGenTauHadPt = newTH2D("tau2PtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    tauMuonCleanedPtVSGenTauHadPt = newTH2D("tauMuonCleanedPtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    tauElectronCleanedPtVSGenTauHadPt = newTH2D("tauElectronCleanedPtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    jetPtVSGenTauHad2Pt = newTH2D("tau2PtVSGenTauHad2Pt", "p_{T}^{rec}(j)[GeV]", "p_{T}^{gen}(#tau_{h}#tau_{h})[GeV]", NBinsTau2Pt, tau2PtBin, NBinsTau2Pt, tau2PtBin);
}

HistoTauEff::~HistoTauEff()
{}

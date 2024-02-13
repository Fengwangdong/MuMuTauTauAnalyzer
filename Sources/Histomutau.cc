#include <TH1D.h>
#include "Histomutau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

// ---------- customize the axis settings of TH1D and TH2D ----------------
TH1D* Histomutau::newTH1D(string name, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* Histomutau::newTH1D(string name, string xTitle, vector<double>& xBinsVect)
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

TH1D* Histomutau::newTH1D(string name, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double *yBinsY){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yBinsY);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double *yBins){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

// --------------- customize the binning of output histograms -----------------
Histomutau::Histomutau(){

    double Mu1PtBin [] = {3, 18, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 110, 115, 120, 126, 133, 141, 150, 160, 171, 183, 196, 210, 225, 241, 258, 276, 300};
    double Mu2PtBin [] = {3, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double Mu3PtBin [] = {3, 10, 20, 30, 50, 100, 200}; 
    double Mu4PtBin [] = {3, 10, 20, 30, 50, 100, 200}; 
    double Ele1PtBin [] = {3, 10, 20, 30, 50, 100, 200}; 
    double Ele2PtBin [] = {3, 10, 20, 30, 50, 100, 200}; 
    double Mu1Mu2PtBin [] = {0, 5, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double tauPtBin [] = {8, 20, 30, 50, 100, 200};
    double tau2PtBin [] = {8, 20, 30, 50, 80, 120, 170, 230, 300, 380, 500, 640, 800, 980, 1180, 1400};
    double Mu3TauPtBin [] = {0, 5, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double Mu1Mu2Mu3TauPtBin [] = {0, 5, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double metPtBin [] = {10, 20, 30, 50, 80, 120, 170, 230, 300, 380, 500, 640, 800, 980, 1180, 1400};

    int NBinsMu1Pt = sizeof(Mu1PtBin)/sizeof(Mu1PtBin[0])-1;
    int NBinsMu2Pt = sizeof(Mu2PtBin)/sizeof(Mu2PtBin[0])-1;
    int NBinsMu3Pt = sizeof(Mu3PtBin)/sizeof(Mu3PtBin[0])-1;
    int NBinsMu4Pt = sizeof(Mu4PtBin)/sizeof(Mu4PtBin[0])-1;
    int NBinsEle1Pt = sizeof(Ele1PtBin)/sizeof(Ele1PtBin[0])-1;
    int NBinsEle2Pt = sizeof(Ele2PtBin)/sizeof(Ele2PtBin[0])-1;
    int NBinsMu1Mu2Pt = sizeof(Mu1Mu2PtBin)/sizeof(Mu1Mu2PtBin[0])-1;
    int NBinsTauPt = sizeof(tauPtBin)/sizeof(tauPtBin[0])-1;
    int NBinsTau2Pt = sizeof(tau2PtBin)/sizeof(tau2PtBin[0])-1;
    int NBinsMu3TauPt = sizeof(Mu3TauPtBin)/sizeof(Mu3TauPtBin[0])-1;
    int NBinsMu1Mu2Mu3TauPt = sizeof(Mu1Mu2Mu3TauPtBin)/sizeof(Mu1Mu2Mu3TauPtBin[0])-1;
    int NBinsMetPt = sizeof(metPtBin)/sizeof(metPtBin[0])-1;

    dRMu1Mu2 = newTH1D("dRMu1Mu2", "#Delta R(#mu_{1}#mu_{2})", 10, 0, 1.0);
    dRMu3Mu4 = newTH1D("dRMu3Mu4", "#Delta R(#mu_{3}#mu_{4})", 10, 0, 1.0);
    dRMu3Ele = newTH1D("dRMu3Ele", "#Delta R(#mu_{3}e)", 10, 0, 1.0);
    dREleEle = newTH1D("dREleEle", "#Delta R(ee)", 10, 0, 1.0);
    dRMu3Tau = newTH1D("dRMu3Tau", "#Delta R(#mu_{3}#tau)", 10, 0, 1.0);
    dREleTau = newTH1D("dREleTau", "#Delta R(e#tau)", 10, 0, 1.0);
    dRTauTau = newTH1D("dRTauTau", "#Delta R(#tau#tau)", 10, 0, 1.0);

    invMassMu1Mu2 = newTH1D("invMassMu1Mu2", "M(#mu_{1}#mu_{2})[GeV]", 20, 0, 60);
    invMassMu3Mu4 = newTH1D("invMassMu3Mu4", "M(#mu_{3}#mu_{4})[GeV]", 20, 0, 60);
    invMassMu3Ele = newTH1D("invMassMu3Ele", "M(#mu_{3}e)[GeV]", 20, 0, 60);
    invMassEleEle = newTH1D("invMassEleEle", "M(ee)[GeV]", 20, 0, 60);
    invMassMu3Tau = newTH1D("invMassMu3Tau", "M(#mu_{3}#tau)[GeV]", 20, 0, 60);
    invMassEleTau = newTH1D("invMassEleTau", "M(e#tau)[GeV]", 20, 0, 60);
    invMassTauTau = newTH1D("invMassTauTau", "M(#tau#tau)[GeV]", 20, 0, 60);

    invMassMuMuTauMuTauMu = newTH1D("invMassMuMuTauMuTauMu", "M(#mu#mu#mu#mu)[GeV]", 25, 20, 1500);
    invMassMuMuTauMuTauEle = newTH1D("invMassMuMuTauMuTauEle", "M(#mu#mu#mue)[GeV]", 25, 20, 1500);
    invMassMuMuTauEleTauEle = newTH1D("invMassMuMuTauEleTauEle", "M(#mu#muee)[GeV]", 25, 20, 1500);
    invMassMuMuTauMuTauHad = newTH1D("invMassMuMuTauMuTauHad", "M(#mu#mu#mu#tau)[GeV]", 25, 20, 1500);
    invMassMuMuTauEleTauHad = newTH1D("invMassMuMuTauEleTauHad", "M(#mu#mue#tau)[GeV]", 25, 20, 1500);
    invMassMuMuTauHadTauHad = newTH1D("invMassMuMuTauHadTauHad", "M(#mu#mu#tau#tau)[GeV]", 200, 20, 1500);

    ptMu1Mu2 = newTH1D("ptMu1Mu2", "p_{T}(#mu_{1}#mu_{2})[GeV]", NBinsMu1Mu2Pt, Mu1Mu2PtBin);
    ptMu3Mu4 = newTH1D("ptMu3Mu4", "p_{T}(#mu_{3}#mu_{4})[GeV]", NBinsMu3TauPt, Mu3TauPtBin);
    ptMu3Ele = newTH1D("ptMu3Ele", "p_{T}(#mu_{3}e)[GeV]", NBinsMu3TauPt, Mu3TauPtBin);
    ptEleEle = newTH1D("ptEleEle", "p_{T}(ee)[GeV]", NBinsMu3TauPt, Mu3TauPtBin);
    ptMu3Tau = newTH1D("ptMu3Tau", "p_{T}(#mu_{3}#tau)[GeV]", NBinsMu3TauPt, Mu3TauPtBin);
    ptEleTau = newTH1D("ptEleTau", "p_{T}(e#tau)[GeV]", NBinsMu3TauPt, Mu3TauPtBin);
    ptTauTau = newTH1D("ptTauTau", "p_{T}(#tau#tau)[GeV]", NBinsMu3TauPt, Mu3TauPtBin);

    ptMuMuTauMuTauMu = newTH1D("ptMuMuTauMuTauMu", "p_{T}(#mu#mu#mu#mu)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);
    ptMuMuTauMuTauEle = newTH1D("ptMuMuTauMuTauEle", "p_{T}(#mu#mu#mue)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);
    ptMuMuTauEleTauEle = newTH1D("ptMuMuTauEleTauEle", "p_{T}(#mu#muee)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);
    ptMuMuTauMuTauHad = newTH1D("ptMuMuTauMuTauHad", "p_{T}(#mu#mu#mu#tau)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);
    ptMuMuTauEleTauHad = newTH1D("ptMuMuTauEleTauHad", "p_{T}(#mu#mue#tau)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);
    ptMuMuTauHadTauHad = newTH1D("ptMuMuTauHadTauHad", "p_{T}(#mu#mu#tau#tau)[GeV]", NBinsMu1Mu2Mu3TauPt, Mu1Mu2Mu3TauPtBin);

    mu1Iso = newTH1D("mu1Iso", "#mu_{1}^{iso}", 20, 0, 0.25);
    mu2Iso = newTH1D("mu2Iso", "#mu_{2}^{iso}", 20, 0, 0.25);
    mu3Iso = newTH1D("mu3Iso", "#mu_{3}^{iso}", 20, 0, 20);
    mu4Iso = newTH1D("mu4Iso", "#mu_{4}^{iso}", 20, 0, 20);
    ele1Iso = newTH1D("ele1Iso", "e_{1}^{iso}", 20, 0, 20);
    ele2Iso = newTH1D("ele2Iso", "e_{2}^{iso}", 20, 0, 20);
    tauIsoMVA = newTH1D("tauIsoMVA", "#tau^{iso}", 20, -1, 1);
    tau2IsoMVA = newTH1D("tau2IsoMVA", "#tau#tau^{iso}", 20, 0, 1);

    mu1Pt = newTH1D("mu1Pt", "p_{T}(#mu_{1}) [GeV]", NBinsMu1Pt, Mu1PtBin);
    mu1Eta = newTH1D("mu1Eta", "#eta(#mu_{1})", 20, -2.1, 2.1);
    mu1Phi = newTH1D("mu1Phi", "#phi(#mu_{1})", 20, -2.5, 2.5);

    mu2Pt = newTH1D("mu2Pt", "p_{T}(#mu_{2}) [GeV]", NBinsMu2Pt, Mu2PtBin);
    mu2Eta = newTH1D("mu2Eta", "#eta(#mu_{2})", 20, -2.1, 2.1);
    mu2Phi = newTH1D("mu2Phi", "#phi(#mu_{2})", 20, -2.5, 2.5);

    mu3Pt = newTH1D("mu3Pt", "p_{T}(#mu_{3}) [GeV]", NBinsMu3Pt, Mu3PtBin);
    mu3Eta = newTH1D("mu3Eta", "#eta(#mu_{3})", 20, -2.1, 2.1);
    mu3Phi = newTH1D("mu3Phi", "#phi(#mu_{3})", 20, -2.5, 2.5);

    mu4Pt = newTH1D("mu4Pt", "p_{T}(#mu_{4}) [GeV]", NBinsMu4Pt, Mu4PtBin);
    mu4Eta = newTH1D("mu4Eta", "#eta(#mu_{4})", 20, -2.1, 2.1);
    mu4Phi = newTH1D("mu4Phi", "#phi(#mu_{4})", 20, -2.5, 2.5);

    ele1Pt = newTH1D("ele1Pt", "p_{T}(e_{1}) [GeV]", NBinsEle1Pt, Ele1PtBin);
    ele1Eta = newTH1D("ele1Eta", "#eta(e_{1})", 20, -2.1, 2.1);
    ele1Phi = newTH1D("ele1Phi", "#phi(e_{1})", 20, -2.5, 2.5);

    ele2Pt = newTH1D("ele2Pt", "p_{T}(e_{2}) [GeV]", NBinsEle2Pt, Ele2PtBin);
    ele2Eta = newTH1D("ele2Eta", "#eta(e_{2})", 20, -2.1, 2.1);
    ele2Phi = newTH1D("ele2Phi", "#phi(e_{2})", 20, -2.5, 2.5);

    tauPt = newTH1D("tauPt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tauEta = newTH1D("tauEta", "#eta(#tau)", 20, -2.1, 2.1);
    tauPhi = newTH1D("tauPhi", "#phi(#tau)", 20, -2.5, 2.5);
    tauMass = newTH1D("tauMass", "M(#tau) [GeV]", 10, 0, 3);
    tauDecayMode = newTH1D("tauDecayMode", "DecayMode(#tau)", 12, 0, 12);

    tau2Pt = newTH1D("tau2Pt", "p_{T}(#tau#tau) [GeV]", NBinsTau2Pt, tau2PtBin);
    tau2Eta = newTH1D("tau2Eta", "#eta(#tau#tau)", 20, -2.1, 2.1);
    tau2Phi = newTH1D("tau2Phi", "#phi(#tau#tau)", 20, -2.5, 2.5);
    tau2Mass = newTH1D("tau2Mass", "M(#tau#tau) [GeV]", 30, 0, 60);
    tau2DecayMode = newTH1D("tau2DecayMode", "DecayMode(#tau_{2})", 12, 0, 12);

    metPt = newTH1D("metPt", "#slash{E_{T}} [GeV]", NBinsMetPt, metPtBin);

    dRMu1Mu3 = newTH1D("dRMu1Mu3", "#Delta R(#mu_{1}#mu_{3})", 25, 0, 5);
    dRMu1Mu4 = newTH1D("dRMu1Mu4", "#Delta R(#mu_{1}#mu_{4})", 25, 0, 5);
    dRMu1Ele1 = newTH1D("dRMu1Ele1", "#Delta R(#mu_{1}e_{1})", 25, 0, 5);
    dRMu1Ele2 = newTH1D("dRMu1Ele2", "#Delta R(#mu_{1}e_{2})", 25, 0, 5);
    dRMu1Tau = newTH1D("dRMu1Tau", "#Delta R(#mu_{1}#tau)", 25, 0, 5);
    dRMu1Tau2 = newTH1D("dRMu1Tau2", "#Delta R(#mu_{1},#tau#tau)", 25, 0, 5);

    dRMu2Mu3 = newTH1D("dRMu2Mu3", "#Delta R(#mu_{2}#mu_{3})", 25, 0, 5);
    dRMu2Mu4 = newTH1D("dRMu2Mu4", "#Delta R(#mu_{2}#mu_{4})", 25, 0, 5);
    dRMu2Ele1 = newTH1D("dRMu2Ele1", "#Delta R(#mu_{2}e_{1})", 25, 0, 5);
    dRMu2Ele2 = newTH1D("dRMu2Ele2", "#Delta R(#mu_{2}e_{2})", 25, 0, 5);
    dRMu2Tau = newTH1D("dRMu2Tau", "#Delta R(#mu_{2}#tau)", 25, 0, 5);
    dRMu2Tau2 = newTH1D("dRMu2Tau2", "#Delta R(#mu_{2},#tau#tau)", 25, 0, 5);

    dMMuMuTauTau = newTH1D("dMMuMuTauTau", "#frac{M(#mu#mu)-M(#tau#tau)}{M(#mu#mu)}", 20, -1, 1);

    dRInvMassMu1Mu2 = newTH2D("dRInvMassMu1Mu2", "#Delta R(#mu_{1}#mu_{2})", "M(#mu_{1}#mu_{2})[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassMu3Mu4 = newTH2D("dRInvMassMu3Mu4", "#Delta R(#mu_{3}#mu_{4})", "M(#mu_{3}#mu_{4})[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassMu3Ele = newTH2D("dRInvMassMu3Ele", "#Delta R(#mu_{3}e)", "M(#mu_{3}e)[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassEleEle = newTH2D("dRInvMassEleEle", "#Delta R(ee)", "M(ee)[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassMu3Tau = newTH2D("dRInvMassMu3Tau", "#Delta R(#mu_{3}#tau)", "M(#mu_{3}#tau)[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassEleTau = newTH2D("dRInvMassEleTau", "#Delta R(e#tau)", "M(e#tau)[GeV]", 10, 0, 1, 20, 0, 60);
    dRInvMassTauTau = newTH2D("dRInvMassTauTau", "#Delta R(#tau#tau)", "M(#tau#tau)[GeV]", 10, 0, 1, 20, 0, 60);

    invMassTauTauMet = newTH2D("invMassTauTauMet", "M(#tau#tau)[GeV]", "#slash{E_{T}} [GeV]", 20, 0, 60, NBinsMetPt, metPtBin);
    invMassMuMuTauHadTauHadMet = newTH2D("invMassMuMuTauHadTauHadMet", "M(#mu#mu#tau#tau)[GeV]", "#slash{E_{T}} [GeV]", 200, 20, 1500, NBinsMetPt, metPtBin);

    // -------------- reco-gen response histograms ------------------
    dRMu1Mu2VSGenMu1GenMu2 = newTH2D("dRMu1Mu2VSGenMu1GenMu2", "#DeltaR(#mu_{1}^{rec}#mu_{2}^{rec})", "#DeltaR(#mu_{1}^{gen}#mu_{2}^{gen})", 10, 0, 1, 10, 0, 1);
    dRMu3TauVSGenMu3GenTauHad = newTH2D("dRMu3TauVSGenMu3GenTauHad", "#DeltaR(#mu_{3}^{rec}#tau_{h}^{rec})", "#DeltaR(#mu_{3}^{gen}#tau_{h}^{gen})", 10, 0, 1, 10, 0, 1);
    dRMu3TauVSGenTauMuGenTauHad = newTH2D("dRMu3TauVSGenTauMuGenTauHad", "#DeltaR(#mu_{3}^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", 10, 0, 1, 10, 0, 1);
    dREleTauVSGenEleGenTauHad = newTH2D("dREleTauVSGenEleGenTauHad", "#DeltaR(e^{rec}#tau_{h}^{rec})", "#DeltaR(e^{gen}#tau_{h}^{gen})", 10, 0, 1, 10, 0, 1);
    dREleTauVSGenTauEleGenTauHad = newTH2D("dREleTauVSGenTauEleGenTauHad", "#DeltaR(e^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{e}^{gen}#tau_{h}^{gen})", 10, 0, 1, 10, 0, 1);

    invMassMu1Mu2VSGenMu1GenMu2 = newTH2D("invMassMu1Mu2VSGenMu1GenMu2", "M(#mu_{1}^{rec}#mu_{2}^{rec})[GeV]", "M(#mu_{1}^{gen}#mu_{2}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);
    invMassMu3TauVSGenMu3GenTauHad = newTH2D("invMassMu3TauVSGenMu3GenTauHad", "M(#mu_{3}^{rec}#tau_{h}^{rec})[GeV]", "M(#mu_{3}^{gen}#tau_{h}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);
    invMassMu3TauVSGenTauMuGenTauHad = newTH2D("invMassMu3TauVSGenTauMuGenTauHad", "M(#mu_{3}^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);
    invMassEleTauVSGenEleGenTauHad = newTH2D("invMassEleTauVSGenEleGenTauHad", "M(e^{rec}#tau_{h}^{rec})[GeV]", "M(e^{gen}#tau_{h}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);
    invMassEleTauVSGenTauEleGenTauHad = newTH2D("invMassEleTauVSGenTauEleGenTauHad", "M(e^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{e}^{gen}#tau_{h}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);
    invMassTauTauVSGenTauHadGenTauHad = newTH2D("invMassTauTauVSGenTauHadGenTauHad", "M(#tau_{h}^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{h}^{gen}#tau_{h}^{gen})[GeV]", 20, 0, 60, 20, 0, 60);

    mu1PtVSGenMu1Pt = newTH2D("mu1PtVSGenMu1Pt", "p_{T}^{rec}(#mu_{1})[GeV]", "p_{T}^{gen}(#mu_{1})[GeV]", NBinsMu1Pt, Mu1PtBin, NBinsMu1Pt, Mu1PtBin);
    mu1EtaVSGenMu1Eta = newTH2D("mu1EtaVSGenMu1Eta", "#eta^{rec}(#mu_{1})", "#eta^{gen}(#mu_{1})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    mu1PhiVSGenMu1Phi = newTH2D("mu1PhiVSGenMu1Phi", "#phi^{rec}(#mu_{1})", "#phi^{gen}(#mu_{1})", 20, -2.1, 2.1, 20, -2.1, 2.1);

    mu2PtVSGenMu2Pt = newTH2D("mu2PtVSGenMu2Pt", "p_{T}^{rec}(#mu_{2})[GeV]", "p_{T}^{gen}(#mu_{2})[GeV]", NBinsMu2Pt, Mu2PtBin, NBinsMu2Pt, Mu2PtBin);
    mu2EtaVSGenMu2Eta = newTH2D("mu2EtaVSGenMu2Eta", "#eta^{rec}(#mu_{2})", "#eta^{gen}(#mu_{2})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    mu2PhiVSGenMu2Phi = newTH2D("mu2PhiVSGenMu2Phi", "#phi^{rec}(#mu_{2})", "#phi^{gen}(#mu_{2})", 20, -2.1, 2.1, 20, -2.1, 2.1);

    mu3PtVSGenMu3Pt = newTH2D("mu3PtVSGenMu3Pt", "p_{T}^{rec}(#mu_{3})[GeV]", "p_{T}^{gen}(#mu_{3})[GeV]", NBinsMu3Pt, Mu3PtBin, NBinsMu3Pt, Mu3PtBin);
    mu3EtaVSGenMu3Eta = newTH2D("mu3EtaVSGenMu3Eta", "#eta^{rec}(#mu_{3})", "#eta^{gen}(#mu_{3})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    mu3PhiVSGenMu3Phi = newTH2D("mu3PhiVSGenMu3Phi", "#phi^{rec}(#mu_{3})", "#phi^{gen}(#mu_{3})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    mu3PtVSGenTauMuPt = newTH2D("mu3PtVSGenTauMuPt", "p_{T}^{rec}(#mu_{3})[GeV]", "p_{T}^{gen}(#tau_{#mu})[GeV]", NBinsMu3Pt, Mu3PtBin, NBinsMu3Pt, Mu3PtBin);

    elePtVSGenElePt = newTH2D("elePtVSGenElePt", "p_{T}^{rec}(e)[GeV]", "p_{T}^{gen}(e)[GeV]", NBinsEle1Pt, Ele1PtBin, NBinsEle1Pt, Ele1PtBin);
    eleEtaVSGenEleEta = newTH2D("eleEtaVSGenEleEta", "#eta^{rec}(e)", "#eta^{gen}(e)", 20, -2.1, 2.1, 20, -2.1, 2.1);
    elePhiVSGenElePhi = newTH2D("elePhiVSGenElePhi", "#phi^{rec}(e)", "#phi^{gen}(e)", 20, -2.1, 2.1, 20, -2.1, 2.1);
    elePtVSGenTauElePt = newTH2D("elePtVSGenTauElePt", "p_{T}^{rec}(e)[GeV]", "p_{T}^{gen}(#tau_{e})[GeV]", NBinsEle1Pt, Ele1PtBin, NBinsEle1Pt, Ele1PtBin);
    elePtVSGenTauEleVisPt = newTH2D("elePtVSGenTauEleVisPt", "p_{T}^{rec}(e)[GeV]", "p_{T}^{gen}(#tau_{e}^{vis})[GeV]", NBinsEle1Pt, Ele1PtBin, NBinsEle1Pt, Ele1PtBin);

    tauPtVSGenTauHadPt = newTH2D("tauPtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    tauEtaVSGenTauHadEta = newTH2D("tauEtaVSGenTauHadEta", "#eta^{rec}(#tau)", "#eta^{gen}(#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tauPhiVSGenTauHadPhi = newTH2D("tauPhiVSGenTauHadPhi", "#phi^{rec}(#tau)", "#phi^{gen}(#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tauPtVSGenTauHadVisPt = newTH2D("tauPtVSGenTauHadVisPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h}^{vis})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);

    tau2PtVSGenTauHad2Pt = newTH2D("tau2PtVSGenTauHad2Pt", "p_{T}^{rec}(#tau#tau)[GeV]", "p_{T}^{gen}(#tau_{h}#tau_{h})[GeV]", NBinsTau2Pt, tau2PtBin, NBinsTau2Pt, tau2PtBin);
    tau2EtaVSGenTauHad2Eta = newTH2D("tau2EtaVSGenTauHad2Eta", "#eta^{rec}(#tau#tau)", "#eta^{gen}(#tau_{h}#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tau2PhiVSGenTauHad2Phi = newTH2D("tau2PhiVSGenTauHad2Phi", "#phi^{rec}(#tau#tau)", "#phi^{gen}(#tau_{h}#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tau2PtVSGenTauHad2VisPt = newTH2D("tau2PtVSGenTauHad2VisPt", "p_{T}^{rec}(#tau_{2})[GeV]", "p_{T}^{gen}(#tau_{h}^{vis}_{2})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);

    // ----------- flat tree for fit -----------
    TreeMuMuTauTau = new TTree("TreeMuMuTauTau","TreeMuMuTauTau");

    TreeMuMuTauTau->Branch("invMassMuMu", &invMassMuMu, "invMassMuMu/D");
    TreeMuMuTauTau->Branch("visMassTauTau", &visMassTauTau, "visMassTauTau/D");
    TreeMuMuTauTau->Branch("visMassMuMuTauTau", &visMassMuMuTauTau, "visMassMuMuTauTau/D");

    TreeMuMuTauTau->Branch("deltaRMuMu", &deltaRMuMu, "deltaRMuMu/D");
    TreeMuMuTauTau->Branch("deltaRTauTau", &deltaRTauTau, "deltaRTauTau/D");

    TreeMuMuTauTau->Branch("Mu1Pt", &Mu1Pt, "Mu1Pt/D");
    TreeMuMuTauTau->Branch("Mu1Eta", &Mu1Eta, "Mu1Eta/D");
    TreeMuMuTauTau->Branch("Mu1DZ", &Mu1DZ, "Mu1DZ/D");

    TreeMuMuTauTau->Branch("Mu2Pt", &Mu2Pt, "Mu2Pt/D");
    TreeMuMuTauTau->Branch("Mu2Eta", &Mu2Eta, "Mu2Eta/D");
    TreeMuMuTauTau->Branch("Mu2DZ", &Mu2DZ, "Mu2DZ/D");

    TreeMuMuTauTau->Branch("Tau1Pt", &Tau1Pt, "Tau1Pt/D");
    TreeMuMuTauTau->Branch("Tau1Eta", &Tau1Eta, "Tau1Eta/D");
    TreeMuMuTauTau->Branch("Tau1Isolation", &Tau1Isolation, "Tau1Isolation/D");
    TreeMuMuTauTau->Branch("Tau1DecayMode", &Tau1DecayMode, "Tau1DecayMode/D");

    TreeMuMuTauTau->Branch("Tau2Pt", &Tau2Pt, "Tau2Pt/D");
    TreeMuMuTauTau->Branch("Tau2Eta", &Tau2Eta, "Tau2Eta/D");
    TreeMuMuTauTau->Branch("Tau2Isolation", &Tau2Isolation, "Tau2Isolation/D");
    TreeMuMuTauTau->Branch("Tau2DecayMode", &Tau2DecayMode, "Tau2DecayMode/D");

    TreeMuMuTauTau->Branch("eventWeight", &eventWeight, "eventWeight/D");
    TreeMuMuTauTau->Branch("nPileup", &nPileup, "nPileup/I");
}

Histomutau::~Histomutau()
{}

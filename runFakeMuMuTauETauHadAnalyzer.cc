#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "FakeMuMuTauETauHadAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile              = cfg.getS("inputFile");
    TString outputDir              = cfg.getS("outputDir");
    TString doWhat                 = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents               = cfg.getL("maxEvents", -1);
    double lumi                    = cfg.getD("lumi", 1);
    double Mu1IsoThreshold         = cfg.getD("Mu1IsoThreshold", 0.25);
    double Mu2IsoThreshold         = cfg.getD("Mu2IsoThreshold", 0.25);
    TString MuonId                 = cfg.getS("MuonId", "LOOSE");
    TString EleRelId               = cfg.getS("EleRelId", "LOOSE");
    double diMuonMassLowThreshold  = cfg.getD("diMuonMassLowThreshold", 0);
    double diMuonMassHighThreshold = cfg.getD("diMuonMassHighThreshold", 25.0);
    bool tauMVAIsoRawORWP          = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold   = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP            = cfg.getS("tauMVAIsoWP", "MEDIUM");
    TString tauAntiMuDisc          = cfg.getS("tauAntiMuDisc", "LOOSE");
    TString tauAntiEleDisc         = cfg.getS("tauAntiEleDisc", "LOOSE");
    bool matchRecGen               = cfg.getB("matchRecGen", false);
    bool deepTauID                 = cfg.getB("deepTauID", false);
    TString deepTauVSele           = cfg.getS("deepTauVSele", "VVVLOOSE");
    TString deepTauVSmu            = cfg.getS("deepTauVSmu", "VLOOSE");
    TString deepTauVSjet           = cfg.getS("deepTauVSjet", "LOOSE");
    double tauDecayModeThreshold   = cfg.getD("tauDecayModeThreshold", -1);
    TString rochesterFile          = cfg.getS("rochesterFile", "");

    //--- Parse the arguments -----------------------------------------------------
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            TString currentArg = argv[i];
            
            //--- possible options ---
            if (currentArg.BeginsWith("inputFile="))
            {
                getArg(currentArg, inputFile);
            }

            else if (currentArg.BeginsWith("outputDir="))
            {
                getArg(currentArg, outputDir);
            }

            else if (currentArg.BeginsWith("doWhat="))
            {
                getArg(currentArg, doWhat);
            }

            else if (currentArg.BeginsWith("maxEvents="))
            {
                getArg(currentArg, maxEvents);
            }

            else if (currentArg.BeginsWith("lumi="))
            {
                getArg(currentArg, lumi);
            }

            else if (currentArg.BeginsWith("Mu1IsoThreshold="))
            {
                getArg(currentArg, Mu1IsoThreshold);
            }

            else if (currentArg.BeginsWith("Mu2IsoThreshold="))
            {
                getArg(currentArg, Mu2IsoThreshold);
            }

            else if (currentArg.BeginsWith("MuonId="))
            {
                getArg(currentArg, MuonId);
            }

            else if (currentArg.BeginsWith("EleRelId="))
            {
                getArg(currentArg, EleRelId);
            }

            else if (currentArg.BeginsWith("diMuonMassLowThreshold="))
            {
                getArg(currentArg, diMuonMassLowThreshold);
            }

            else if (currentArg.BeginsWith("diMuonMassHighThreshold="))
            {
                getArg(currentArg, diMuonMassHighThreshold);
            }

            else if (currentArg.BeginsWith("tauMVAIsoRawORWP="))
            {
                getArg(currentArg, tauMVAIsoRawORWP);
            }

            else if (currentArg.BeginsWith("tauMVAIsoRawThreshold="))
            {
                getArg(currentArg, tauMVAIsoRawThreshold);
            }

            else if (currentArg.BeginsWith("tauMVAIsoWP="))
            {
                getArg(currentArg, tauMVAIsoWP);
            }

            else if (currentArg.BeginsWith("tauAntiMuDisc="))
            {
                getArg(currentArg, tauAntiMuDisc);
            }

            else if (currentArg.BeginsWith("tauAntiEleDisc="))
            {
                getArg(currentArg, tauAntiEleDisc);
            }

            else if (currentArg.BeginsWith("matchRecGen="))
            {
                getArg(currentArg, matchRecGen);
            }

            else if (currentArg.BeginsWith("deepTauID="))
            {
                getArg(currentArg, deepTauID);
            }

            else if (currentArg.BeginsWith("deepTauVSele="))
            {
                getArg(currentArg, deepTauVSele);
            }

            else if (currentArg.BeginsWith("deepTauVSmu="))
            {
                getArg(currentArg, deepTauVSmu);
            }

            else if (currentArg.BeginsWith("deepTauVSjet="))
            {
                getArg(currentArg, deepTauVSjet);
            }

            else if (currentArg.BeginsWith("tauDecayModeThreshold="))
            {
                getArg(currentArg, tauDecayModeThreshold);
            }

            else if (currentArg.BeginsWith("rochesterFile="))
            {
                getArg(currentArg, rochesterFile);
            }
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    MuonId.ToUpper();
    EleRelId.ToUpper();
    tauMVAIsoWP.ToUpper();
    tauAntiMuDisc.ToUpper();
    tauAntiEleDisc.ToUpper();
    deepTauVSele.ToUpper();
    deepTauVSmu.ToUpper();
    deepTauVSjet.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            FakeMuMuTauETauHadAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, false, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, false, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                DataHist.Loop();
            } // end while loop on file list 
        } // end else inputFile.EndsWith(".root")
    } // end if data

    // ----- This variable is to be used for MC reweighting -----
    float summedWeights = 0;

    // ------------------------ MC histogram production ------------------
    if (doWhat == "DYJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();
            FakeMuMuTauETauHadAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            DYJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana DYJetsLumi(fileName);
                summedWeights += DYJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;


    if (doWhat == "WJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WJetsLumi(inputFile);
            summedWeights = WJetsLumi.Loop();
            FakeMuMuTauETauHadAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            WJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WJetsLumi(fileName);
                summedWeights += WJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                WJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "TTJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana TTJetsLumi(inputFile);
            summedWeights = TTJetsLumi.Loop();
            FakeMuMuTauETauHadAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            TTJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana TTJetsLumi(fileName);
                summedWeights += TTJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                TTJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if TTJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WW" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WWIncLumi(inputFile);
            summedWeights = WWIncLumi.Loop();
            FakeMuMuTauETauHadAnalyzer WWIncHist(inputFile, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            WWIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WWIncLumi(fileName);
                summedWeights += WWIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer WWIncHist(fileName, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                WWIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WWInc

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WZIncLumi(inputFile);
            summedWeights = WZIncLumi.Loop();
            FakeMuMuTauETauHadAnalyzer WZIncHist(inputFile, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            WZIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WZIncLumi(fileName);
                summedWeights += WZIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer WZIncHist(fileName, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                WZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WZInc

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "ZZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana ZZIncLumi(inputFile);
            summedWeights = ZZIncLumi.Loop();
            FakeMuMuTauETauHadAnalyzer ZZIncHist(inputFile, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            ZZIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana ZZIncLumi(fileName);
                summedWeights += ZZIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer ZZIncHist(fileName, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                ZZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZInc

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "JPSI" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana JpsiLumi(inputFile);
            summedWeights = JpsiLumi.Loop();
            FakeMuMuTauETauHadAnalyzer JpsiHist(inputFile, outputDir, lumi*880400.0*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
            JpsiHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana JpsiLumi(fileName);
                summedWeights += JpsiLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauHadAnalyzer JpsiHist(fileName, outputDir, lumi*880400.0*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, matchRecGen, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, rochesterFile);
                JpsiHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if Jpsi

    return 0;
}

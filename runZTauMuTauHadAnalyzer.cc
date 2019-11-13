#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "ZTauMuTauHadAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile            = cfg.getS("inputFile");
    TString outputDir            = cfg.getS("outputDir");
    TString doWhat               = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents             = cfg.getL("maxEvents", -1);
    double lumi                  = cfg.getD("lumi", 1);
    bool invertedMu1Iso          = cfg.getB("invertedMu1Iso", false);
    float Mu1IsoThreshold        = cfg.getF("Mu1IsoThreshold", 0.25); 
    bool tauMVAIsoRawORWP        = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP          = cfg.getS("tauMVAIsoWP", "MEDIUM");
    bool signSameOROpposite      = cfg.getB("signSameOROpposite", false);
    float mTMuTauLowThreshold    = cfg.getF("mTMuTauLowThreshold", 0);
    float mTMuTauHighThreshold   = cfg.getF("mTMuTauHighThreshold", 160.0);
    bool invertedPzetaCut        = cfg.getB("invertedPzetaCut", false);
    float pzetaThreshold         = cfg.getF("pzetaThreshold", -125.0);

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

            else if (currentArg.BeginsWith("invertedMu1Iso="))
            {
                getArg(currentArg, invertedMu1Iso);
            }

            else if (currentArg.BeginsWith("Mu1IsoThreshold="))
            {
                getArg(currentArg, Mu1IsoThreshold);
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

            else if (currentArg.BeginsWith("signSameOROpposite="))
            {
                getArg(currentArg, signSameOROpposite);
            }

            else if (currentArg.BeginsWith("mTMuTauLowThreshold="))
            {
                getArg(currentArg, mTMuTauLowThreshold);
            }

            else if (currentArg.BeginsWith("mTMuTauHighThreshold="))
            {
                getArg(currentArg, mTMuTauHighThreshold);
            }

            else if (currentArg.BeginsWith("invertedPzetaCut="))
            {
                getArg(currentArg, invertedPzetaCut);
            }

            else if (currentArg.BeginsWith("pzetaThreshold="))
            {
                getArg(currentArg, pzetaThreshold);
            }
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    tauMVAIsoWP.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            ZTauMuTauHadAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                ZTauMuTauHadAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
            ZTauMuTauHadAnalyzer DYJetsHist(inputFile, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
                ZTauMuTauHadAnalyzer DYJetsHist(fileName, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
            ZTauMuTauHadAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
                ZTauMuTauHadAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
            ZTauMuTauHadAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
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
                ZTauMuTauHadAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuTauLowThreshold, mTMuTauHighThreshold, invertedPzetaCut, pzetaThreshold);
                TTJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if TTJets

    return 0;
}
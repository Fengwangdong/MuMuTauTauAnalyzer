#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "TauEffAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile      = cfg.getS("inputFile");
    TString outputDir      = cfg.getS("outputDir");
    TString doWhat         = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents       = cfg.getL("maxEvents", -1);
    double lumi            = cfg.getD("lumi", 1);
    TString MuonId         = cfg.getS("MuonId", "LOOSE");
    TString EleRelId       = cfg.getS("EleRelId", "LOOSE");
    bool tauMVAIsoRawORWP          = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold   = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP            = cfg.getS("tauMVAIsoWP", "MEDIUM");
    TString tauAntiMuDisc          = cfg.getS("tauAntiMuDisc", "NULL");
    TString tauAntiEleDisc         = cfg.getS("tauAntiEleDisc", "NULL");
    bool deepTauID                 = cfg.getB("deepTauID", false);
    TString deepTauVSele           = cfg.getS("deepTauVSele", "VVVLOOSE");
    TString deepTauVSmu            = cfg.getS("deepTauVSmu", "VLOOSE");
    TString deepTauVSjet           = cfg.getS("deepTauVSjet", "LOOSE");
    double tauDecayModeThreshold   = cfg.getD("tauDecayModeThreshold", -1);
    TString JetId                  = cfg.getS("JetId", "TIGHT");
    double deepDiTauRawThreshold   = cfg.getD("deepDiTauRawThreshold", 0.688);

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

            else if (currentArg.BeginsWith("MuonId="))
            {
                getArg(currentArg, MuonId);
            }

            else if (currentArg.BeginsWith("EleRelId="))
            {
                getArg(currentArg, EleRelId);
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

            else if (currentArg.BeginsWith("JetId="))
            {
                getArg(currentArg, JetId);
            }

            else if (currentArg.BeginsWith("deepDiTauRawThreshold="))
            {
                getArg(currentArg, deepDiTauRawThreshold);
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
    JetId.ToUpper();

    // ----- This variable is to be used for MC reweighting -----
    float summedWeights = 0;

    // ------------------------ MC histogram production ------------------
    if (doWhat == "H125AA5" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana H125AA5Lumi(inputFile);
            summedWeights = H125AA5Lumi.Loop();
            TauEffAnalyzer H125AA5Hist(inputFile, outputDir, lumi*48.58, summedWeights, maxEvents, MuonId, EleRelId, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, deepDiTauRawThreshold);
            H125AA5Hist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana H125AA5Lumi(fileName);
                summedWeights += H125AA5Lumi.Loop();
            } // end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                TauEffAnalyzer H125AA5Hist(fileName, outputDir, lumi*48.58, summedWeights, maxEvents, MuonId, EleRelId, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, deepDiTauRawThreshold);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}

#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "JetTauTauAnalyzer.h"
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
    bool invertedTauIso            = cfg.getB("invertedTauIso", false);
    bool invertedTau2Iso           = cfg.getB("invertedTau2Iso", false);
    TString JetId                  = cfg.getS("JetId", "TIGHT");
    bool massDecorrelation         = cfg.getB("massDecorrelation", false);
    double deepDiTauRawThreshold   = cfg.getD("deepDiTauRawThreshold", 0.5);
    double deepDiTauRawLowerBound  = cfg.getD("deepDiTauRawLowerBound", 0.2);

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

            else if (currentArg.BeginsWith("invertedTauIso=")) // Tau means j1, iso is its deepDiTau score
            {
                getArg(currentArg, invertedTauIso);
            }

            else if (currentArg.BeginsWith("invertedTau2Iso=")) // Tau2 means j2, iso is its deepDiTau score
            {
                getArg(currentArg, invertedTau2Iso);
            }

            else if (currentArg.BeginsWith("JetId="))
            {
                getArg(currentArg, JetId);
            }

            else if (currentArg.BeginsWith("massDecorrelation="))
            {
                getArg(currentArg, massDecorrelation);
            }

            else if (currentArg.BeginsWith("deepDiTauRawThreshold="))
            {
                getArg(currentArg, deepDiTauRawThreshold);
            }

            else if (currentArg.BeginsWith("deepDiTauRawLowerBound="))
            {
                getArg(currentArg, deepDiTauRawLowerBound);
            }
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    JetId.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            JetTauTauAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "DATA");
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                JetTauTauAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "DATA");
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

            JetTauTauAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "DYJ");
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
                JetTauTauAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "DYJ");
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "ZTT" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();

            JetTauTauAnalyzer ZTauTauHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "ZTT");
            ZTauTauHist.Loop();
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
                // ----------------- ZTauTau -------------------
                JetTauTauAnalyzer ZTauTauHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "ZTT");
                ZTauTauHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZTT

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WJetsLumi(inputFile);
            summedWeights = WJetsLumi.Loop();
            JetTauTauAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WJETS");
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
                JetTauTauAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WJETS");
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
            JetTauTauAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "TTJETS");
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
                JetTauTauAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "TTJETS");
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
            JetTauTauAnalyzer WWIncHist(inputFile, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WW");
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
                JetTauTauAnalyzer WWIncHist(fileName, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WW");
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
            JetTauTauAnalyzer WZIncHist(inputFile, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WZ");
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
                JetTauTauAnalyzer WZIncHist(fileName, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "WZ");
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
            JetTauTauAnalyzer ZZIncHist(inputFile, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "ZZ");
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
                JetTauTauAnalyzer ZZIncHist(fileName, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, invertedTauIso, invertedTau2Iso, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, "ZZ");
                ZZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZInc

    return 0;
}

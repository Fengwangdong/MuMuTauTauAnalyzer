# MuMuTauTauAnalyzer

This framework is used to analyze the output of "MuMuTauTauTreelizer". It is written in standard C++/ROOT format, as is independent from CMSSW. 
It reads the vector trees of different objects (eg. muons, electrons, taus, and jets), through making customized selection scripts, and outputs 
of variable histograms and/or flat trees.

# Introduction for running the analyzer

First you must make sure you have the ROOT and BOOST C++ libraries included in your local environment. If you need to run this framework in batch mode, it is better to set up a CMSSW package and run the following commands in its "src/" directory. 

$ git clone https://github.com/Fengwangdong/MuMuTauTauAnalyzer.git

$ cd MuMuTauTauAnalyzer

$ make clean

$ make # compile the C++ functions

$ cp example.cfg mumutautau.cfg

One needs the "mumutautau.cfg" file to customize the default input parameters before running the analyzer. In addition, these parameters can be 
also customized in the command line for instance when executing the analyzer, for instance:

# Run the diMuon Analyzer:

$ ./runMuMuAnalyzer doWhat=DYJets maxEvents=1000 inputFile=inputFile.root ###### for producing histograms of the dimuon channel (low diMu-mass control region)

$ ./runZMuMuAnalyzer doWhat=DYJets maxEvents=1000 inputFile=inputFile.root ###### for producing histograms of the dimuon channel (Z boson control region)

# Run the diMuon + ditau (tau_mu + tau_mu) Analyzer:

$ ./runMuMuTauMuTauMuAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_mu + tau_mu channel

# Run the diMuon + ditau (tau_mu + tau_e) Analyzer:

$ ./runMuMuTauMuTauEAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_mu + tau_e channel

# Run the diMuon + ditau (tau_e + tau_e) Analyzer:

$ ./runMuMuTauETauEAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_e + tau_e channel

# Run the diMuon + ditau (tau_mu + tau_h) Analyzer:

$ ./runMuMuTauMuTauHadAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_mu + tau_h channel

# Run the diMuon + ditau (tau_e + tau_h) Analyzer:

$ ./runMuMuTauETauHadAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_e + tau_h channel

# Run the diMuon + ditau (tau_h + tau_h) Analyzer:

$ ./runMuMuTauHadTauHadAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing histograms of the tau_h + tau_h channel

# Run the Z+Mu (muon + muon + tau_mu) Analyzer:

$ ./runFakeMuMuTauMuAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_mu channel (control region for jet faking muon study) 

# Run the Z+Ele (muon + muon + tau_e) Analyzer:

$ ./runFakeMuMuTauEAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_e channel (control region for jet faking electron study) 

# Run the Z+Tau (muon + muon + tau_h) Analyzer:

$ ./runFakeMuMuTauHadAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_h channel (control region for jet faking tau study) 

# Run the Z+MuTau (muon + muon + tau_mu + tau_h) Analyzer:

$ ./runFakeMuMuTauMuTauHadAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_mu + tau_h channel (control region for jet faking tau study with an adjacent muon) 

# Run the Z+EleTau (muon + muon + tau_e + tau_h) Analyzer:

$ ./runFakeMuMuTauETauHadAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_e + tau_h channel (control region for jet faking tau study with an adjacent electron) 

# Run the Z+diTau (muon + muon + tau_h + tau_h) Analyzer:

$ ./runFakeMuMuTauHadTauHadAnalyzer doWhat=Data maxEvents=3000 inputFile=inputFile.root ##### for producing the histograms of dimuon + tau_h + tau_h channel (control region for jet faking di-tau study) 

# Run the ZTauTau (muon + tau_h) Analyzer:

$ ./runZTauMuTauHadAnalyzer doWhat=DYJets maxEvents=2000 inputFile=inputFile.root ####### for producing histograms for tauID study 

# Run the diMuon + ditau inclusive Analyzer:
$ ./runMuMuTauTauInclusiveAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ###### for producing flat trees of all channels

# Run the tau efficiency Analyzer:
$ ./runTauEffAnalyzer doWhat=H125AA5 maxEvents=2000 inputFile=inputFile.root ####### for producing histograms for tau efficiency study
###############################################################

NOTE: If the parameters are customized in the command line, their default values in "mumutautau.cfg" will be ignored. 

In case there are many input root files, you can make a text file (eg. list.txt) with the list of input files with their paths, and modify the parameter of above commands as "inputFile=list.txt".

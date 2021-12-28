#include "AliAODInputHandler.h"
#include "AliAnalysisAlien.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisTaskMuMu.h"
#include "AliCodeTimer.h"
#include "AliInputEventHandler.h"
#include <TChain.h>
#include <TList.h>
#include <TStopwatch.h>
#include <TSystem.h>
#include <fstream>
#include <iostream>

void GetTriggerList(Bool_t simulations, TString &triggers, TString &inputs) {
  // Get the list of triggers to be analyzed
  //
  // Here you can use class names and/or combinations of classes and input,
  // e.g. triggers->Add(new TObjString("CINT7-B-NOPF-ALLNOTRD & 0MUL"));

  if (!simulations) {
    triggers = "CMUL7-B-NOPF-MUFAST,"
               "CINT7-B-NOPF-MUFAST,"
               "CMSL7-B-NOPF-MUFAST,"
               "CINT7-B-NOPF-MUFAST&0MUL,"
               "CMSL7-B-NOPF-MUFAST&0MUL,"
               "CINT7-B-NOPF-MUFAST&0MSL";
    inputs = "0MSL:19,0MSH:20,0MLL:4,0MUL:17";
  } else {
    // add here the MC-specific trigger you want to analyze (if any)
    triggers = "CMULLO-B-NOPF-MUON,"
               "CMSNGL-B-NOPF-MUON,"
               "ANY";
    // e.g. for dpmjet simulations (at least) we have the following "triggers"
    // : C0T0A,C0T0C,MB1,MBBG1,V0L,V0R,MULow,EMPTY,MBBG3,MULL,MULU,MUHigh
    inputs = "";
  }
}

enum GridRunMode {
        kLocal,
        kTest,
        kFull,
        kMerge,
        kRetrieve
};

void runGrid(AliAnalysisManager &mgr, GridRunMode gridMode) {
  AliAnalysisAlien *alienHandler = new AliAnalysisAlien();

  // select the aliphysics version. all other packages
  // are LOADED AUTOMATICALLY!
  alienHandler->SetAliPhysicsVersion("vAN-20200201_ROOT6-1");

  // set the Alien API version
  alienHandler->SetAPIVersion("V1.1x");

  // select the input data
  alienHandler->SetGridDataDir("/alice/data/2018/LHC18m");
  alienHandler->SetDataPattern("*pass2/AOD/*AliAOD.Muons.root");

  // MC has no prefix, data has prefix 000
  alienHandler->SetRunPrefix("000");

  // runnumber
  TString inputFile = gSystem->GetFromPipe("cat run.list"); 
  alienHandler->AddRunList(inputFile.Data());
  //alienHandler->AddRunNumber(290223);
  //alienHandler->AddRunNumber(291037);

  alienHandler->SetAnalysisMacro("runMuMuMinv.C");

  // number of files per subjob
  alienHandler->SetSplitMaxInputFileNumber(100);
  alienHandler->SetExecutable("run_mumu_minv.sh");

  // specify how many seconds your job may take
  alienHandler->SetTTL(35000);
  alienHandler->SetJDLName("run_mumu_minv.jdl");

  alienHandler->SetOutputToRunNo(kTRUE);
  alienHandler->SetKeepLogs(kTRUE);

  alienHandler->SetMaxMergeStages(1);
  alienHandler->SetMergeViaJDL(gridMode==GridRunMode::kRetrieve ? kFALSE:kTRUE);

  // define the output folders
  alienHandler->SetGridWorkingDir("Analysis/LHC18m");
  alienHandler->SetGridOutputDir("output");

  // connect the alien plugin to the manager
  mgr.SetGridHandler(alienHandler);
  if (gridMode==GridRunMode::kTest) {
    // specify how many files you want to run
    alienHandler->SetNtestFiles(1);
    // and launch the analysis
    alienHandler->SetRunMode("test");
    mgr.StartAnalysis("grid");
  } else {
    // else launch the full grid analysis
    if (gridMode!=GridRunMode::kRetrieve && gridMode!=GridRunMode::kMerge) {
      alienHandler->SetRunMode("full");
    } else {
      alienHandler->SetRunMode("terminate");
    }
    mgr.StartAnalysis("grid");
  }
}

void runLocal(AliAnalysisManager &mgr, bool debug) {
  const char *filelist = "list.aod.txt";
  if (gSystem->AccessPathName(filelist) == kTRUE) {
    std::cout << "MUST have a list.aod.txt to run in local mode\n", exit(1);
  }

  TChain *c = new TChain("aodTree");
  std::ifstream in(filelist);
  std::string line;
  while (std::getline(in, line)) {
    c->Add(line.c_str());
  }
  if (debug) {
    mgr.SetNSysInfo(10);
    mgr.SetDebugLevel(10);
  }
  TStopwatch timer;
  mgr.StartAnalysis("local", c);
  timer.Print();
  if (debug) {
    mgr.ProfileTask("AliAnalysisTaskMuMu");
  }
}

AliAnalysisTask *runMuMu(GridRunMode gridMode = kLocal,
                         Bool_t simulations = kFALSE, 
                         const char *addtask = "AddTaskMuMuMinv") {

  AliAnalysisManager *mgr = new AliAnalysisManager("MuMu");

  mgr->SetInputEventHandler(new AliAODInputHandler());

  TString triggers, inputs;

  GetTriggerList(simulations, triggers, inputs);

  TString outputname = addtask;

  outputname.ReplaceAll("AddTask", "");

  AliAnalysisTask *task =
      reinterpret_cast<AliAnalysisTaskMuMu *>(gInterpreter->ExecuteMacro(Form(
          "%s.C(\"%s\",\"%s\",\"%s\",\"%s\",%d)", addtask, outputname.Data(),
          triggers.Data(), inputs.Data(), "pp", simulations)));

  if (!mgr->InitAnalysis()) {
    std::cout << "Could not InitAnalysis" << std::endl;
    return 0x0;
  }

  mgr->PrintStatus();
  task->Print();

  if (gridMode==GridRunMode::kLocal) {
    bool debug = false;
    runLocal(*mgr, debug);
  } else {
    runGrid(*mgr, gridMode);
  }

  AliCodeTimer::Instance()->Print();

  return task;
}

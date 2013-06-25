////////////////////////////////////////////////////////////////////////////////
//
//    FILE: RunProof.C
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: 2010
//
// CONTENT: Main macro to run over MiniTrees or TESCO Trees using PROOF
//          in PROOF-Lite, PROOF-Cluster or Sequential mode
//
////////////////////////////////////////////////////////////////////////////////

TProof* proof = 0;

Double_t G_Event_Weight = 1;
Double_t G_Event_Lumi   = 5311.0;   

void RunTree(TString  sampleName      = "TTbar_Madgraph",
	      TString  selector       = "TreeAnalysisTop",
              TString  fileSuffix     = "",
              TString  sampleSys      = "", // for systematic samples, indicate which source is going to be studied -> to be added in the histo name
	      Double_t lumiForPUdata  = 5311.0, // luminosity in http://www.hep.uniovi.es/jfernan/PUhistos/Data2012/
	      Int_t    sys_source     = -1,    // -1 nominal; enum sys_sources { sys_jes = 0, sys_jer, sys_les};
	      Int_t    sys_direction  = -1,    // -1 nominal; enum sys_directions { sys_Up = 0, sys_Nom, sys_Down};
	      Long64_t nEvents        = -1)
{

  // This loads all the PROOF Analysis Framework utilities
  gROOT->LoadMacro("$PAFPATH/PAF.C");

  cout << "Params: " << endl;
  cout << "sampleName      " << sampleName    << endl;
  cout << "selector        " << selector      << endl;
  cout << "fileSuffix      " << fileSuffix    << endl;
  cout << "sampleSys       " << sampleSys     << endl;
  cout << "lumiForPUdata   " << lumiForPUdata << endl;
  cout << "sys_source      " << sys_source    << endl;
  cout << "sys_direction   " << sys_direction << endl;
  cout << "nEvents         " << nEvents       << endl;

  // PROOF settings - see scripts/PAFOptions.h
  //----------------------------------------------------------------------------

  // PROOF mode
  //----------------------------------------------------------------------------
  //gPAFOptions->proofMode = kLite;             // PROOF Lite
  gPAFOptions->proofMode = kCluster;            // PROOF Cluster
  //gPAFOptions->proofMode = kSequential;       // No PROOF

  gPAFOptions->NSlots = 6;                   // Number of slots

  // Optional parameters for PROOF Cluster mode
  // gPAFOptions->proofServer = "proof.ifca.es";  // PROOF server
  // gPAFOptions->proofServerPort = 1093;         // PROOF port
  // gPAFOptions->maxSlavesPerNode = 9999;        // Max number of slaves / node

  // PROOF start
  //----------------------------------------------------------------------------
  cout << ">> Starting PROOF..." << endl;
  proof = InitProof();
  if (!proof && gPAFOptions->proofMode != kSequential) {
    cerr << "ERROR: I could not initialise a PROOF session!" << endl;
    return;
  }
  if (gPAFOptions->proofMode != kSequential) gPAFOptions->proofSession->SetLogLevel(2, TProofDebug::kOutput); 
 
  // Tree type
  //----------------------------------------------------------------------------
  gPAFOptions->SetTreeType(kMiniTrees);

  // Base path to input files
  //----------------------------------------------------------------------------
  TString dataPath = "/gpfs/csic_projects/tier3data";     // IFCA   (gridui)
  
  // Read Data and MC information from the google doc table
  gROOT->LoadMacro("/gpfs/csic_users/arodrig/Analysis-Run2012/DatasetManager/DatasetManager.C+");

  //----------------------------------------------------------------------------
  if (sampleName.Contains("ZJets")) {
    
    if(fileSuffix=="0") gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_ZJets_Madgraph_0.root");
    if(fileSuffix=="1") gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_ZJets_Madgraph_1.root");
    if(fileSuffix=="2") gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_ZJets_Madgraph_2.root");
    if(fileSuffix=="3") gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_ZJets_Madgraph_3.root");
    if(fileSuffix=="4") gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_ZJets_Madgraph_4.root");
    
    G_Event_Weight = 3532.8 * G_Event_Lumi / 30459503.;    

  }
  else if (sampleName.Contains("DataMu12")) {

    if(fileSuffix=="A"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleMuA_892_0.root");
    }
    if(fileSuffix=="B1"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleMuB_4404_0.root");
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleMuB_4404_1.root");
    }
    if(fileSuffix=="B2"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleMuB_4404_2.root");
    }

    G_Event_Weight = 1.;
  }
  else if (sampleName.Contains("DataEG12")) {

    if(fileSuffix=="A"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleElectronA_892_0.root");
    }
    if(fileSuffix=="B"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleElectronB_4404_0.root");
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_DoubleElectronB_4404_1.root");
    }

    G_Event_Weight = 1.;
  }
  else if (sampleName.Contains("DataMuEG12")) {
    
    if(fileSuffix=="A"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_MuEGA_892.root");
    }
    if(fileSuffix=="B"){
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_MuEGB_4404_0.root");
    gPAFOptions->dataFiles.push_back("/gpfs/csic_projects/tier3data/MC_Summer12_53X/NewJEC/Tree_MuEGB_4404_1.root");
    }
    G_Event_Weight = 1.;
    
  }
  else {

    DatasetManager *dm = new DatasetManager("Summer12_53X","NewJEC");

    // Use this if you know that the information on the google doc table has
    // changed and you need to update the information
    dm->RedownloadFiles();

    dm->LoadDataset(sampleName);  // Load information about a given dataset

    G_Event_Weight = dm->GetCrossSection() * G_Event_Lumi / dm->GetEventsInTheSample();
  
    cout << endl;
    cout << "      x-section = " << dm->GetCrossSection()      << endl;
    cout << "     luminosity = " << G_Event_Lumi               << endl;
    cout << "        nevents = " << dm->GetEventsInTheSample() << endl;
    cout << " base file name = " << dm->GetBaseFileName()      << endl;
    cout << endl;

    gPAFOptions->dataFiles = dm->GetFiles();
  }

  cout << " G_Event_Weight = " << G_Event_Weight << endl;

  // Output file name
  //----------------------------------------------------------------------------
  TString outputDir = "/gpfs/csic_users/arodrig/Analysis-Run2012/TopAnalysis-NewJEC-BTagMoriond2013-Master/TopResults/Summer12/root";
 
  gSystem->mkdir(outputDir, kTRUE);
  
  std::ostringstream oss;      
  oss << G_Event_Lumi;

  TString LumiString = oss.str();

  TString outputFile = outputDir
    + "/"
    + selector
    + "_Dilep" 
    + "_"
    + LumiString
    + "pb-1_"
    + sampleName
    + fileSuffix
    + sampleSys
    + ".root";
  
  gPAFOptions->outputFile = outputFile;

  // Parameters for the analysis
  //----------------------------------------------------------------------------
  // See packages/InputParameters/InputParameters.h for information on how
  // to use this class.

  gPAFOptions->inputParameters = new InputParameters();

  gPAFOptions->inputParameters->SetNamedString("sampleName",   sampleName.Data());
  gPAFOptions->inputParameters->SetNamedDouble("weight",       G_Event_Weight);

  gPAFOptions->inputParameters->SetNamedInt("sys_source",     sys_source);
  gPAFOptions->inputParameters->SetNamedInt("sys_direction",  sys_direction);

  gPAFOptions->inputParameters->SetNamedDouble("luminosity",   lumiForPUdata);  // PU 73.5mb

  gPAFOptions->inputParameters->SetNamedString("fileSuffix",   fileSuffix.Data());

  // Dynamic histograms
  //----------------------------------------------------------------------------
  //  gPAFOptions->dynamicHistograms.push_back("myHistogram");
  
  // Number of events (Long64_t)
  //----------------------------------------------------------------------------
  gPAFOptions->SetNEvents(nEvents);
  // First event (Long64_t)
  //----------------------------------------------------------------------------
  gPAFOptions->SetFirstEvent(0);
  
  // Name of analysis class
  //----------------------------------------------------------------------------
  // If 0 the default name schema will be used, i.e. depending on the value
  // of gPAFOptions->treeType: MyAnalysisTESCO or MyAnalsyisMiniTrees

  gPAFOptions->SetAnalysis(selector.Data());

  // Additional packages to be uploaded to PROOF
  //----------------------------------------------------------------------------
  gPAFOptions->AddPackage("PUWeight");
  gPAFOptions->AddPackage("BTagSFUtil");

  // Control output and checks
  //----------------------------------------------------------------------------
  // + If true (default) PAF checks for new version in CVS every time
  // gPAFOptions->checkVersion = true;
  // + If true (default) the output file is reopened so the objects in the
  //   file can be interactively accessed. The object in the output are also
  //   listed

  gPAFOptions->reopenOutputFile = false;

  // Run the analysis
  //----------------------------------------------------------------------------
  if (!RunAnalysis())
    cerr << "ERROR: There was a problem running the analysis!" << endl;
}

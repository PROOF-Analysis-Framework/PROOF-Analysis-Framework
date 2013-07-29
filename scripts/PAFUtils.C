///////////////////////////////////////////////////////////////////////
//
//    FILE: StartProof.C
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: January, 2011
//
// CONTENT: Implements the functionality needed to run an Analysis
//          using the PROOF Analysis Framework (PAF). Some more helper
//          functions may be found in PAFCompiledUtils.h/C
//
///////////////////////////////////////////////////////////////////////

// Include the singleton where the options are stored.
#include "PAFOptions.C"
// Some definitions...
#include "PAF.h"

// Plugins for the different PAF Modes
#include "PAFModePlugin.h"
// #include "PoDPlugin.h"
// #include "PROOFLitePlugin.h"
// #include "PROOFClusterPlugin.h"
// #include "PROOFCloudPlugin.h"



// Uncomment the line below to get information on time spent at each step
// This setting may also be defined in the main user code from a clean 
// session.
//#define TIMERS
#ifdef TIMERS
double PAFTime0; //InitProof
double PAFTime1; //Building dataset
double PAFTime2; //Create base selector
double PAFTime3; //Include path
double PAFTime4; //Loading packages
double PAFTime5; //Compile selector
double PAFTime6; //Parameters and dynamic histograms
double PAFTime7; //Processing data
double PAFTime8; //Output file
#endif

// The PAF Mode Plugin that will be used depending on the 
// PAF Mode selected
PAFModePlugin* gPAFModePlugin = 0;

// Creates a session dir and sets the build dir there
bool CreateSessionDir() {
  // XXX: errors are not properly catched here!
  TString dir = gSystem->GetFromPipe("mktemp -d");
  // - And let's set the build dir there so nothing interferes in the
  //   PAF directory installation
  if (dir == "") {
    return false;
  }
  gSystem->SetBuildDir(dir);
  TString ProofSandboxDir;
  ProofSandboxDir.Form("%s/.proof", dir.Data());
  gEnv->SetValue("Proof.Sandbox", ProofSandboxDir);
  return true;
}





///////////////////////////////////////////////////////////////////////
//
// Function to initialize the PROOF session depending on the mode 
// selected
//
TProof* InitProof() {
#if DEBUGUTILS
  cerr << PAFDEBUG << ">> InitProof(" << gPAFOptions->GetPAFMode() 
       << ")" << endl;
#endif
#ifdef TIMERS
  cout << PAFINFO << "Setting up InitProof timer..." << endl;
  TStopwatch PAFTimer;
  PAFTimer.Start();
#endif

  ProofMode pm = gPAFOptions->GetPAFMode();


  ///////////////////
  // Use plugins where possible
  //
  cout << PAFINFO << "+ Loading PAF Mode Plugin for the selected mode" << endl;

  // ++ PoD
  if (pm == kPoD) {
    gROOT->LoadMacro("$PAFPATH/scripts/PoDPlugin.C");
    gPAFModePlugin = new PoDPlugin(gPAFOptions->GetNSlots(),
				   gPAFOptions->GetMaxSlavesPerNode(), 
				   gPAFOptions->GetPoDTimeOut());
  }

  // ++ PROOF Lite
  else if (pm == kLite) {
    gROOT->LoadMacro("$PAFPATH/scripts/PROOFLitePlugin.C");
    gPAFModePlugin = new PROOFLitePlugin(gPAFOptions->GetNSlots());
  }

  // ++ PROOF Cluster
  else if (pm == kCluster) {
    gROOT->LoadMacro("$PAFPATH/scripts/PROOFClusterPlugin.C");
    gPAFModePlugin = new PROOFClusterPlugin(gPAFOptions->GetNSlots(),
					    gPAFOptions->GetMaxSlavesPerNode());
  }
  
  // ++ Cloud
  else if ( pm == kCloud ) {
    gROOT->LoadMacro("$PAFPATH/scripts/PROOFCloudPlugin.C");
    gPAFModePlugin = new PROOFCloudPlugin(gPAFOptions->GetNSlots(),
					  gPAFOptions->proofRequest,
					  gPAFOptions->proofServer,
					  gPAFOptions->proofServerPort);
  }

  // ++ Sequential
  else if (pm == kSequential) {
    gROOT->LoadMacro("$PAFPATH/scripts/SequentialPlugin.C");
    gPAFModePlugin = new SequentialPlugin();

  } 
  // ++ Something else
  else {
    cerr << PAFERROR << "You have chosen a PROOF mode (" 
	 << gPAFOptions->GetPAFMode() << ") not yet implemented" << endl;
    cerr << PAFERROR << "Exiting!" << endl;
    return 0;
  }




  ///////////////////
  // Initial checks
  //

  if (!gPAFModePlugin->InitialChecks())
    return false;





  ///////////////////
  // Set build dir
  //
  if (!CreateSessionDir()) {
    cerr << PAFERROR << "Unable to continue without a valid build dir!" << endl;
    cerr << PAFERROR << "Exiting!" << endl;
    return 0;
  }


  // Check PAF Version (no more needed)
  //if (gPAFOptions->checkVersion)
  //  gSystem->Exec("$PAFPATH/bin/checkversion.sh&");




  ///////////////////
  // Start PROOF
  //

  gPAFOptions->proofSession = gPAFModePlugin->Init();



  ///////////////////
  // Load extra utils
  //

  // ++ PAFCompiledUtils
  gROOT->LoadMacro("$PAFPATH/scripts/PAFCompiledUtils.C+");

  // ++ Load or Enable InputParameters
  vector<TString> ip;
  ip.push_back("InputParameters");
  if (gPAFOptions->GetPAFMode() == kSequential) {
    LoadPackages(ip, false);
  } else {
    UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), ip, false);
  }


#ifdef TIMERS
  PAFTime0 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (InitProof): " << PAFTime0 << endl;
#endif

#if DEBUGUTILS
  cerr << PAFDEBUG << "<< InitProof(" << gPAFOptions->GetPROOFSession() << ")" << endl;
#endif
  return gPAFOptions->GetPROOFSession();
}
//
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//
// Functions needed to run the analysis
//

///////////////////////////////
//
// Set include path
//
void SetIncludePath() {
  // XXX this is a noop, should be removed!
  TString pwdpath = "-I";
  pwdpath+=gSystem->pwd(); //path to local dir
  TString curpath = gSystem->GetIncludePath(); //current path
#if DEBUGUTILS
  cerr << PAFDEBUG << "+ Current PWD path in the master is \"" 
       << pwdpath << "\"" << endl;
  cerr << PAFDEBUG << "+ Current include path in the master is \"" 
       << curpath << "\"" << endl;
#endif
}

/////////////////////////////////
// Load Packages (used in sequential mode)
//
void LoadPackages(const vector<TString>& packages, bool isSelector) {
  TString packages_dir;
  packages_dir.Form("%s/packages/", gSystem->GetBuildDir());
  gSystem->MakeDirectory(packages_dir);

  TString pwddir = gSystem->pwd();
  for (unsigned int i = 0; i < packages.size(); i++) {
    cout << PAFINFO << "Creating package " << packages[i] << "... " << endl; 
    
#if DEBUGUTILS
    cerr << PAFDEBUG << "+ par file... " << endl;
#endif
    BuildParFile(packages[i], isSelector);
    
    //This is equivalent to enable package
    gSystem->ChangeDirectory(packages_dir + packages[i]);

#if DEBUGUTILS    
    cerr << PAFDEBUG << "In directory " << gSystem->pwd() << endl;
#endif

    // + First execute BUILD.sh
#if DEBUGUTILS    
    cerr << PAFDEBUG << "building... " << endl;
#endif
    gSystem->Exec("./PROOF-INF/BUILD.sh");
    // + Then load and execute SETUP.C
#if DEBUGUTILS    
    cerr << PAFDEBUG << "loading... " << endl;
#endif
    gROOT->LoadMacro("PROOF-INF/SETUP.C");
    SETUP();
    // ENOL: SETUP seems not to work for me :( XXX
    // Manually loading the library
    gSystem->Load("lib"+packages[i]);

    // Changes for root 5.34: add the package to the include path
    gSystem->AddIncludePath("-I" + packages_dir + packages[i]);
    
    //Back to the pwd directory
    gSystem->ChangeDirectory(pwddir);
  }
}


///////////////////////////////
//
// Run the full analysis
// This function assumes the PROOF session is already initialised (if not
// InitProof() should be called before. It returns true if everything went
// fine, or false otherwise.
//

bool RunAnalysis() {
#ifdef TIMERS
  cout << PAFINFO << "+ Setting up timers..." << endl;
  TStopwatch PAFTimer;
  PAFTimer.Start();
#endif

  //
  // If we are in a PROOF like session, check it was initialized
  //
  if (gPAFOptions->GetPAFMode() != kSequential && (!gPAFOptions->GetPROOFSession())) {
    cerr << PAFERROR "The PROOF Session was not initialized in RunAnalysis()"
	 << endl
         << PAFERROR << "Exiting! " << endl;
    return false;
  }

  //Get Selector
  TString selector = gPAFOptions->GetAnalysis();
  
  //
  //Data
  //
  cout << PAFINFO << ">> Building dataset..." << endl;

  if (gPAFOptions->dataFiles.size() < 1) {
    cerr << PAFERROR << "Cannot continue with an empty dataset" << endl
         << PAFERROR << "Exiting!" << endl;
    return false;
  }
  
  // In sequetial mode create TChain
  TString chainname;
  if (gPAFOptions->GetTreeDir() != "" )
    chainname = gPAFOptions->GetTreeDir() + "/" + gPAFOptions->GetTreeName();
  else
    chainname = gPAFOptions->GetTreeName();
  TChain* tchaindataset = new TChain(chainname); // For all modes

  for (unsigned int i = 0; i < gPAFOptions->dataFiles.size(); i++)
    tchaindataset->Add(gPAFOptions->dataFiles[i]);

#if DEBUGUTILS
  cerr << PAFDEBUG << "Files in dataset:" << endl;
  tchaindataset->GetListOfFiles()->Print();
#endif

#ifdef TIMERS
  //PAFTIME1
  PAFTime1 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Building dataset): " << PAFTime1 << endl;
  PAFTimer.Start();
#endif

  //
  //Make selector
  if (gPAFOptions->createSelector) {
    cout << PAFINFO << ">> Creating Selector..." << endl;
    TString pkgName;
    if (!CreateSelector(gPAFOptions->dataFiles[0], pkgName,
			gPAFOptions->GetTreeDir(), 
			gPAFOptions->GetTreeName(),
			gPAFOptions->GetAnalysis(),
			gPAFOptions->GetSelectorPackages())) {
        cerr << PAFERROR "Error creating selector..." << endl;
        return false;
    } else {
        gPAFOptions->AddSelectorPackage(pkgName); 
    }
  } else {
    // XXX try to use an already existing PAFAnalysis package !?
    cerr << PAFWARN << "No Selector created, your code will probably fail!" << endl;
  }

#ifdef TIMERS
  //PAFTIME2
  PAFTime2 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Create base selector): " << PAFTime2 << endl;
  PAFTimer.Start();
#endif

  //
  // Set include path
  cout << PAFINFO << ">> Setting include path..." << endl;
  SetIncludePath();

#ifdef TIMERS
  //PAFTIME3
  PAFTime3 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Include path): " << PAFTime3 << endl;
  PAFTimer.Start();
#endif

  //
  // Upload and enable packages / Load packages
  cout << PAFINFO << ">> Loading packages ..." << endl;
  if (gPAFOptions->GetPAFMode() == kSequential) {
    LoadPackages(gPAFOptions->GetPackages(), false);
    LoadPackages(gPAFOptions->GetSelectorPackages(), true);
  }
  else {
    UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), 
			    gPAFOptions->GetPackages(), false);
    UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), 
			    gPAFOptions->GetSelectorPackages(), true);
  }


#ifdef TIMERS
  //PAFTIME4
  PAFTime4 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Loading packages): " << PAFTime4 << endl;
  PAFTimer.Start();
#endif

  //
  // Compile Selector
  //
  TString selectorcfile = selector + ".C";
  TString selectorhfile = selector + ".h";

  TString dest = gSystem->GetBuildDir();
  dest += "/";
  dest += selectorcfile;

  if (gSystem->CopyFile(selectorcfile, dest)) {
      cerr << PAFERROR << "Could not copy " << selectorcfile << " to temp directory" << endl;
      return false;
  }

  if (gSystem->FindFile(".", selectorhfile)) {
    dest.Replace(dest.Length() - 1, dest.Length(), "h");
    if (gSystem->CopyFile(selectorhfile, dest)) {
      cerr << PAFERROR << "ERROR: Could not copy " << selectorhfile << " to temp directory" << endl;
      return false;
    }
  }

  // Selector
  TString selectorcplus = selectorcfile; 
  selectorcplus+= "++";
  PAFBaseSelector *pafbaseselector = 0;

  if (gPAFOptions->GetPAFMode() == kSequential) {
    cout << PAFINFO << ">> Creating selector..." << endl;
    pafbaseselector = (PAFBaseSelector*)TSelector::GetSelector(selectorcplus);
  }

#ifdef TIMERS
  //PAFTIME5
  PAFTime5 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Compile selector): " << PAFTime5 << endl;
  PAFTimer.Start();
#endif
  

  //  
  // Add the set of parameters to the input lists
  //
  if (gPAFOptions->inputParameters) {
    cout << PAFINFO << ">> Adding input parameters..." << endl;
    
    if (gPAFOptions->GetPAFMode() == kSequential) {
      TList* inputlist = new TList;
      if (gPAFOptions->inputParameters) {
	inputlist->Add(gPAFOptions->inputParameters);
      }
      pafbaseselector->SetInputList(inputlist);
    }
    else {
      if (gPAFOptions->inputParameters) {
	gPAFOptions->GetPROOFSession()->AddInput(gPAFOptions->inputParameters);
      }
    }
  }

  //
  // Add dynamic histograms (feedback)
  //
  if (gPAFOptions->GetPAFMode() != kSequential && 
      gPAFOptions->dynamicHistograms.size() > 0) {
    cout << PAFINFO << ">> Adding dynamic histograms (Feedback)" << endl;
    for (unsigned int i = 0; 
	 i < gPAFOptions->dynamicHistograms.size(); 
	 i++) {
      cout << PAFINFO << "+ " << gPAFOptions->dynamicHistograms[i] << endl;
      gPAFOptions->GetPROOFSession()->AddFeedback(gPAFOptions->dynamicHistograms[i]);
    }
    new TDrawFeedback(proof);
  }
  else {
#if DEBUGUTILS
    cerr << PAFDEBUG << ">> No dynamic histograms (Feedback)" << endl;
#endif
  }
#ifdef TIMERS
  PAFTime6 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Parametes and dynamic histograms): " 
       << PAFTime6 << endl;
  PAFTimer.Start();
#endif

  //
  // Processing...
  //
  cout << PAFINFO << ">> Processing " << selector << " in ";
  if (gPAFOptions->GetPAFMode() == kSequential) {
    cout << "sequential mode..." << endl;
    cerr << PAFWARN << "Note that no dialog or progressing bar will be shown!" << endl;
  }
  else {
    cout << gPAFOptions->GetPROOFSession()->GetParallel() << " nodes..." << endl;
  }

  Long64_t nevents    = gPAFOptions->GetNEvents();
  Long64_t firstevent = gPAFOptions->GetFirstEvent();
  cout << PAFINFO << "+ ";  
  if (nevents == TChain::kBigNumber) cout << "All"; else cout << nevents;
  cout << " events will be scanned, starting";
  if (firstevent)
    cout << " on event " << firstevent << endl;
  else
    cout << " at first event" << endl;
  if (gPAFOptions->GetPAFMode() == kSequential) {
    tchaindataset->Process(pafbaseselector, 0, nevents, firstevent);
  }
  else {
    tchaindataset->SetProof();
    tchaindataset->Process(selectorcplus, 0, nevents, firstevent);
  }

#ifdef TIMERS
  PAFTime7 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Processing data): " << PAFTime7 << endl;
  PAFTimer.Start();
#endif

  //
  // Create the ouptut file and fill it
  //
  cout << PAFINFO << ">> Saving results to " << gPAFOptions->outputFile << " ..." << endl;
  if (gSystem->FindFile(".", TString(gPAFOptions->outputFile))) {
    TString outputFileBak = gPAFOptions->outputFile + ".bak";
    cerr << PAFWARN << "File " << gPAFOptions->outputFile << " already exists! "
         << "Moving it to " << outputFileBak << endl;
    gSystem->CopyFile(gPAFOptions->outputFile, outputFileBak, kTRUE);
    gSystem->Unlink(gPAFOptions->outputFile);
  }
  TFile histoAnalysis(gPAFOptions->outputFile, "NEW");
  if (histoAnalysis.IsOpen()) {
    TList* li = 0;
    TList* lo = 0;
    if (gPAFOptions->GetPAFMode() == kSequential) {
      li = inputlist;
      lo = pafbaseselector->GetOutputList();
    }
    else {
      li = gPAFOptions->GetPROOFSession()->GetInputList();
      lo = gPAFOptions->GetPROOFSession()->GetOutputList();
    }
    li->Write();
    lo->Write();
    histoAnalysis.Close();

    //
    // This is used to have the objects available in the shell
    // XXX should only be done if interactive!?
    //
    if (gPAFOptions->reopenOutputFile) {
      cout << PAFINFO << ">> You may directly access the following objects that you saved ..."
           << endl;
      TFile *f = TFile::Open(gPAFOptions->outputFile);
      f->ls();
    }
  }
  else {
    cerr << PAFERROR << "Could not open output file " << gPAFOptions->outputFile
	 << endl;
  }
  
  if (gPAFModePlugin)
    gPAFModePlugin->Finish();

#ifdef TIMERS
  PAFTime8 = PAFTimer.RealTime();
  cout << PAFINFO << "  + TIME (Output file): " << PAFTime8 << endl;

  ofstream ftimes(Form("tiempos_ejecucion%d", gPAFOptions->GetNSlots()),
		   ios::app);
  ftimes << Form("%f;%f;%f;%f;%f;%f;%f;%f;%f;\n",
		 PAFTime0,
		 PAFTime1, PAFTime2, PAFTime3, PAFTime4,
		 PAFTime5, PAFTime6, PAFTime7, PAFTime8);
  ftimes.flush();
  ftimes.close();
#endif


  return true;
}
//
///////////////////////////////////////////////////////////////////////

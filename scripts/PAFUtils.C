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

// Some definitions...
#include "PAF.h"

// Include the singleton where the options are stored.
#include "PAFOptions.C"

// ROOT includes
#include "TNamed.h"
#include "TProof.h"
#include "TEnv.h"
#include "TROOT.h"
#include "TFile.h"
#include "TDrawFeedback.h"


// Plugins for the different PAF Modes
#include "PAFModePlugin.h"

// Uncomment to try to compile
// #include "PoDPlugin.h"
// #include "PROOFLitePlugin.h"
// #include "PROOFClusterPlugin.h"
// #include "PROOFCloudPlugin.h"
// #include "SequentialPlugin.h"
//class PROOFLitePlugin;
//class PROOFClusterPlugin;
//class PROOFCloudPlugin;

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
  cout << PAFINFO << "Creating buildir and proof sand box" << endl;
  // XXX: errors are not properly catched here!
  TString tmpdir = gSystem->GetFromPipe("mktemp -d");
  // - And let's set the build dir there so nothing interferes in the
  //   PAF directory installation
  if (tmpdir == "") {
    return false;
  }
  TString ProofSandboxDir = Form("%s/.proof", tmpdir.Data());
  TString builddir = tmpdir;


  
  //XXX I.G. Why not set everything to ~/.paf... so we avoid problems in
  //    cleaning the tmp area?
  //    This does not work directly like that
  //TString builddir = "~/.paf/BuildDir";
  //TString ProofSandboxDir = "~/.paf/Sandbox";
  //gSystem->mkdir(builddir.Data(),true);
  //gSystem->mkdir(ProofSandboxDir.Data(),true);
  
#if DEBUGUTILS
  cerr << PAFDEBUG << "BuilDir set to " << builddir << endl;
  cerr << PAFDEBUG << "Sandbox set to " << ProofSandboxDir << endl;
#endif
  
  gSystem->SetBuildDir(builddir);
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

  EProofMode pm = gPAFOptions->GetPAFMode();



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







  // Check PAF Version (no more needed)
  //if (gPAFOptions->checkVersion)
  //  gSystem->Exec("$PAFPATH/bin/checkversion.sh&");




  ///////////////////
  // Start PROOF
  //

  gPAFOptions->SetPROOFSession(gPAFModePlugin->Init());
  if (gPAFOptions->GetPROOFSession()) {
    cout << PAFINFO << "Setting PROOF to use mergers..." << endl;
    gPAFOptions->GetPROOFSession()->SetParameter("PROOF_UseMergers", (Int_t)0);
  }
  else if (gPAFOptions->GetPAFMode() != kSequential) {
    cerr << PAFERROR << "Could not start session!!!" << endl;
    cerr << PAFERROR << "Exiting!" << endl;
    return 0;
  }
  
  ///////////////////
  // Set build dir and sandbox
  //
  if (!CreateSessionDir()) {
    cerr << PAFERROR << "Unable to continue without a valid build dir!" << endl;
    cerr << PAFERROR << "Exiting!" << endl;
    return 0;
  }
  
  
  
  ///////////////////
  // Load extra utils
  //
  
  // ++ PAFCompiledUtils
  cout << PAFINFO << "Compiling PAF extra utils..." << endl;
  if (gROOT->LoadMacro("$PAFPATH/scripts/PAFCompiledUtils.C+") !=0) {
    cerr << PAFERROR << "Could not compile$PAFPATH/scripts/PAFCompiledUtils.C" << endl;
    cerr << PAFERROR << "Exiting" << endl;
    return 0;
  }
  
  // ++ Load or Enable InputParameters
  vector<TString> ip;
  ip.push_back("InputParameters");
  if (gPAFOptions->GetPAFMode() == kSequential) {
    LoadPackages(ip, false);
  } else if (!UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), 
				      ip, false)) {
    return 0;
  }
  
  
#ifdef TIMERS
  PAFTime0 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (InitProof): " << PAFTime0 << endl;
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
  cout << PAFINFO << "+++ TIME (Building dataset): " << PAFTime1 << endl;
  PAFTimer.Start();
#endif

  //
  //Make selector
  if (gPAFOptions->ShouldCreateSelector()) {
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
  cout << PAFINFO << "+++ TIME (Create base selector): " << PAFTime2 << endl;
  PAFTimer.Start();
#endif

  //
  // Set include path
  cout << PAFINFO << ">> Setting include path..." << endl;
  SetIncludePath();

#ifdef TIMERS
  //PAFTIME3
  PAFTime3 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Include path): " << PAFTime3 << endl;
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
    if (!UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), 
				 gPAFOptions->GetPackages(), false))
      return false; 
    if (!UploadAndEnablePackages(gPAFOptions->GetPROOFSession(), 
				 gPAFOptions->GetSelectorPackages(), true))
      return false;
  }


#ifdef TIMERS
  //PAFTIME4
  PAFTime4 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Loading packages): " << PAFTime4 << endl;
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
  PAFBaseSelector* pafbaseselector = 0;

  if (gPAFOptions->GetPAFMode() == kSequential) {
    cout << PAFINFO << ">> Creating selector..." << endl;
    pafbaseselector = (PAFBaseSelector*) TSelector::GetSelector(selectorcplus);
  }

#ifdef TIMERS
  //PAFTIME5
  PAFTime5 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Compile selector): " << PAFTime5 << endl;
  PAFTimer.Start();
#endif
  

  //  
  // Add the set of parameters and some other stuffto the input lists
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
      TProof* p = gPAFOptions->GetPROOFSession();
      if (gPAFOptions->inputParameters) {
	p->AddInput(gPAFOptions->inputParameters);
      }
      //Define if should merge through
      p->AddInput(new TNamed("PAF_MergeThroughFile",
			     gPAFOptions->GetMergeThroughFile()?"true":"false"));
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
    new TDrawFeedback(gPAFOptions->GetPROOFSession());
  }
  else {
#if DEBUGUTILS
    cerr << PAFDEBUG << ">> No dynamic histograms (Feedback)" << endl;
#endif
  }
#ifdef TIMERS
  PAFTime6 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Parametes and dynamic histograms): " 
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
  if (nevents == TChain::kBigNumber)
    cout << "All"; 
  else 
    cout << nevents;
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
    const char* options = 0;
    if (gPAFOptions->GetMergeThroughFile()) {
      if (BackupFile(gPAFOptions->GetOutputFile().Data()))
	cerr << PAFWARN << "+ File \"" << gPAFOptions->GetOutputFile() 
	     << "\" already exists! It has been backed up."
	     << endl;
      
      TString of = Form("of=%s;stf", gPAFOptions->GetOutputFile().Data());
      options=of.Data();
    }
    tchaindataset->Process(selectorcplus, options, nevents, firstevent);
  }

#ifdef TIMERS
  PAFTime7 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Processing data): " << PAFTime7 << endl;
  PAFTimer.Start();
#endif

  //
  // If not merging throug file, let's create the ouptut file and fill it
  //
  if (!gPAFOptions->GetMergeThroughFile()) {
    cout << PAFINFO << ">> Saving results to \"" 
	 << gPAFOptions->GetOutputFile() << "\"..." << endl;

    // Backup the output file if it already exists
    if (BackupFile(gPAFOptions->GetOutputFile().Data()))
      cerr << PAFWARN << "+ File \"" << gPAFOptions->GetOutputFile() 
	   << "\" already exists! It has been backed up."
	   << endl;

    // Open file and store objects
    cout << PAFINFO << "+ Opening new file \""
	 << gPAFOptions->GetOutputFile() << "\"..." << endl;
    TFile* histoAnalysis = TFile::Open(gPAFOptions->GetOutputFile(), 
				       "NEW", "PAFOutputFile");
    if (!histoAnalysis->IsZombie()) {
      cout << PAFINFO << "+ Saving objects in input and output lists"
	   << endl;
      TList* li = 0;
      TList* lo = 0;
      if (gPAFOptions->GetPAFMode() == kSequential) {
	//XXX Is this working???
	li = pafbaseselector->GetInputList()
	  lo = pafbaseselector->GetOutputList();
      }
      else {
	li = gPAFOptions->GetPROOFSession()->GetInputList();
	lo = gPAFOptions->GetPROOFSession()->GetOutputList();
      }
      li->Write();
      lo->Write();
      histoAnalysis->Close();
    }
    else {
      cerr << PAFERROR << "  + Could not open output file \"" << of 
	   << "\"" << endl;
    }
  }

  //
  // This is used to have the objects available in the shell
  // It is only done if we are in an interactive session
  //
  if (gPAFOptions->ShouldReopenOutputFile() && !gROOT->IsBatch()) {
    cout << PAFINFO << ">> Reopening the file in current session..."
	 << endl;
    TFile *f = TFile::Open(gPAFOptions->GetOutputFile());
    if (f) {
      cout << PAFINFO << ">> You may now directly access all the saved objects."
	   << endl
	   << PAFINFO << "   The list of available obects is:"
	   << endl;
      f->ls();
    }
  }



  /***************************



  //
  // Create the ouptut file and fill it
  //
  cout << PAFINFO << ">> Saving results to \"" 
       << gPAFOptions->GetOutputFile() << "\"..." << endl;
  if (gSystem->FindFile(".", gPAFOptions->GetOutputFile())) {
    TString outputFileBak = gPAFOptions->GetOutputFile() + ".bak";
    cerr << PAFWARN << "   + File \"" << gPAFOptions->GetOutputFile() << "\" already exists! "
	 << "Moving it to " << outputFileBak << endl;
    gSystem->CopyFile(gPAFOptions->GetOutputFile(), outputFileBak, kTRUE);
    gSystem->Unlink(gPAFOptions->GetOutputFile());
  }
  cout << PAFINFO << "   + Opening new file \""
       << gPAFOptions->GetOutputFile() << "\"..." << endl;
  TFile* histoAnalysis = TFile::Open(gPAFOptions->GetOutputFile(), 
				     "NEW", "PAFOutputFile");
  if (!histoAnalysis->IsZombie()) {
    cout << PAFINFO << "   + Saving objects in input and output lists"
	 << endl;
    TList* li = 0;
    TList* lo = 0;
    if (gPAFOptions->GetPAFMode() == kSequential) {
      //XXX Is this working???
      li = pafbaseselector->GetInputList()
	lo = pafbaseselector->GetOutputList();
    }
    else {
      li = gPAFOptions->GetPROOFSession()->GetInputList();
      lo = gPAFOptions->GetPROOFSession()->GetOutputList();
    }
    li->Write();
    lo->Write();
    histoAnalysis->Close();

    //
    // This is used to have the objects available in the shell
    // XXX should only be done if interactive!?
    //     * DONE with gROOT ->IsBatch()
    //
    if (gPAFOptions->reopenOutputFile && !gROOT->IsBatch()) {
      cout << PAFINFO << "   + Reopening the file in current session..."
	   << endl;
      TFile *f = TFile::Open(of);
      cout << PAFINFO << ">> You may now directly access all the saved objects."
	   << endl
	   << PAFINFO << "   The list of available obects is:"
           << endl;
      f->ls();
    }
  }
  else {
    cerr << PAFERROR << "  + Could not open output file \"" << of 
	 << "\"" << endl;
  }
  ***************************/  

  if (gPAFModePlugin)
    gPAFModePlugin->Finish();
  
#ifdef TIMERS
  PAFTime8 = PAFTimer.RealTime();
  cout << PAFINFO << "+++ TIME (Output file): " << PAFTime8 << endl;

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

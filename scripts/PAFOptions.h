///////////////////////////////////////////////////////////////////////
//
//    FILE: PAFOptions.h
//   CLASS: PAFOptions
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: January, 2011
//
// CONTENT: This file hosts the options and settings important in
//          the PROOF Analysis Framework (PAF). It is a singleton. A 
//          global variable gPAFOptions is created in the 
//          implementation file
//
///////////////////////////////////////////////////////////////////////

#ifndef PAFOptions_h
#define PAFOptions_h 1

// ROOT includes
#include "TString.h"
#include "TChain.h" //For TChain::kBigNumber
#include "TProof.h"

// STL includes
#include <vector>

// InputParameters forward declaration.
// This trick works to have PAFOptions class loaded at the begining.
// The library is loaded afterwards.
class InputParameters;

//////////////////////////////////////////////////////////////////
// The different available proof modes. Read the documentation
// for details:
// * kSequential: No PROOF. Plain sequential code
// * kLite: PROOF Lite mode
// * kCluster: PROOF Cluter mode
// * kPoD: PROOF on Demand mode (NOT yet implemented)
// * kCloud: PROOF on Cloud (basically Cluster mode without fixed root)
enum EProofMode {kSequential, kLite, kCluster, kPoD, kCloud};
const char* kCProofMode[] = {"Sequential", "PROOF Lite", "PROOF Cluster", "PoD", "Cloud"};
//
/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// The different available tree types. Read tge documentation
// for details:
// * kMiniTrees: Flat Trees developed at IFCA-UO
// * kTESCO: Trees developed by the ETH
enum ETreeType {kMiniTrees, kTESCO};
const char* kCTreeType[] = {"MiniTrees", "TESCO"};
//
/////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////
// The PAFOptions class
//
class PAFOptions {
 public:
  void Dump() const;

  
  ///////////////////////////////
  //
  // PROOF Mode. See EProofMode enum for details
  EProofMode proofMode; 
  EProofMode GetPAFMode() const {return proofMode;}
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // Number of slots you would like to use
  // + The default value depends on PROOF Mode
  void SetNSlots(int nslots) {NSlots = nslots;}
  int  GetNSlots() const {return NSlots;}
  int NSlots;
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // PROOF Cluster/Cloud specific variables
  //+ Proof Server name (default is proof.ifca.es)
  TString proofServer;
  //+ Proof Server port (default is 1093)
  Int_t proofServerPort;
  //+ Perform or not the request for nodes (default is True)
  bool proofRequest;
  //+ Maximum number of slaves per node (use 9999 for all)
  void SetMaxSlavesPerNode(int mspn) {maxSlavesPerNode = mspn;}
  int  GetMaxSlavesPerNode() const {return maxSlavesPerNode;}
  int maxSlavesPerNode;
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // PoD specific parameters
  void SetPoDTimeOut (int);
  int  GetPoDTimeOut () const {return fPoDTimeout;}
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // Tree type. It defines the data formats that may be used. See ETreeType
  // enum for details. Default is kMiniTrees
  ETreeType GetTreeType() const { return fTreeType;}
  void SetTreeType(ETreeType tt) {
    fTreeType = tt;
    if (tt == kMiniTrees) {
      fTreeDir  = "";
      fTreeName = "Tree";
      if (fAnalysisFile == "")
	fAnalysisFile = "MyAnalysisMiniTrees";
    }
    else {
      fTreeDir  = "analyze";
      fTreeName = "Analysis";
      if (fAnalysisFile == "")
	fAnalysisFile = "MyAnalysisTESCO";
    }
  }
  void SetTree(const char* t) {TString tt = t; Ssiz_t i= tt.Last('/');fTreeDir=tt(0,i); fTreeName=tt(i+1,tt.Sizeof());}
  TString GetTreeDir() const { return fTreeDir;}
  TString GetTreeName() const { return fTreeName;}
  void SetTreeDir(const char* td) { fTreeDir = td;}
  void SetTreeName(const char* tn) { fTreeName = tn;}
  //
  ///////////////////////////////


  ///////////////////////////////
  // Input data sample
  //
  std::vector<TString> dataFiles;
  void AddDataFile(const char* file) {dataFiles.push_back(file);}
  void AddDataFiles(const std::vector<TString>& files);
  void SetDataFiles(const std::vector<TString>& files) {dataFiles = files;}
  unsigned int GetNDataFiles() const {return dataFiles.size();}
  std::vector<TString> GetDataFiles() const {return dataFiles;}
  void PrintDataFiles() const;
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Output file name. Specifies the name of the file where you want the
  // histograms to be saved
  void SetOutputFile(const char* of) {fOutputFile = of;}
  TString GetOutputFile() const {return fOutputFile;}
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Parameters for the analysis
  InputParameters *inputParameters;

  InputParameters* GetInputParameters();

  void SetInputString(std::string s);
  void SetInputInt(int i);
  void SetInputFloat(float f);
  void SetInputDouble(double d);
  void SetInputBool(bool b);

  void SetInputNamedString(std::string n, std::string m);
  void SetInputNamedInt(std::string n, int i);
  void SetInputNamedFloat(std::string n, float f);
  void SetInputNamedDouble(std::string n, double d);
  void SetInputNamedBool(std::string n, bool b);

  void SetInputObject(TObject* obj) {fProofSession->AddInput(obj);}
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // Dynamic histograms. Specify the name of the histograms you would like
  // to monitor as they are filled by PROOF
  std::vector<TString> dynamicHistograms;
  void AddDynamicHistogram(const char* histo) {dynamicHistograms.push_back(histo);}
  std::vector<TString> GetDynamicHistograms() const {return dynamicHistograms;}
  unsigned int GetNDynamicHistograms() const {return dynamicHistograms.size();}
  //
  ///////////////////////////////

  /////////////////////////////
  //
  // Number of events. Specifies the number of events to process.
  // Set it to -1 to use the full sample.
  Long64_t nEvents;
  // First event to be processed
  Long64_t firstEvent;

  void SetNEvents(Long64_t nevents = TChain::kBigNumber) {nEvents = nevents; if (nEvents<0) nEvents = TChain::kBigNumber;}
  Long64_t GetNEvents() const {return nEvents;}
  void SetFirstEvent(Long64_t firstevent = 0) {firstEvent = firstevent;}
  Long64_t GetFirstEvent() const {return firstEvent;}
  //
  ///////////////////////////////
  

  ///////////////////////////////
  //
  // Name of analysis class. 
  void SetAnalysis(const char* analysis) { fAnalysisFile = analysis;}
  TString GetAnalysis() const {return fAnalysisFile;}
  //
  ///////////////////////////////


  /////////////////////////////
  //
  // Packages to be uploaded to PROOF. The mandatory ones are
  // added automatically in packages
  void AddPackage(const char* package) {packages.push_back(TString(package));}
  std::vector<TString> GetPackages() const {return packages;}
  unsigned int GetNPackages() const {return packages.size();}

  void AddSelectorPackage(const char* spackage) {selectorpackages.push_back(TString(spackage));}
  std::vector<TString> GetSelectorPackages() const {return selectorpackages;}
  unsigned int GetNSelectorPackages() const {return selectorpackages.size();}
  //
  ///////////////////////////////





  /////////////////////////////
  //
  // Some extra settings to control the output and checks
  bool reopenOutputFile;
  bool createSelector;
  //
  ///////////////////////////////



 public:
  
  /////////////////////////////
  // Merge through file: Important for TTrees
  void SetMergeThroughFile(bool merge=true) {fMergeThroughFile = merge;}
  bool GetMergeThroughFile() const {return fMergeThroughFile;}
  //
  ///////////////////////////////

  /////////////////////////////
  //
  // PROOF Session.
  TProof* GetPROOFSession() const {return fProofSession;}
  void SetPROOFSession(TProof* ps)  {fProofSession = ps;}
  //
  ///////////////////////////////



  /////////////////////////////
  //
  // Get the PAFOptions instance since this is a singleton
  static PAFOptions* Instance() {
    if (!thePAFOptions)
      thePAFOptions = new PAFOptions();
    return thePAFOptions;
  }
  //
  ///////////////////////////////




 protected:
  // Name of analysis class. 
  TString fAnalysisFile;

  // Output file name.
  TString fOutputFile;

  // Tree type. It defines the data formats that may be used. See TreeType
  // enum for details. Default is kMiniTrees
  ETreeType fTreeType;
  TString  fTreeDir;
  TString  fTreeName;


  // Packages to be uploaded to PROOF. The mandatory ones are
  // added automatically in packages
  std::vector<TString> packages;
  std::vector<TString> selectorpackages;


  // Max time we will wait to get all slots
  // when using PoD to set up our proof cluster
  int fPoDTimeout;


  // Merge through file: Important for TTrees
  bool fMergeThroughFile;

  // PROOF Session. Don't mess with it!
  TProof* fProofSession;

  PAFOptions():
    // PROOF Mode
    proofMode(kLite),
    // PROOF Cluster or Cloud
    NSlots(-1), 
    proofServer("proof.ifca.es"), 
    proofServerPort(1093),
    proofRequest(true),
    maxSlavesPerNode(9999),
    // Output file name
    fOutputFile("histofile.root"),
    // Input Parameters
    inputParameters(0),
    // Number of events and first event
    nEvents(TChain::kBigNumber),
    firstEvent(0),
    // Extra options
    reopenOutputFile(false),
    createSelector(true),
    // Analysis Class
    fAnalysisFile(""),
    // Output file name.
    fOtputFile("outputfile.root"),
    // Tree type
    fTreeType(kMiniTrees),
    fTreeDir(""),
    fTreeName("Tree"),
    //Timeout when using PoD and asking for slots
    fPoDTimeout(20),
    // Merge through file: Important for TTrees
    fMergeThroughFile(false),
    // Other internal stuff
    fProofSession(0)
      {
	AddPackage("TCounterUI");
	AddPackage("InputParameters");
	AddPackage("PAFBaseSelector");
	// XXX Trying to make this run more than once. 
	//AddPackage("PAFAnalysis");
      }
    
    static PAFOptions* thePAFOptions;
};

//
/////////////////////////////////////////////////////////////////////////


#endif

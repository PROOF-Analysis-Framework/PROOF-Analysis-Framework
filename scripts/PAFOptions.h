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
enum ProofMode {kSequential, kLite, kCluster, kPoD, kCloud};
//
/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// The different available tree types. Read tge documentation
// for details:
// * kMiniTrees: Flat Trees developed at IFCA-UO
// * kTESCO: Trees developed by the ETH
enum TreeType {kMiniTrees, kTESCO};
//
/////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////
// The PAFOptions class
//
class PAFOptions {
 public:
  
  ///////////////////////////////
  //
  // PROOF Mode. See ProofMode enum for details
  ProofMode proofMode; 
  ProofMode GetPAFMode() const {return proofMode;}
  //
  ///////////////////////////////


  ///////////////////////////////
  //
  // Number of slots you would like to use
  // + The default value depends on PROOF Mode
  void SetNSlots(int nslots) {NSlots = nslots;}
  int  GetNSlots() const {return NSlots;}
  int NSlots;


  ///////////////////////////////
  //
  // PROOF Cluster specific variables
  //+ Proof Server name (default is proof.ifca.es)
  TString proofServer;
  //+ Proof Server port (default is 1093)
  Int_t proofServerPort;
  //+ Perform or not the request for nodes (default is True)
  bool proofRequest;
  //+ Maximum number of slaves per node (use 9999 for all)
  Int_t maxSlavesPerNode;
  // Internal variable to keep the session dir of PAF
  TString pafSessionDir;
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Tree type. It defines the data formats that may be used. See TreeType
  // enum for details. Default is kMiniTrees
  TreeType GetTreeType() const { return treeType;}
  void SetTreeType(TreeType tt) {
    treeType = tt;
    if (tt == kMiniTrees) {
      treeDir  = "";
      treeName = "Tree";
      if (myAnalysis == "")
	myAnalysis = "MyAnalysisMiniTrees";
    }
    else {
      treeDir  = "analyze";
      treeName = "Analysis";
      if (myAnalysis == "")
	myAnalysis = "MyAnalysisTESCO";
    }
  }
  void SetTree(const char* t) {tt = t; Ssiz_t i= tt.Last('/');treeDir=tt(0,i); treeName=tt(i+1,tt.Sizeof());}
  TString GetTreeDir() const { return treeDir;}
  TString GetTreeName() const { return treeName;}
  void SetTreeDir(const char* td) { treeDir = td;}
  void SetTreeName(const char* tn) { treeName = tn;}
  //
  ///////////////////////////////


  ///////////////////////////////
  // Input data sample
  //
  vector<TString> dataFiles;
  void AddDataFile(const char* file) {dataFiles.push_back(file);}
  void AddDataFiles(const vector<TString>& files);
  void SetDataFiles(const vector<TString>& files) {dataFiles = files;}
  unsigned int GetNDataFiles() const {return dataFiles.size();}
  vector<TString> GetDataFiles() const {return dataFiles;}
  void PrintDataFiles() const;
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Output file name. Specifies the name of the file where you want the
  // histograms to be saved
  TString outputFile;
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Parameters for the analysis
  InputParameters *inputParameters;

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

  void SetInputObject(TObject* obj) {proofSession->AddInput(obj);}

  void SetPoDTimeOut (int);
  int  GetPoDTimeOut () const {return PoD_Timeout;}
  //
  ///////////////////////////////

  ///////////////////////////////
  //
  // Dynamic histograms. Specify the name of the histograms you would like
  // to monitor as they are filled by PROOF
  vector<TString> dynamicHistograms;
  void AddDynamicHistogram(const char* histo) {dynamicHistograms.push_back(histo);}
  vector<TString> GetDynamicHistograms() const {return dynamicHistograms;}
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
  void SetAnalysis(const char* analysis) const { myAnalysis = analysis;}
  TString GetAnalysis() const {return myAnalysis;}
  //
  ///////////////////////////////


  /////////////////////////////
  //
  // Packages to be uploaded to PROOF. The mandatory ones are
  // added automatically in packages
  void AddPackage(const char* package) {packages.push_back(TString(package));}
  vector<TString> GetPackages() const {return packages;}
  unsigned int GetNPackages() const {return packages.size();}

  void AddSelectorPackage(const char* spackage) {selectorpackages.push_back(TString(spackage));}
  vector<TString> GetSelectorPackages() const {return selectorpackages;}
  unsigned int GetNSelectorPackages() const {return selectorpackages.size();}
  //
  ///////////////////////////////





  /////////////////////////////
  //
  // Some extra settings to control the output and checks
  bool checkVersion;
  bool reopenOutputFile;
  bool createSelector;
  //
  ///////////////////////////////



  static PAFOptions* Instance() {
    if (!thePAFOptions)
      thePAFOptions = new PAFOptions();
    return thePAFOptions;
  }


 public:
  
  /////////////////////////////
  //
  // PROOF Session. Don't mess with it!
  TProof* proofSession;
  TProof* GetPROOFSession() const {return proofSession;}
  //
  ///////////////////////////////



 protected:
  // Name of analysis class. 
  TString myAnalysis;

  // Tree type. It defines the data formats that may be used. See TreeType
  // enum for details. Default is kMiniTrees
  TreeType treeType;
  TString  treeDir;
  TString  treeName;


  // Packages to be uploaded to PROOF. The mandatory ones are
  // added automatically in packages
  vector<TString> packages;
  vector<TString> selectorpackages;


  // Max time we will wait to get all slots
  // when using PoD to set up our proof cluster
  int PoD_Timeout;


  PAFOptions():
    // PROOF Mode
    proofMode(kLite),
    // PROOF Cluster or Cloud
    NSlots(-1), 
    proofServer("proof.ifca.es"), 
    proofServerPort(1093),
    proofRequest(true),
    maxSlavesPerNode(9999),
    pafSessionDir(""),
    // Tree type
    treeType(kMiniTrees),
    // Output file name
    outputFile("histofile.root"),
    // Number of events and first event
    nEvents(TChain::kBigNumber),
    firstEvent(0),
    // Analysis Class
    myAnalysis(""),
    // Input Parameters
    inputParameters(0),
    // Extra options
    checkVersion(false),
    reopenOutputFile(false),
    createSelector(true),
    //Timeout when using PoD and asking for slots
    PoD_Timeout (20),
    // Other internal stuff
    proofSession(0)
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

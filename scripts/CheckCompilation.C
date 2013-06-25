///////////////////////////////////////////////////////////////////////
//
//    FILE: CheckCompilation.C
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: January, 2011
//
// CONTENT: This macro checks if the current analysis file compiles correctly
//
///////////////////////////////////////////////////////////////////////

#include "TString.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <iostream>


void CleanFile(const char* basefile) {
  if (!gSystem->AccessPathName(basefile))
    gSystem->Unlink(basefile);
}

void CleanPackages(vector<TString> thefiles) {
  for (unsigned int i = 0; i < thefiles.size(); i++) {
    TString thefile="packages/";
    thefile += thefiles[i];
    thefile += "/";
    thefile += thefiles[i];
    TString sofile = thefile + "_C.so";
    TString dfile = thefile + "_C.d";
    CleanFile(sofile);
    CleanFile(dfile);
  }
}

bool PackageCompiled(const char* package) {
  TString thefile="packages/";
  thefile += package;
  thefile += "/";
  thefile += package;
  thefile += "_C.so";

  //  cout << "Checking if " << thefile << " exists..." << gSystem->AccessPathName(thefile)<< endl;
  
  return gSystem->AccessPathName(thefile);
}


void CheckCompilation(const char* flavour = "MiniTrees") {

  //////////////////
  // Initial list of packagees
  cout << ">> Initialising packages..." << endl;
  vector <TString> packages;
  packages.push_back("TCounterUI");
  packages.push_back("InputParameters");
  packages.push_back("PAFBaseSelector");
  TString cmsAnalysisSelector="PAFBaseSelector";
  cmsAnalysisSelector+=flavour;
  packages.push_back(cmsAnalysisSelector);

  //////////////////
  // Some cleaning in case things are there for no reason
  CleanPackages(packages);

  //////////////////
  // Compiling packages
  cout << ">> Compiling packages..." << endl;
  for (unsigned int i = 0; i < packages.size(); i++) {
    cout << "   + " << packages[i] << endl;
    TString packagepath = "-I";
    packagepath+=gSystem->pwd(); //path to local dir
    packagepath+="/packages/";
    packagepath+=packages[i];
    TString curpath = gSystem->GetIncludePath(); //current path
    cout << "     - Adding " << packagepath << " to path" << endl;
    if (!curpath.Contains(packagepath)) {
      gSystem->AddIncludePath(packagepath);
    }
    
    TString command="packages/";
    command += packages[i];
    command += "/";
    command += packages[i];
    command += ".C+";

    cout << "     - Loading macro \"" << command << "\"" << endl;
    gROOT->LoadMacro(command);
    if (PackageCompiled(packages[i])) {
      cerr << "ERROR: Could not load " << packages[i] << endl;
      CleanPackages(packages);
      return;
    }
  }


  //////////////////
  // My Analysis
  TString myanalysis("MyAnalysis");
  myanalysis+=flavour;

  CleanFile(myanalysis + "_C.so");
  CleanFile(myanalysis + "_C.d");


  cout << ">> Compiling My Analysis (" << myanalysis << ")..." << endl;
  gROOT->LoadMacro(myanalysis + ".C+");
  if (gSystem->AccessPathName(myanalysis + "_C.so")) {
    cerr << "ERROR: Could not load " << myanalysis << endl;
    CleanFile(myanalysis + "_C.so");
    CleanFile(myanalysis + "_C.d");
    return;
  }

  ///////////////////
  // Final cleaning
  cout << ">> Cleaning..." << endl;
  CleanPackages(packages);
  CleanFile(myanalysis + "_C.so");
  CleanFile(myanalysis + "_C.d");

  cout << endl 
       << "============================================================"
       << endl 
       << "SUCCESS: If you got here, it means everything compiled fine." 
       << endl 
       << "============================================================"
       << endl;



}

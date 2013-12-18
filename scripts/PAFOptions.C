///////////////////////////////////////////////////////////////////////
//
//    FILE: PAFOptions.C
//   CLASS: PAFOptions
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: January, 2011
//
///////////////////////////////////////////////////////////////////////
#include "PAFOptions.h"

//#include "../packages/InputParameters/InputParameters.h"

#include <iostream>

using namespace std;

PAFOptions* PAFOptions::thePAFOptions = 0;

//Global variable with parameters
PAFOptions* gPAFOptions = PAFOptions::Instance();

InputParameters* PAFOptions::GetInputParameters() {
  if (!inputParameters)
    inputParameters = new InputParameters;
  return inputParameters;
}

void PAFOptions::SetInputString(std::string s) {
  GetInputParameters()->SetString(s);
}
void PAFOptions::SetInputInt(int i) {
  GetInputParameters()->SetInt(i);
}
void PAFOptions::SetInputFloat(float f) {
  GetInputParameters()->SetFloat(f);
}
void PAFOptions::SetInputDouble(double d) {
  GetInputParameters()->SetDouble(d);
}
void PAFOptions::SetInputBool(bool b) {
  GetInputParameters()->SetBool(b);
}
void PAFOptions::SetInputNamedString(std::string n, std::string m) {
  GetInputParameters()->SetNamedString(n, m);
}
void PAFOptions::SetInputNamedInt(std::string n, int i) {
  GetInputParameters()->SetNamedInt(n, i);
}
void PAFOptions::SetInputNamedFloat(std::string n, float f) {
  GetInputParameters()->SetNamedFloat(n, f);
}
void PAFOptions::SetInputNamedDouble(std::string n, double d) {
  GetInputParameters()->SetNamedDouble(n, d);
}
void PAFOptions::SetInputNamedBool(std::string n, bool b) {
  GetInputParameters()->SetNamedBool(n, b);
}
void PAFOptions::SetPoDTimeOut(int timeout) {
  PoD_Timeout = timeout;
  
  if(timeout < 1)
    PoD_Timeout = 1;
}

void PAFOptions::AddDataFiles(const vector<TString>& files) {
  dataFiles.reserve( dataFiles.size() + files.size());
  dataFiles.insert( dataFiles.end(), files.begin(), files.end());
}

void PAFOptions::PrintDataFiles() const {
  for (unsigned int i = 0; i < dataFiles.size(); i++)
    cout << "* " << dataFiles[i] << endl;
}


void PAFOptions::Dump() const {
  cout << PAFINFO << "++===========================================++" << endl;
  cout << PAFINFO << "|| PAF OPTIONS                               ||" << endl;
  cout << PAFINFO << "++-------------------------------------------++" << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| PAF                                       ||" << endl;
  cout << PAFINFO << "++ ---                                       ||" << endl;
  cout << PAFINFO << "|| * PAF Mode: " << kCProofMode[fProofMode] << endl;
  cout << PAFINFO << "|| * N. Slots: " << fNSlots << endl;
  cout << PAFINFO << "|| * PROOF Session: " << fProofSession << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| PROOF Cloud                               ||" << endl;
  cout << PAFINFO << "++ -------------                             ||" << endl;
  cout << PAFINFO << "|| * Server: " << proofServer << endl;
  cout << PAFINFO << "|| * Server port: " << proofServerPort << endl;
  cout << PAFINFO << "|| * Request: " << proofRequest << endl;
  cout << PAFINFO << "|| * Max. Number of Slaves per Node: " 
       << maxSlavesPerNode << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| PoD                                       ||" << endl;
  cout << PAFINFO << "++ ---                                       ||" << endl;
  cout << PAFINFO << "|| * Timeout: " << fPoDTimeout << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| TREE                                      ||" << endl;
  cout << PAFINFO << "++ -------------                             ||" << endl;
  cout << PAFINFO << "|| * Type: " << kCTreeType[fTreeType] << endl;
  cout << PAFINFO << "|| * Dir: " <<  fTreeDir << endl;
  cout << PAFINFO << "|| * Name: " << fTreeName << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| INPUT                                     ||" << endl;
  cout << PAFINFO << "++ -----                                     ||" << endl;
  cout << PAFINFO << "|| * Data Files:" << endl;
  for (unsigned int i = 0; i < dataFiles.size(); i++)
    cout << PAFINFO << "||   + " << dataFiles[i] << endl;
  cout << PAFINFO << "|| * Events to process: " << fNEvents << endl;
  cout << PAFINFO << "|| * First Event: " << fFirstEvent << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| CODE                                      ||" << endl;
  cout << PAFINFO << "++ ----                                      ||" << endl;
  cout << PAFINFO << "|| * Analysis File: " << fAnalysisFile << endl;
  cout << PAFINFO << "|| * Create Selector: " << fCreateSelector << endl;
  cout << PAFINFO << "|| * Packages:" << endl;
  for (unsigned int i = 0; i < packages.size(); i++)
    cout << PAFINFO << "||   + " << packages[i] << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "|| OUTPUT                                    ||" << endl;
  cout << PAFINFO << "++ ------                                    ||" << endl;
  cout << PAFINFO << "|| * Output File: " << fOutputFile << endl;
  cout << PAFINFO << "|| * Reopen output file: " << fReopenOutputFile << endl;
  cout << PAFINFO << "|| * Dynamic Histograms:" << endl;
  for (unsigned int i = 0; i < dynamicHistograms.size(); i++)
    cout << PAFINFO << "||   + " << dynamicHistograms[i] << endl;
  cout << PAFINFO << "|| * Merge through file: " << fMergeThroughFile << endl;
  cout << PAFINFO << "||                                           ||" << endl;
  cout << PAFINFO << "++===========================================++" << endl;

}

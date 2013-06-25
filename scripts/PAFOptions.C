///////////////////////////////////////////////////////////////////////
//
//    FILE: PAFOptions.C
//   CLASS: PAFOptions
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: January, 2011
//
///////////////////////////////////////////////////////////////////////
#include "PAFOptions.h"

PAFOptions* PAFOptions::thePAFOptions = 0;

//Global variable with parameters
PAFOptions* gPAFOptions = PAFOptions::Instance();

void PAFOptions::SetInputString(std::string s) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetString(s);
}
void PAFOptions::SetInputInt(int i) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetInt(i);
}
void PAFOptions::SetInputFloat(float f) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetFloat(f);
}
void PAFOptions::SetInputDouble(double d) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetDouble(d);
}
void PAFOptions::SetInputBool(bool b) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetBool(b);
}
void PAFOptions::SetInputNamedString(std::string n, std::string m) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetNamedString(n, m);
}
void PAFOptions::SetInputNamedInt(std::string n, int i) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetNamedInt(n, i);
}
void PAFOptions::SetInputNamedFloat(std::string n, float f) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetNamedFloat(n, f);
}
void PAFOptions::SetInputNamedDouble(std::string n, double d) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetNamedDouble(n, d);
}
void PAFOptions::SetInputNamedBool(std::string n, bool b) {
  if (!inputParameters)
    inputParameters = new InputParameters;
  inputParameters->SetNamedBool(n, b);
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

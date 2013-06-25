///////////////////////////////////////////////////////////////////////
//
//    FILE: InputParameters.h
//   CLASS: InputParameters
// AUTHORS: A.Y. Rodriguez Marrero, I. Gonzalez Caballero
//    DATE: 2010
//
// CONTENT: This class provides a mechanism to easily store and share
//          parameters with a PROOF session.
//
///////////////////////////////////////////////////////////////////////

#ifndef InputParameters_h
#define InputParameters_h 1

#include <map>
#include <string>

#include "TNamed.h"
#include "TString.h"
#include "TProof.h"

class InputParameters : public TNamed {
 public:
  InputParameters(const char *s = "Set Of Parameters");
  virtual ~InputParameters();
    
  // Store Getters
  const char* GetString() const { return fString.Data(); }
  Int_t TheInt() const { return fInt; }
  Float_t TheFloat() const { return fFloat; }
  Double_t TheDouble() const { return fDouble; }
  Bool_t TheBool() const { return fBool; }
  const char *TheNamedString(std::string n);
  Int_t TheNamedInt(std::string n, Int_t &i);
  Int_t TheNamedFloat(std::string n, Float_t &d);
  Int_t TheNamedDouble(std::string n, Double_t &d);
  Int_t TheNamedBool(std::string n, Bool_t &b);
  
  // Store Setters
  void SetString(std::string s) { fString = s; };
  void SetInt(int i) { fInt = i; };
  void SetFloat(float d) { fFloat = d; };
  void SetDouble(double db) { fDouble = db; };
  void SetBool(bool b) { fBool = b; };
  void SetNamedString(std::string n, std::string m) { fMapString[n] = m; }
  void SetNamedInt(std::string n, int i) { fMapInt[n] = i; }
  void SetNamedFloat(std::string n, float d) { fMapFloat[n] = d; }
  void SetNamedDouble(std::string n, double db) { fMapDouble[n] = db; }
  void SetNamedBool(std::string n, bool b) { fMapBool[n] = b; }

  // Dump content
  void DumpParms(ostream& output);
  void DumpParms();
  
 protected:
  // Information stores
  TString			fString;    // A TString parameter
  Int_t                         fInt;       // An Int_t parameter
  Float_t                       fFloat;     // A Float_t parameter
  Double_t                      fDouble;    // A Double_t parameter
  Bool_t                        fBool;      // A Bool_t parameter
  std::map<std::string,TString> fMapString; // A map of named strings
  std::map<std::string,int>     fMapInt;    // A map of named ints
  std::map<std::string,float>   fMapFloat;  // A map of named floats
  std::map<std::string,double>  fMapDouble; // A map of named doubles
  std::map<std::string,bool>    fMapBool;   // A map of named booleans


  // We need to stream this class
  ClassDef(InputParameters, 1);  // Structure to define many parameters in one go
};

inline InputParameters::InputParameters(const char *s): 
  TNamed(s,""), 
  fString(""), 
  fInt(0), 
  fFloat(0.), 
  fDouble(0.), 
  fBool(kFALSE)
{}

inline InputParameters::~InputParameters() { }

inline const char *InputParameters::TheNamedString(std::string n) {
  std::map<std::string,TString>::iterator iter = fMapString.find(n);
  if (iter != fMapString.end()) { return iter->second.Data(); }
  return NULL;
}

inline Int_t InputParameters::TheNamedInt(std::string n, Int_t &i) {
  std::map<std::string,int>::iterator iter = fMapInt.find(n);
  if (iter != fMapInt.end()) { i = iter->second; return 0; }
  return -1;
}

inline Int_t InputParameters::TheNamedFloat(std::string n, Float_t &d) {
  std::map<std::string,float>::iterator iter = fMapFloat.find(n);
  if (iter != fMapFloat.end()) { d = iter->second; return 0; }
  return -1;
}

inline Int_t InputParameters::TheNamedDouble(std::string n, Double_t &d) {
  std::map<std::string,double>::iterator iter = fMapDouble.find(n);
  if (iter != fMapDouble.end()) { d = iter->second; return 0; }
  return -1;
}

inline Int_t InputParameters::TheNamedBool(std::string n, Bool_t &b) {
  std::map<std::string,bool>::iterator iter = fMapBool.find(n);
  if (iter != fMapBool.end()) { b = iter->second; return 0; }
  return -1;
}


#endif

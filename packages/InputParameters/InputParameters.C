///////////////////////////////////////////////////////////////////////
//
//    FILE: InputParameters.C
//   CLASS: InputParameters
// AUTHORS: A.Y. Rodriguez Marrero, I. Gonzalez Caballero
//    DATE: 2010
//
///////////////////////////////////////////////////////////////////////
#include "InputParameters.h"

#if !defined(__CINT__)
ClassImp(InputParameters);
#endif


#include <iostream>

// XXX (enolfc) This was meant to be operator << but it is already overload by ClassDef :(
void InputParameters::DumpParms(ostream &out) {
  out << " +++++++++++++++ Input Parameters +++++++++++++ " << std::endl
      << " + Name: " << this->GetName() << std::endl
      << " + String: " << this->GetString() << std::endl
      << " + Int: " << this->TheInt() << ", Float: " << this->TheFloat()
      << ", Double: " << this->TheDouble() << ", Bool: " << this->TheBool() << std::endl;

  out << " + Named String(s): " << this->fMapString.size() << std::endl;
  std::map<std::string,TString>::iterator its = this->fMapString.begin();
  while (its != this->fMapString.end()) { 
    out << " +   '" << its->first.c_str() << "' -> " << its->second.Data() << std::endl;
    its++; 
  }

  out << " + Named Int(s): " << this->fMapInt.size() << std::endl;
  std::map<std::string,int>::iterator iti = this->fMapInt.begin();
  while (iti != this->fMapInt.end()) {
    out << " +   '" << iti->first.c_str() << "' -> " << iti->second << std::endl; 
    iti++; 
  }

  out << " + Named Float(s): " << this->fMapFloat.size() << std::endl;
  std::map<std::string,float>::iterator itd = this->fMapFloat.begin();
  while (itd != this->fMapFloat.end()) { 
    out << " +   '" << itd->first.c_str() << "' -> " << itd->second << std::endl;
    itd++; 
  }

  out << " + Named Double(s): " << this->fMapDouble.size() << std::endl;
  std::map<std::string,double>::iterator itdb = this->fMapDouble.begin();
  while (itdb != this->fMapDouble.end()) {
    out << " +   '" << itdb->first.c_str() << "' -> " << itdb->second << std::endl;
    itdb++;
  }

  out << " + Named Bool(s): " << this->fMapBool.size() << std::endl;
  std::map<std::string,bool>::iterator itb = this->fMapBool.begin();
  while (itb != this->fMapBool.end()) {
    out << " +   '" << itb->first.c_str() << "' -> " << itb->second << std::endl;
    itb++; 
  }
  out << " +++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}


void InputParameters::DumpParms() {
  this->DumpParms(std::cout);
}

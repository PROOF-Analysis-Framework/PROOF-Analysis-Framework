/**
	@brief Class to group a bunch of samples with the parameters associated to it. 
	@file PAFSampleCollection.cxx
	@class PAFSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2016-11-09
 */
#pragma once

// PAF includes
#include "PAFSample.h"

// ROOT includes
#include "TNamed.h"
#include "TString.h"


class PAFSampleCollection: public TNamed {
 public:
  PAFSampleCollection(const char* name = "PAFDefaultSampleCollection");
  virtual ~PAFSampleCollection();

  // Dealing with samples
  inline void AddSample(PAFSample* ps);
  inline unsigned int GetNSamples() const;
  inline PAFSample* GetSample(unsigned int i);
  PAFSample* GetSampleByName(const TString& name);

  // Getting the files (in the form of TDSet)
  TDSet* GetDataFiles(const char* samplename);
  std::vector<TDSet*> GetDataFiles();

  // Tree name managemet
  std::vector<TString> GetDefaultTreeNames() const;
  inline TString GetDefaultTreeName(unsigned int i) const;
  bool IsTreeNameSet() const;
  void SetDefaultTreeName(const TString& defaultTreeName);

  // Dealing with parameters
  template <typename T>
    void SetParameter(const char* key, T param);

  PAFVariableContainer* GetParameters() { return fParameters;}


 protected:
  std::vector<PAFSample*> fSamples;    //List of samples
  PAFVariableContainer*   fParameters; //The SampleCollection paremeters


  ClassDef(PAFSampleCollection, 1);
};

//----------------------------------------------------------------------
// Template methods
template <typename T>
void PAFSampleCollection::SetParameter(const char* key, T param) {

  if (!fParameters)
    fParameters = new PAFVariableContainer;

  fParameters->Add(key, param);
}


//----------------------------------------------------------------------
// Inline methods

void  PAFSampleCollection::AddSample(PAFSample* ps) {fSamples.push_back(ps);}
unsigned int  PAFSampleCollection::GetNSamples() const {return fSamples.size();}
PAFSample*  PAFSampleCollection::GetSample(unsigned int i) {return fSamples[i];}
TString PAFSampleCollection::GetDefaultTreeName(unsigned int i) const {
  return fSamples[i]->GetDefaultTreeName();
}

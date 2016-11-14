/**
	@brief Class to group a bunch of samples with the parameters associated to it. 
	@file PAFSampleCollection.cxx
	@class PAFSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2016-11-09
 */

#include "PAFSampleCollection.h"

#include "PAF.h"

ClassImp(PAFSampleCollection);


PAFSampleCollection::PAFSampleCollection(const char* name):
  TNamed(name, name), 
  fParameters(0) {}



PAFSampleCollection::~PAFSampleCollection() {
  delete fParameters;
  for (unsigned int i = 0; i < fSamples.size(); i++)
    delete fSamples[i];
}


PAFSample* PAFSampleCollection::GetSampleByName(const TString& name) {
  for (unsigned int i = 0; i < fSamples.size(); i++)
    if (TString(fSamples[i]->GetName()) == name)
      return fSamples[i];
  return 0;
}

TDSet* PAFSampleCollection::GetDataFiles(const char* name) {
  PAF_DEBUG("PAFSampleCollection", TString::Format("GetDataFiles(%s)", name));
  for (unsigned int i = 0; i < fSamples.size(); i++) {
    PAF_DEBUG("PAFSampleCollection", 
	      TString::Format("  + fSamples[i]->GetName()", fSamples[i]->GetName()));
      if (TString(fSamples[i]->GetName()) == name)
	return fSamples[i]->GetDataFiles();
  }
}


std::vector<TDSet*> PAFSampleCollection::GetDataFiles() {
  std::vector<TDSet*> tdsets;
  for (unsigned int i = 0; i < fSamples.size(); i++)
    tdsets.push_back(fSamples[i]->GetDataFiles());
  return tdsets;
}



void PAFSampleCollection::SetDefaultTreeName(const TString& defaultTreeName) {
  for (unsigned int i = 0; i < fSamples.size(); i++)
    fSamples[i]->SetDefaultTreeName(defaultTreeName);
}




std::vector<TString> PAFSampleCollection::GetDefaultTreeNames() const {
  std::vector<TString> treenames(fSamples.size());
  for (unsigned int i = 0; i < fSamples.size(); i++)
    treenames.push_back(fSamples[i]->GetDefaultTreeName());

}

bool PAFSampleCollection::IsTreeNameSet() const {
  for (unsigned int i = 0; i < fSamples.size(); i++)
    if (fSamples[i]->GetDefaultTreeName().IsNull())
      return false;

  return true;
}



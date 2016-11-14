/**
	@brief Class to store a data sample with the parameters associated to it. 
	@file PAFSample.cxx
	@class PAFSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2016-11-09
 */

#pragma once

// PAF includes
#include "PAFVariableContainer.h"

// Root includes
#include "TNamed.h"
#include "TString.h"
#include "TDSet.h"
#include "TFileInfo.h"

class PAFSample: public TNamed {
 public:
  PAFSample(const char* name = "PAFDefaultSample");
  virtual ~PAFSample();
  
  void AddDataFile(const TString& fileName, const char* objname = 0);
  void AddDataFile(TFileInfo* dataFile);
  void AddDataFiles(const std::vector<TString>& files, const char* objname = 0);
  
  void SetDataFiles(TDSet* dataFiles) {fDataFiles = dataFiles;}
  TDSet* GetDataFiles() { return fDataFiles;}
  
  TString GetDefaultTreeName() const { return fDataFiles->GetObjName();}
  void SetDefaultTreeName(const TString& defaultTreeName);
  
  
  template <typename T>
    void SetParameter(const char* key, T param);

  PAFVariableContainer* GetParameters() { return fParameters;}


 protected:
  TDSet*                fDataFiles;  //Holds the data files
  PAFVariableContainer* fParameters; //The sample parameters


  ClassDef(PAFSample, 1);
	
};

template <typename T>
void PAFSample::SetParameter(const char* key, T param) {

  if (!fParameters)
    fParameters = new PAFVariableContainer;

  fParameters->Add(key, param);
}

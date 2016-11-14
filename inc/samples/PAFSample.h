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


  // Adding files to sample
  void AddDataFile(const TString& fileName, const char* objname = 0);
  void AddDataFile(TFileInfo* dataFile);
  void AddDataFiles(const std::vector<TString>& files, const char* objname = 0);
  
  // Dealing with files in the form TDSets
  inline void SetDataFiles(TDSet* dataFiles);
  inline TDSet* GetDataFiles();

  // Dealing with tree names
  inline TString GetDefaultTreeName() const;
  void SetDefaultTreeName(const TString& defaultTreeName);
  

  // Dealing with parameters
  template <typename T>
    void SetParameter(const char* key, T param);

  inline PAFVariableContainer* GetParameters();


 protected:
  TDSet*                fDataFiles;  //Holds the data files
  PAFVariableContainer* fParameters; //The sample parameters


  ClassDef(PAFSample, 1);
};


//----------------------------------------------------------------------
// Template methods

template <typename T>
void PAFSample::SetParameter(const char* key, T param) {

  if (!fParameters)
    fParameters = new PAFVariableContainer;

  fParameters->Add(key, param);
}


//----------------------------------------------------------------------
// Inline methods
void PAFSample::SetDataFiles(TDSet* dataFiles) {fDataFiles = dataFiles;}

TDSet* PAFSample::GetDataFiles() { return fDataFiles;}

TString PAFSample::GetDefaultTreeName() const { return fDataFiles->GetObjName();}

PAFVariableContainer* PAFSample::GetParameters() { return fParameters;}

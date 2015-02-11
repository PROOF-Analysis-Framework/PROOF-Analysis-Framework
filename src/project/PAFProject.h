/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.h
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include <vector>

#include "TString.h"
#include "TFileInfo.h"
#include "TFileCollection.h"

#include "../settings/PAFISettings.h"
#include "../environments/PAFIExecutionEnvironment.h"
#include "../packages/PAFPackage.h"
#include "../packages/PAFPackageSelector.h"
#include "../packages/PAFLibrary.h"
#include "../computing/PAFISelector.h"
#include "../computing/PAFChainSelector.h"
#include "../computing/PAFChainItemSelector.h"
#include "../computing/PAFBaseSelector.h"
#include "../variable_container/PAFVariableContainer.h"

class PAFProject 
{
	public:
		PAFProject();

		PAFProject(PAFIExecutionEnvironment* executionEnvironment);

		virtual ~PAFProject();

		void SetExecutionEnvironment(PAFIExecutionEnvironment* executionEnvironment) {fExecutionEnvironment = executionEnvironment;}
		PAFIExecutionEnvironment* GetExecutionEnvironment() {return fExecutionEnvironment;}

		void AddPackage(PAFPackage* package) {fPackages.push_back(package);}
		std::vector<PAFPackage*>* GetPackages() {return &fPackages;}

		void AddSelectorPackage(PAFPackageSelector* packageSelector) {fSelectorPackages.push_back(packageSelector);}
		std::vector<PAFPackageSelector*>* GetSelectorPackages() {return &fSelectorPackages;}

		void AddLibrary(PAFLibrary* library) {fLibraries.push_back(library); }
		std::vector<PAFLibrary*>* GetLibraries() {return &fLibraries;}

		void AddDataFile(const char* dataFile) {fDataFiles->Add(dataFile);}
		void AddDataFile(TFileInfo* dataFile) {fDataFiles->Add(dataFile);}
		TFileCollection* GetDataFiles() {return fDataFiles;}
		
		void SetPAFSettings(PAFISettings* settings);
		PAFISettings* GetPAFSettings(){ return fPAFSettings; }

		void SetOutputFile(const char* fileName) {fOutputFile = TString(fileName);}
		TString GetOutputFile() {return fOutputFile;}

		void SetInputParameters(PAFVariableContainer* inputParameters) {fInputParameters = inputParameters;}
		PAFVariableContainer* GetInputParameters() {return fInputParameters;}
		template <typename T>
		void SetInputParam(const char* key, T param);

		void AddDynamicHistogram(const char* histo) {fDynamicHistograms.push_back(histo);}
		std::vector<TString> GetDynamicHistograms() {return fDynamicHistograms;}
		
		bool GetCompileOnSlaves() {return fCompileOnSlaves;}
		void SetCompileOnSlaves(bool compileOnSlaves) {fCompileOnSlaves = compileOnSlaves;}

		void Run();      

	private:
		PAFIExecutionEnvironment*           fExecutionEnvironment;
		PAFVariableContainer*				fInputParameters;
		PAFISelector*                       fPAFSelector;
		std::vector<PAFPackage*>            fPackages; //!
		std::vector<PAFPackageSelector*>    fSelectorPackages; //! FIXME: Why we should comment this to ClassDef and ClassImp?
		std::vector<PAFLibrary*>			fLibraries; //!
		TFileCollection*                    fDataFiles;
		TString                             fOutputFile;
		std::vector<TString>				fDynamicHistograms;
		PAFISettings*						fPAFSettings;
		bool								fCompileOnSlaves;

	private:
		void UploadAndEnablePackage(PAFPackage* package);
		void UploadAndEnablePackages(std::vector<PAFPackage*> packages);
		void UploadAndEnablePackages(std::vector<PAFPackageSelector*> packages);
		void LoadLibraries();

		template<typename T>
		T CreateObject(const char* className);
	
		void PreparePAFAnalysis();
		
		void PrepareEnvironment();
		void PreparePAFSelector();
		void AddDynamicHistograms();
		
	ClassDef(PAFProject, 1);
};

template <typename T>
inline void PAFProject::SetInputParam(const char* key, T param)
{
	TString tkey(key);
	fInputParameters->Add(tkey, param);
}


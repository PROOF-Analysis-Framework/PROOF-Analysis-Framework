/**
	@brief Abstract class with common funcionality of different PAFIProjects.
	@file PAFAbstractProject.h
	@class PAFAbstractProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-18
*/

#pragma once

#include <vector>

#include "TString.h"

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

class PAFAbstractProject 
{
	public:
		PAFAbstractProject();
		PAFAbstractProject(PAFIExecutionEnvironment* executionEnvironment);
		virtual ~PAFAbstractProject();

		void SetExecutionEnvironment(PAFIExecutionEnvironment* executionEnvironment) {fExecutionEnvironment = executionEnvironment;}
		PAFIExecutionEnvironment* GetExecutionEnvironment() {return fExecutionEnvironment;}

		void SetPackages(std::vector<PAFPackage*>* packages) { fPackages = packages; }
		std::vector<PAFPackage*>* GetPackages() { return fPackages; }
		void AddPackage(TString& packageName);
		void AddPackage(const char* packageName);
		void AddPackage(PAFPackage* package);

		void SetSelectorPackages(std::vector<PAFPackageSelector*>* selectorPackages) { fSelectorPackages = selectorPackages; } 
		std::vector<PAFPackageSelector*>* GetSelectorPackages() { return fSelectorPackages; }
		void AddSelectorPackage(TString& packageSelectorName);
		void AddSelectorPackage(const char* packageSelectorName);
		void AddSelectorPackage(PAFPackageSelector* packageSelector);

		void SetLibraries(std::vector<PAFLibrary*>* libraries) { fLibraries = libraries; }
		std::vector<PAFLibrary*>* GetLibraries() {return fLibraries;}
		void AddLibrary(TString& libraryName);
		void AddLibrary(const char* libraryName);
		void AddLibrary(PAFLibrary* library);

		void SetPAFSettings(PAFISettings* settings);
		PAFISettings* GetPAFSettings(){ return fPAFSettings; }

		void SetOutputFile(TString& fileName) { fOutputFile = fileName; }
		void SetOutputFile(const char* fileName) { fOutputFile = TString(fileName); }
		TString GetOutputFile() { return fOutputFile; }

		void SetInputParameters(PAFVariableContainer* inputParameters) { fInputParameters = inputParameters; }
		PAFVariableContainer* GetInputParameters() { return fInputParameters; }
		template <typename T>
		void SetInputParam(TString& key, T param);
		template <typename T>
		void SetInputParam(const char* key, T param);

		void SetDynamicHistograms(std::vector<TString>* dynamicHistograms) { fDynamicHistograms = dynamicHistograms; }
		std::vector<TString>* GetDynamicHistograms() { return fDynamicHistograms; }
		void AddDynamicHistogram(TString& histogram);
		void AddDynamicHistogram(const char* histogram);
		
		bool GetCompileOnSlaves() { return fCompileOnSlaves; }
		void SetCompileOnSlaves(bool compileOnSlaves) { fCompileOnSlaves = compileOnSlaves; }

		void Run();
		virtual void doRun(PAFBaseSelector* selector) = 0;

	protected:
		void InitMembers();

		template<typename T>
		T CreateObject(const char* className);
		
		void PreparePackage(PAFPackage* package);
		void PreparePackages();
		void LoadProjectItems();
		void PreparePAFSelector();
		void AddDynamicHistograms();
		
	protected:
		PAFIExecutionEnvironment*		fExecutionEnvironment;
		PAFVariableContainer*			fInputParameters;
		PAFISelector*				fPAFSelector;
		std::vector<PAFPackage*>*		fPackages; //!
		std::vector<PAFPackageSelector*>*	fSelectorPackages; //!
		std::vector<PAFLibrary*>*		fLibraries; //!
		TString					fOutputFile;
		std::vector<TString>*			fDynamicHistograms;
		PAFISettings*				fPAFSettings;
		bool					fCompileOnSlaves;
		
	ClassDef(PAFAbstractProject, 1);
};

template <typename T>
inline void PAFAbstractProject::SetInputParam(TString& key, T param)
{
	fInputParameters->Add(key, param);
}

template <typename T>
inline void PAFAbstractProject::SetInputParam(const char* key, T param)
{
	TString tkey(key);
	SetInputParam(tkey, param);
}

template<>
inline void PAFAbstractProject::SetInputParam(TString& key, const char* param)
{
	TString tparam(param);
	SetInputParam(key, tparam);
}

template <>
inline void PAFAbstractProject::SetInputParam(const char* key, const char* param)
{
	TString tkey(key);
	SetInputParam(tkey, param);
}


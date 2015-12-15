/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.h
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
 */

#pragma once

#include "PAFAbstractProject.h"

#include "TDSet.h"
#include "TFileInfo.h"
#include "TFile.h"

class PAFProject : public PAFAbstractProject
{
	public:
		PAFProject();
		PAFProject(PAFIExecutionEnvironment* executionEnvironment);
		virtual ~PAFProject();

		void SetDefaultTreeName(const TString& defaultTreeName);
		void SetDefaultTreeName(const char* defaultTreeName);
		TString GetDefaultTreeName() const;

		void SetDataFiles(TDSet* dataFiles);
		TDSet* GetDataFiles();

		void AddDataFile(const TString& fileName, const char* objname);
		void AddDataFile(const char* fileName, const char* objname = 0);
		void AddDataFile(TFileInfo* dataFile);

		void AddDataFiles(const std::vector<TString>& files, const char* objname = 0);

		void SetFirstEvent(Long64_t firstEvent);
		Long64_t GetFirstEvent() const;

		void SetNEvents(Long64_t nEvents);
		Long64_t GetNEvents() const;

		virtual void doRun(PAFBaseSelector* selector);
		virtual void doProjectChecks();

	protected:
		void InitMembers();

		bool ExistsTree(TFile* rootFile, const char* treeName);
		void GetListOfTrees(TDirectory* directory, TList* resultTrees, const char* path);

		virtual TString GetDirectoryFromObjName(const TString& objName);
		virtual TString GetNameFromObjName(const TString& objName);

	protected:
		TDSet* 	fDataFiles;
		Long64_t fFirstEvent;
		Long64_t fNEvents;

	ClassDef(PAFProject, 1);
};

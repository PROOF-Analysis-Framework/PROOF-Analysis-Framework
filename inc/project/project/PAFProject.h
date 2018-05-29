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

// PAF includes
#include "PAFSampleCollection.h"

// ROOT includes
#include "TFileInfo.h"
#include "TFile.h"

class PAFProject : public PAFAbstractProject
{
	public:
		PAFProject();
		PAFProject(PAFIExecutionEnvironment* executionEnvironment);
		virtual ~PAFProject();

		// Set the name of the default tree. Should be called after the files are loaded
		// TBD. Make sure AddDataFiles or SetDataFiles are not called after this
		void SetDefaultTreeName(const TString& defaultTreeName);

		void SetDataFiles(TDSet* dataFiles, const char* samplename = "PAFDefaultSample");
		TDSet* GetDataFiles(const char* samplename = "PAFDefaultSample");

		void AddDataFile(const TString& fileName, const char* objname = 0, 
				 const char* samplename = "PAFDefaultSample");
		void AddDataFile(TFileInfo* dataFile, const char* samplename = "PAFDefaultSample");

		void AddDataFiles(const std::vector<TString>& files, const char* objname = 0, 
				  const char* samplename = "PAFDefaultSample");


		// Dealing with the sample collection
		PAFSampleCollection* AddSample(PAFSample* sample);
		inline void SetSampleCollection(PAFSampleCollection* sc);
		inline PAFSampleCollection* GetSampleCollection();

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
		PAFSample* CheckAndCreateSample(const char* samplename) const;
		void CheckFileTrees(TDSet* tdset);


	protected:
		PAFSampleCollection* fSampleCollection;
		Long64_t fFirstEvent;
		Long64_t fNEvents;

	ClassDef(PAFProject, 1);
};


//----------------------------------------------------------------------
// Inline methods
void PAFProject::SetSampleCollection(PAFSampleCollection* sc) {
  fSampleCollection = sc;
}

PAFSampleCollection* PAFProject::GetSampleCollection() {
  return fSampleCollection;
}

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

#include "TFileInfo.h"
#include "TFileCollection.h"

class PAFProject : public PAFAbstractProject
{
	public:
		PAFProject();
		PAFProject(PAFIExecutionEnvironment* executionEnvironment);
		virtual ~PAFProject();
		
		void SetDataFiles(TFileCollection* dataFiles) { fDataFiles = dataFiles; }
		TFileCollection* GetDataFiles() { return fDataFiles; }
		void AddDataFile(TString& fileName);
		void AddDataFile(const char* fileName);
		void AddDataFile(TFileInfo* dataFile);

		void doRun(PAFBaseSelector* selector);      

	protected:
		TFileCollection* fDataFiles;
		
	ClassDef(PAFProject, 1);
};

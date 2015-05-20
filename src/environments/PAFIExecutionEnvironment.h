/**
	@brief Interface to create strategy pattern with diferentes executions environments.
	@file PAFIExecutionEnvironment.h
	@class PAFIExecutionEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "TObject.h"
#include "TDSet.h"
#include "TDrawFeedback.h"

#include "../computing/PAFBaseSelector.h"
#include "../packages/PAFPackage.h"
#include "../packages/PAFLibrary.h"

class PAFIExecutionEnvironment 
{
	public:
		PAFIExecutionEnvironment() {}
		virtual ~PAFIExecutionEnvironment() {}

		virtual void Initialise() = 0;
		virtual void Dispose() = 0;
		
		virtual void AddInput(TObject* obj) = 0;
		virtual void AddFeedback(const char* name) = 0;
		virtual TDrawFeedback* CreateDrawFeedback() = 0;

		virtual bool UploadPackage(PAFPackage* package) = 0;
		virtual bool EnablePackage(PAFPackage* package) = 0;

		virtual bool LoadLibrary(PAFLibrary* library) = 0;

		virtual void Process(PAFBaseSelector* selector, Long64_t nentries) = 0;
		virtual void Process(PAFBaseSelector* selector, TDSet* dataFiles) = 0;
};

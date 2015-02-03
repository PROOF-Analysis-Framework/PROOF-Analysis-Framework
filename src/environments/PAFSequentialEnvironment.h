/**
	@brief Implementation of PAFIExecutionEnvironment to work in sequential mode.
	@file PAFSequentialEnvironment.h
	@class PAFSequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-02-02
*/

#include "PAFIExecutionEnvironment.h"

class PAFSequentialEnvironment : public PAFIExecutionEnvironment {
	public:
		PAFSequentialEnvironment() : PAFIExecutionEnvironment(), fInputList() {}
		virtual ~PAFSequentialEnvironment() {}

		virtual void AddInput(TObject* obj);
		virtual void AddFeedback(const char* name);
		virtual TDrawFeedback* CreateDrawFeedback();
		virtual void Process(TFileCollection* dataFiles, PAFBaseSelector* selector);
		virtual void Process(TFileCollection* dataFiles, PAFBaseSelector* selector, TString& outputFile);
		
		virtual bool UploadPackage(PAFPackage* package);
		virtual bool EnablePackage(PAFPackage* package);
		
		virtual bool LoadLibrary(PAFLibrary* library);

	protected:
		TList fInputList;
};
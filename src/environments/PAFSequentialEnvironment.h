/**
	@brief Implementation of PAFIExecutionEnvironment to work in sequential mode.
	@file PAFSequentialEnvironment.h
	@class PAFSequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-02
*/

#include "PAFIExecutionEnvironment.h"

class PAFSequentialEnvironment : public PAFIExecutionEnvironment {
	public:
		PAFSequentialEnvironment();
		virtual ~PAFSequentialEnvironment();

		void Initialise() {}
		void Dispose() {}
		
		virtual void SetOutput(TString& outputFile);
		
		virtual void AddInput(TObject* obj);
		virtual void AddFeedback(const char* name);
		virtual TDrawFeedback* CreateDrawFeedback();
		virtual void Process(PAFBaseSelector* selector, TFileCollection* dataFiles);
		
		virtual bool UploadPackage(PAFPackage* package);
		virtual bool EnablePackage(PAFPackage* package);
		
		virtual bool LoadLibrary(PAFLibrary* library);

	protected:
		void InitMembers();
		
		virtual void DrawFeedback(TSelector* selector);

	protected:
		TString 		fOutputFile;
		TList*			fInputList;
		PAFVariableContainer* 	fFeedbackCanvas;
};
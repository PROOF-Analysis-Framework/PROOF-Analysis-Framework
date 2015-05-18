/**
	@brief Implementation of PAFIExecutionEnvironment to work over diferents PROOF environments.
	@file PAFPROOFEnvironment.h
	@class PAFPROOFEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFIExecutionEnvironment.h"

#include "TProof.h"
#include "proof_library_upload/PAFPROOFIUploadLibrary.h"

class PAFPROOFEnvironment : public PAFIExecutionEnvironment 
{
	public:
		PAFPROOFEnvironment();
		virtual ~PAFPROOFEnvironment();

		void Initialise();
		void Dispose();
		
		virtual void SetOutput(TString& outputFile);
		
		void AddInput(TObject* obj);
		void AddFeedback(const char* name);
		TDrawFeedback* CreateDrawFeedback();
		
		bool UploadPackage(PAFPackage* package);
		bool EnablePackage(PAFPackage* package);

		bool LoadLibrary(PAFLibrary* library);

		virtual void Process(PAFBaseSelector* selector, Long64_t nentries);
		virtual void Process(PAFBaseSelector* selector, TDSet* dataFiles);

		void SetPROOFUpload(PAFPROOFIUploadLibrary* proofUploadLibrary);
		PAFPROOFIUploadLibrary* GetPROOFUpload();

	protected:
		void InitMembers();
		virtual TProof* doCreateTProof() = 0;
		virtual void LoadPAF();
		
	protected:
		TString			fOutputFile;
		TProof*			fSession;
		PAFPROOFIUploadLibrary*	fPROOFUploadLibrary;
};


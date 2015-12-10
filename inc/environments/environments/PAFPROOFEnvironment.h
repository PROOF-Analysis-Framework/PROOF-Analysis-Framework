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
#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFEnvironment : public PAFIExecutionEnvironment 
{
	public:
		PAFPROOFEnvironment();
		virtual ~PAFPROOFEnvironment();

		void Initialise();
		void Dispose();

		void AddInput(TObject* obj);
		void AddFeedback(const char* name);
		TDrawFeedback* CreateDrawFeedback();
		
		virtual void SetProgressUpdated(PAFIProgressUpdated* progressUpdated);
		virtual PAFIProgressUpdated* GetProgressUpdated();

		Bool_t UploadPackage(PAFPackage* package);
		Bool_t EnablePackage(PAFPackage* package);

		Bool_t LoadLibrary(PAFLibrary* library);

		virtual void Process(PAFBaseSelector* selector, Long64_t nentries);
		virtual void Process(PAFBaseSelector* selector, TDSet* dataFiles, Long64_t firstEvent, Long64_t nEvents);

		void SetPROOFUpload(PAFPROOFIUploadLibrary* proofUploadLibrary);
		PAFPROOFIUploadLibrary* GetPROOFUpload();

	protected:
		void InitMembers();
		virtual TProof* doCreateTProof() = 0;
		virtual void LoadPAF();

	protected:
		TProof*			fSession;
		PAFPROOFIUploadLibrary*	fPROOFUploadLibrary;
};

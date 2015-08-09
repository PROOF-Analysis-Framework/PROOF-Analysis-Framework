/**
	@brief Interface to create a strategy pattern to PROOF libraries upload.
	@file PAFPROOFIUploadLibrary.h
	@class PAFPROOFIUploadLibrary
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
 */

#pragma once

#include "TProof.h"

#include "PAFLibrary.h"

class PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFIUploadLibrary();
		virtual ~PAFPROOFIUploadLibrary();

		void SetSession(TProof* session);
		TProof* GetSession();

		virtual bool UploadLibrary(PAFLibrary* library) = 0;

	protected:
		TProof* fSession;
};

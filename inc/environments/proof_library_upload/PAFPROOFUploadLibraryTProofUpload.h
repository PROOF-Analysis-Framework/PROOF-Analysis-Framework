/**
	@brief PROOF Uplod library using TProof package mechanism.
	@file PAFPROOFUploadLibraryTProofUpload.h
	@class PAFPROOFUploadLibraryTProofUpload
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
 */

#pragma once

#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFUploadLibraryTProofUpload : public PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFUploadLibraryTProofUpload();
		virtual ~PAFPROOFUploadLibraryTProofUpload();

		bool UploadLibrary(PAFLibrary* library);
};

/**
	@brief PROOF Uplod library using a shared file system.
	@file PAFPROOFUploadLibrarySharedDirectory.h
	@class PAFPROOFUploadLibrarySharedDirectory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
 */

#pragma once

#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFUploadLibrarySharedDirectory : public PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFUploadLibrarySharedDirectory();
		virtual ~PAFPROOFUploadLibrarySharedDirectory();

		bool UploadLibrary(PAFLibrary* library);
};

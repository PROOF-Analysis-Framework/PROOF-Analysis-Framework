/**
	@brief PROOF Uplod library using a shared file system.
	@file PAFPROOFUploadLibrarySharedDirectory.cxx
	@class PAFPROOFUploadLibrarySharedDirectory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
 */

#include "PAFPROOFUploadLibrarySharedDirectory.h"

#include "TString.h"

PAFPROOFUploadLibrarySharedDirectory::PAFPROOFUploadLibrarySharedDirectory()
	: PAFPROOFIUploadLibrary()
{

}
PAFPROOFUploadLibrarySharedDirectory::~PAFPROOFUploadLibrarySharedDirectory()
{

}

bool PAFPROOFUploadLibrarySharedDirectory::UploadLibrary(PAFLibrary* library)
{
	TString loader = TString::Format("gSystem->Load(\"%s\");", library->GetFileName().Data());
	gSystem->Load(library->GetFileName().Data());
	fSession->Exec(loader.Data());

	return true;
}

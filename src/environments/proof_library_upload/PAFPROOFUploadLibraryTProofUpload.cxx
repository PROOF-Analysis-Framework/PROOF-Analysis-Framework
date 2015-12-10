/**
	@brief PROOF Uplod library using TProof package mechanism.
	@file PAFPROOFUploadLibraryTProofUpload.h
	@class PAFPROOFUploadLibraryTProofUpload
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
 */

#include "PAFPROOFUploadLibraryTProofUpload.h"

#include "PAF.h"

PAFPROOFUploadLibraryTProofUpload::PAFPROOFUploadLibraryTProofUpload()
	: PAFPROOFIUploadLibrary()
{

}

PAFPROOFUploadLibraryTProofUpload::~PAFPROOFUploadLibraryTProofUpload()
{

}

bool PAFPROOFUploadLibraryTProofUpload::UploadLibrary(PAFLibrary* library)
{
	library->CreatePARFile();
	TString parFileName = library->GetPARFileName();
	gSystem->Load(library->GetFileName());
	fSession->UploadPackage(parFileName.Data(), TProof::kRemoveOld);
	fSession->EnablePackage(library->GetLibraryName(), kTRUE);

	PAF_DEBUG("PAFPROOFUploadLibraryTProofUpload", TString::Format("Loaded %s", library->GetLibraryName().Data()));

	return true;
}

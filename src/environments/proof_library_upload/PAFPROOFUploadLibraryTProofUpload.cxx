
#include "PAFPROOFUploadLibraryTProofUpload.h"

#include "../../PAF.h"

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
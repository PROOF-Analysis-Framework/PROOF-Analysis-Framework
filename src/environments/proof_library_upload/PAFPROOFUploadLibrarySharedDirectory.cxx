
#include "PAFPROOFUploadLibrarySharedDirectory.h"

#include "TString.h"

PAFPROOFUploadLibrarySharedDirectory::PAFPROOFUploadLibrarySharedDirectory()
	: PAFPROOFIUploadLibrary()
{

}

PAFPROOFUploadLibrarySharedDirectory::PAFPROOFUploadLibrarySharedDirectory(TProof* session)
	: PAFPROOFIUploadLibrary(session)
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
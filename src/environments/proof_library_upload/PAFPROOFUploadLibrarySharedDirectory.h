
#pragma once

#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFUploadLibrarySharedDirectory : public PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFUploadLibrarySharedDirectory();
		PAFPROOFUploadLibrarySharedDirectory(TProof* session);
		virtual ~PAFPROOFUploadLibrarySharedDirectory();
		
		bool UploadLibrary(PAFLibrary* library);
};

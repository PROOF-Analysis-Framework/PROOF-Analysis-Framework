
#pragma once

#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFUploadLibrarySharedDirectory : public PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFUploadLibrarySharedDirectory();
		virtual ~PAFPROOFUploadLibrarySharedDirectory();
		
		bool UploadLibrary(PAFLibrary* library);
};

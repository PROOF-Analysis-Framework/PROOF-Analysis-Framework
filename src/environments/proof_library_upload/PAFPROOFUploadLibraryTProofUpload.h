
#pragma once

#include "PAFPROOFIUploadLibrary.h"

class PAFPROOFUploadLibraryTProofUpload : public PAFPROOFIUploadLibrary 
{
	public:
		PAFPROOFUploadLibraryTProofUpload();
		virtual ~PAFPROOFUploadLibraryTProofUpload();
		
		bool UploadLibrary(PAFLibrary* library);
};

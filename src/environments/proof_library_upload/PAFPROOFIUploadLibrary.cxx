/**
	@brief Interface to create a strategy pattern to PROOF libraries upload.
	@file PAFPROOFIUpload.cxx
	@class PAFPROOFIUpload
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-15
*/

#include "PAFPROOFIUploadLibrary.h"

PAFPROOFIUploadLibrary::PAFPROOFIUploadLibrary()
	: fSession(0)
{

}

PAFPROOFIUploadLibrary::~PAFPROOFIUploadLibrary()
{

}

void PAFPROOFIUploadLibrary::SetSession(TProof* session)
{
	fSession = session;
}

TProof* PAFPROOFIUploadLibrary::GetSession()
{
	return fSession;
}

/**
	@brief PAFLibrary which will contain libraries to load in environments.
	@file PAFLibrary.cxx
	@class PAFLibrary
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-17
*/

#include "PAFLibrary.h"

#include "TSystem.h"

#include "../util/PAFStringUtil.h"

#include "../PAF.h"

ClassImp(PAFLibrary);

PAFLibrary::PAFLibrary()
	: fPAFSettings(0), fFileName()
{

}

PAFLibrary::PAFLibrary(PAFISettings* pafsettings, const char* fileName)
	: fPAFSettings(pafsettings), fFileName(fileName)
{

}

void PAFLibrary::SetSettings(PAFISettings* pafsettings)
{
	fPAFSettings = pafsettings;
}

PAFISettings* PAFLibrary::GetSettings()
{
	return fPAFSettings;
}

TString PAFLibrary::GetFileName()
{
	return fFileName;
}

TString PAFLibrary::GetLibraryName()
{
	TString* fileNameCopy = new TString(fFileName);
	std::vector<TString*>* pathParts = PAFStringUtil::Split(fileNameCopy, "/");
	
	TString* fileName = pathParts->at(pathParts->size() - 1);
	TString result((*fileName)(0, fileName->Length() - 3));
	
	delete pathParts;
	delete fileNameCopy;
	
	return result;
}

void PAFLibrary::CreatePARFile()
{
	TString creteparfile_command = TString::Format("%s/bin/MakeParFileLib.sh -s -d %s/packages/ %s", fPAFSettings->GetPAFPATH()->Data(), gSystem->GetBuildDir(), fFileName.Data());
	TString response_createparfile_command = gSystem->GetFromPipe(creteparfile_command);
}

TString PAFLibrary::GetPARFileName()
{	
	TString result = TString::Format("%s/packages/%s.par", gSystem->GetBuildDir(), GetLibraryName().Data());
	
	return result;
}

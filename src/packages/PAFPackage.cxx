/**
	@brief Generic PAFPackage which will contain items to load in environments.
	@file PAFPackage.cxx
	@class PAFPackage
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPackage.h"

#include "TSystem.h"

#include "../PAF.h"

ClassImp(PAFPackage);

PAFPackage::PAFPackage(PAFISettings* pafsettings, const char* name)
 : fPAFSettings(pafsettings), fName(name)
{
	
}

void PAFPackage::PreparePackage()
{
	TString packages_dir = GetPackagesDir();
	gSystem->MakeDirectory(packages_dir);

	TString build_command = GetPreparePackageCommand();
	gSystem->Exec(build_command);
}

TString PAFPackage::GetPreparePackageCommand()
{
	TString package_dir = GetPackageDir();
	if(package_dir == "")
		PAF_ERROR("PAFPackage", "Package not found in repositories.");
	return TString::Format("%s/bin/PreparePackage.sh -s -d %s -r %s %s", fPAFSettings->GetPAFPATH()->Data() , GetPackagesDir().Data(), package_dir.Data(), GetName().Data());
}

void PAFPackage::CreateParFile()
{
	TString creteparfile_command = TString::Format("%s/bin/MakeParFile.sh -s -d %s %s", fPAFSettings->GetPAFPATH()->Data(), GetPackagesDir().Data(), GetName().Data());
	gSystem->Exec(creteparfile_command);
}

void PAFPackage::CompileAsLibrary()
{
	TString compileaslibrary_command = TString::Format("%s/bin/CompileLibrary.sh -s -d %s %s", fPAFSettings->GetPAFPATH()->Data(),  GetPackagesDir().Data(), GetName().Data());
	gSystem->Exec(compileaslibrary_command);
}

TString PAFPackage::GetLibraryFileName()
{
	return TString::Format("%s%s/lib%s.so", GetPackagesDir().Data(), GetName().Data(), GetName().Data());
}

TString PAFPackage::GetParFileName()
{
	return TString::Format("%s%s.par", GetPackagesDir().Data(), GetName().Data());
}

TString PAFPackage::GetPackageDir()
{
	std::vector<TString*>* package_directories = fPAFSettings->GetPackagesDirectories();
	
	for(int i = 0; i < package_directories->size(); i++){
		TString package_filename = TString::Format("%s/%s", package_directories->at(i)->Data(), fName.Data());
		if(gSystem->OpenDirectory(package_filename))
			return *(package_directories->at(i));
	}
	return TString("");
}

TString PAFPackage::GetPackagesDir()
{
	return TString::Format("%s/packages/", gSystem->GetBuildDir());
}


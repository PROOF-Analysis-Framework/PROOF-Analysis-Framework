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

ClassImp(PAFPackage);

void PAFPackage::PreparePackage()
{
	TString packages_dir = GetPackagesDir();
	gSystem->MakeDirectory(packages_dir);

	TString build_command = GetPreparePackageCommand();
	gSystem->Exec(build_command);
}

TString PAFPackage::GetPreparePackageCommand()
{
	return TString::Format("%s/bin/PreparePackage.sh -s -d %s %s", fPAFSettings->GetPAFPATH()->Data() , GetPackagesDir().Data(), GetName().Data());
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

TString PAFPackage::GetPackagesDir()
{
	return TString::Format("%s/packages/", gSystem->GetBuildDir());
}

TString PAFPackage::GetBuildDir()
{
	return TString::Format("%s/", gSystem->GetBuildDir());
}



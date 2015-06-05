/**
	@brief PAF test class to test the get directory method of packages.
	@file PackageGetDirectory.h
	@class PackageGetDirectory
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-05
 */

#include "PackageGetDirectory.h"

#include "PAF/util/PAFStringUtil.h"
#include "PAF/settings/PAFManualSettings.h"

#include "TSystem.h"

int main()
{
	PackageGetDirectory test;
	return PAFTest::Evaluate(&test);
}

void PackageGetDirectory::Initialise()
{
	system("rm -r tmp");
}

void PackageGetDirectory::Test()
{
	TString rootDir = TString(gSystem->pwd()).Append("/tmp");
	TString* pafPath = new TString(gSystem->Getenv("PAFPATH"));

	std::vector<TString*>* repositories = new std::vector<TString*>();
	PAFISettings* settings = new PAFManualSettings(pafPath, repositories);
	SetSettings(settings);
	SetName("Test");
	AssertEquals("", GetPackageDir().Data());

	TString repository1 = rootDir.Copy().Append("/repository1");
	gSystem->mkdir(repository1.Data(), kTRUE);
	repositories->push_back(&repository1);
	delete settings;
	settings = new PAFManualSettings(pafPath, repositories);
	AssertEquals("", GetPackageDir().Data());

	TString package1 = repository1.Copy().Append("/Test");
	gSystem->mkdir(package1.Data(), kTRUE);
	AssertEquals(repository1.Data(), GetPackageDir().Data());

	TString repository2 = rootDir.Copy().Append("/repository2");
	gSystem->mkdir(repository2.Data(), kTRUE);
	repositories->clear();
	repositories->push_back(&repository2);
	delete settings;
	settings = new PAFManualSettings(pafPath, repositories);
	AssertEquals("", GetPackageDir().Data());

	repositories->push_back(&repository1);
	delete settings;
	settings = new PAFManualSettings(pafPath, repositories);
	AssertEquals(repository1.Data(), GetPackageDir().Data());

	repositories->clear();
	repositories->push_back(&repository1);
	repositories->push_back(&repository2);
	delete settings;
	settings = new PAFManualSettings(pafPath, repositories);
	AssertEquals(repository1.Data(), GetPackageDir().Data());
}


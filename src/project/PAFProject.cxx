/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFProject.h"
#include "MakeSimpleSelector.h"
#include "../util/PAFNamedContainer.h"

ClassImp(PAFProject);

void PAFProject::UploadAndEnablePackage(PAFPackage* package)
{
	package->PreparePackage();
	if(fCompileOnSlaves)
	{
		package->CreateParFile();
		fExecutionEnvironment->UploadPackage(package);
		fExecutionEnvironment->EnablePackage(package);
	}
	else
	{
		package->CompileAsLibrary();
		fLibraries.push_back(new PAFLibrary(package->GetLibraryFileName()));
	}
}
void PAFProject::UploadAndEnablePackages(std::vector<PAFPackage*> packages)
{
	for(unsigned int i = 0; i < packages.size(); i++)
		UploadAndEnablePackage(packages[i]);
}

void PAFProject::UploadAndEnablePackages(std::vector<PAFPackageSelector*> packages)
{
	for(unsigned int i = 0; i < packages.size(); i++)
		UploadAndEnablePackage(packages[i]);
}

void PAFProject::LoadLibraries()
{
	for(unsigned int i = 0; i < fLibraries.size(); i++)
		fExecutionEnvironment->LoadLibrary(fLibraries[i]);
}

void PAFProject::PreparePAFAnalysis()
{ 
	TFile* file = new TFile(((TFileInfo*)fDataFiles->GetList()->At(0))->GetCurrentUrl()->GetFile()); //FIXME Smells too bad.
	TTree* tree = (TTree*)file->Get("Tree");
	TString dest = gSystem->GetBuildDir();
	dest += "/PAFAnalysis/";
	gSystem->mkdir(dest.Data());

	MakeSimpleSelector(tree, dest);
	file->Close();

	PAFPackage* package = new PAFPackageTSelector(PAFANALYSIS_NAME);
	UploadAndEnablePackage(package);

	delete file;
}

void PAFProject::AddDynamicHistograms()
{
    for (unsigned int i = 0; i < fDynamicHistograms.size(); i++) {
      fExecutionEnvironment->AddFeedback(fDynamicHistograms[i]);
    }
    fExecutionEnvironment->CreateDrawFeedback();
}

template<typename T>
T PAFProject::CreateObject(const char* className)
{
	TClass result(className);
	return (T)result.New();
}

void CreateSessionDir()
{
	TString buildDir = TString::Format("%s/.paf/BuildDir",gSystem->pwd());
	gSystem->mkdir(buildDir, true);
  	gSystem->SetBuildDir(buildDir);
}

void PAFProject::PrepareEnvironment()
{
	CreateSessionDir();
	PreparePAFAnalysis();

	UploadAndEnablePackages(fPackages);
	UploadAndEnablePackages(fSelectorPackages);

	LoadLibraries();	
}

void PAFProject::PrepareProject()
{
	fExecutionEnvironment->AddInput(fInputParameters); //FIXME
	
	PAFISelector* result = NULL;

	if(fSelectorPackages.size() == 0)
	{
		//TODO Throw an exception.
	}
	else if (fSelectorPackages.size() == 1)
	{
		result = CreateObject<PAFChainItemSelector*>(fSelectorPackages[0]->GetName());
	}
	else
	{
		std::vector<PAFISelector*> selectors;
		for(unsigned int i = 0; i < fSelectorPackages.size(); i++)
			selectors.push_back( 
				CreateObject<PAFISelector*>(fSelectorPackages[i]->GetName()) );
		result = new PAFChainSelector(&selectors);
	}

	fPAFSelector = result;
	fExecutionEnvironment->AddInput(new PAFNamedContainer("PAFSelector", fPAFSelector));
}

void PAFProject::Run()
{
	PrepareEnvironment();
	PrepareProject();
	AddDynamicHistograms();
	PAFBaseSelector* selector = CreateObject<PAFBaseSelector*>(PAFANALYSIS_NAME); 

	selector->SetPAFSelector(fPAFSelector);	
	if(fOutputFile.Length() == 0)
		fExecutionEnvironment->Process(fDataFiles, selector);
	else
		fExecutionEnvironment->Process(fDataFiles, selector, fOutputFile);
	//gPAFModePlugin->Finish();
}

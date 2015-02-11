/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFProject.h"

#include "TSystem.h"

#include "../util/PAFNamedItem.h"
#include "../settings/PAFEnvironmentVariableSettings.h"

#include "../PAF.h"

ClassImp(PAFProject);

PAFISettings*	DEFAULT_PAFISETTINGS = new PAFEnvironmentVariableSettings();
bool			DEFAULT_COMPILE_ON_SLAVES = false;


PAFProject::PAFProject() : fExecutionEnvironment(0), fInputParameters(0), fPAFSelector(0), fPackages(), fSelectorPackages(), fLibraries(), fDataFiles(0), fOutputFile(), fDynamicHistograms(), fPAFSettings(0), fCompileOnSlaves(false)
{
	fInputParameters = new PAFVariableContainer();
	fDataFiles = new TFileCollection("PAFFiles");
	fPAFSettings = DEFAULT_PAFISETTINGS;
	fCompileOnSlaves = DEFAULT_COMPILE_ON_SLAVES;
}

PAFProject::PAFProject(PAFIExecutionEnvironment* executionEnvironment) : fExecutionEnvironment(0), fInputParameters(0), fPAFSelector(0), fPackages(), fSelectorPackages(), fLibraries(), fDataFiles(0), fOutputFile(), fDynamicHistograms(), fPAFSettings(0), fCompileOnSlaves(false) 
{
	fExecutionEnvironment = executionEnvironment;
	fInputParameters = new PAFVariableContainer();
	fDataFiles = new TFileCollection("PAFFiles");
	fPAFSettings = DEFAULT_PAFISETTINGS;
	fCompileOnSlaves = DEFAULT_COMPILE_ON_SLAVES;
}


PAFProject::~PAFProject()
{
	delete fInputParameters;
	delete fDataFiles;
}

void PAFProject::SetPAFSettings(PAFISettings* settings)
{
	delete fPAFSettings;
	fPAFSettings = settings;
}


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
	
	UploadAndEnablePackages(fPackages);
	UploadAndEnablePackages(fSelectorPackages);

	LoadLibraries();
}

void PAFProject::PreparePAFSelector()
{
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
}

void PAFProject::Run()
{
	PAF_DEBUG("Project", "Launching configured project");
	PrepareEnvironment();
	PreparePAFSelector();
	AddDynamicHistograms();
	
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFParams", fInputParameters));
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFSelector", fPAFSelector));
	
	PAFBaseSelector* selector = new PAFBaseSelector(); 
	
	selector->SetSelectorParams(fInputParameters);
	selector->SetPAFSelector(fPAFSelector);
	
	if(fOutputFile.Length() == 0)
		fExecutionEnvironment->Process(fDataFiles, selector);
	else
		fExecutionEnvironment->Process(fDataFiles, selector, fOutputFile);

	//gPAFModePlugin->Finish();
}

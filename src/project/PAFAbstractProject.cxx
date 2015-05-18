/**
	@brief Abstract class with common funcionality of different PAFIProject.
	@file PAFAbstractProject.h
	@class PAFAbstractProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-18
*/

#include "PAFAbstractProject.h"

#include "TSystem.h"

#include "../util/PAFNamedItem.h"
#include "../settings/PAFEnvironmentVariableSettings.h"
#include "../util/PAFStopWatch.h"

#include "../PAF.h"

#include "../environments/PAFPROOFLiteEnvironment.h"

ClassImp(PAFAbstractProject);

PAFISettings*	DEFAULT_PAFISETTINGS = new PAFEnvironmentVariableSettings();
bool            DEFAULT_COMPILE_ON_SLAVES = false;

PAFAbstractProject::PAFAbstractProject()
{
	InitMembers();
	fExecutionEnvironment = new PAFPROOFLiteEnvironment(4);
}

PAFAbstractProject::PAFAbstractProject(PAFIExecutionEnvironment* executionEnvironment)
	: fExecutionEnvironment(executionEnvironment)
{
	InitMembers();
}

PAFAbstractProject::~PAFAbstractProject()
{

}

void PAFAbstractProject::InitMembers()
{
	fInputParameters = new PAFVariableContainer();
	fPackages = new std::vector<PAFPackage*>();
	fSelectorPackages = new std::vector<PAFPackageSelector*>();
	fLibraries = new std::vector<PAFLibrary*>();
	fOutputFile = TString();
	fDynamicHistograms = new std::vector<TString>();
	fPAFSettings = DEFAULT_PAFISETTINGS;
	fCompileOnSlaves = DEFAULT_COMPILE_ON_SLAVES;
}

void PAFAbstractProject::AddPackage(TString& packageName)
{
	PAFPackage* result = new PAFPackage(GetPAFSettings(), packageName);
	AddPackage(result);
}

void PAFAbstractProject::AddPackage(const char* packageName)
{
	TString tPackageName(packageName);
	AddPackage(tPackageName);
}

void PAFAbstractProject::AddPackage(PAFPackage* package)
{
	fPackages->push_back(package);
}

void PAFAbstractProject::AddSelectorPackage(TString& packageSelectorName)
{
	PAFPackageSelector* result = new PAFPackageSelector(GetPAFSettings(), packageSelectorName);
	AddSelectorPackage(result);

}

void PAFAbstractProject::AddSelectorPackage(const char* packageSelectorName)
{
	TString tPackageSelectorName(packageSelectorName);
	AddSelectorPackage(tPackageSelectorName);
}

void PAFAbstractProject::AddSelectorPackage(PAFPackageSelector* packageSelector)
{
	fSelectorPackages->push_back(packageSelector);
}

void PAFAbstractProject::AddLibrary(TString& libraryName)
{
	PAFLibrary* result = new PAFLibrary(fPAFSettings, libraryName);
	AddLibrary(result);
}

void PAFAbstractProject::AddLibrary(const char* libraryName)
{
	TString tLibraryName(libraryName);
	AddLibrary(tLibraryName);
}

void PAFAbstractProject::AddLibrary(PAFLibrary* library)
{
	fLibraries->push_back(library);
}

void PAFAbstractProject::SetPAFSettings(PAFISettings* settings)
{
	delete fPAFSettings;
	fPAFSettings = settings;
}

void PAFAbstractProject::AddDynamicHistogram(TString& histogram)
{
	fDynamicHistograms->push_back(histogram);
}

void PAFAbstractProject::AddDynamicHistogram(const char* histogram)
{
	TString tHistogram(histogram);
	AddDynamicHistogram(tHistogram);
}

void PAFAbstractProject::AddDynamicHistograms()
{
    for (unsigned int i = 0; i < fDynamicHistograms->size(); i++) 
	{
      fExecutionEnvironment->AddFeedback(fDynamicHistograms->at(i));
    }
    fExecutionEnvironment->CreateDrawFeedback();
}

template<typename T>
T PAFAbstractProject::CreateObject(const char* className)
{
	TClass result(className);
	return (T)result.New();
}

void CreateSessionDir()
{
	//TString buildDir = "/tmp/PAF/BuildDir";
	TString buildDir = TString::Format("%s/.paf/BuildDir",gSystem->pwd());
	gSystem->mkdir(buildDir, true);
  	gSystem->SetBuildDir(buildDir);
}

void PAFAbstractProject::PreparePackage(PAFPackage* package)
{
	package->PreparePackage();
	if(fCompileOnSlaves)
	{
		package->CreateParFile();
	}
	else
	{
		package->CompileAsLibrary();
		fLibraries->push_back(new PAFLibrary(fPAFSettings, package->GetLibraryFileName()));
	}
}

void PAFAbstractProject::PreparePackages()
{
	CreateSessionDir();
	
	for(unsigned int i = 0; i < fPackages->size(); i++)
	{
		PreparePackage(fPackages->at(i));
	}

	for(unsigned int i = 0; i < fSelectorPackages->size(); i++)
	{
		PreparePackage(fSelectorPackages->at(i));
	}
}

void PAFAbstractProject::LoadProjectItems()
{
	for(unsigned int i = 0; i < fLibraries->size(); i++)
	{
		fExecutionEnvironment->LoadLibrary(fLibraries->at(i));
	}

	if(fCompileOnSlaves)
	{
		for(unsigned int i = 0; i < fPackages->size(); i++)
		{
			fExecutionEnvironment->UploadPackage(fPackages->at(i));
			fExecutionEnvironment->EnablePackage(fPackages->at(i));
		}

		for(unsigned int i = 0; i < fSelectorPackages->size(); i++)
		{
			fExecutionEnvironment->UploadPackage(fSelectorPackages->at(i));
			fExecutionEnvironment->EnablePackage(fSelectorPackages->at(i));
		}
	}
}

void PAFAbstractProject::PreparePAFSelector()
{
	PAFISelector* result = NULL;

	if(fSelectorPackages->size() == 0)
	{
		PAF_FATAL("PAFProject", "No PAFSelector specified.");
	}
	else if (fSelectorPackages->size() == 1)
	{
		result = CreateObject<PAFChainItemSelector*>(fSelectorPackages->at(0)->GetName());
	}
	else
	{
		std::vector<PAFISelector*>* selectors = new std::vector<PAFISelector*>();
		for(unsigned int i = 0; i < fSelectorPackages->size(); i++)
		{	
			selectors->push_back( 
				CreateObject<PAFISelector*>(fSelectorPackages->at(i)->GetName()));
		}
		result = new PAFChainSelector(selectors);
	}

	fPAFSelector = result;
}

void PAFAbstractProject::Run()
{
	PAFStopWatch timer;
	timer.Start();
	PreparePackages();
	PAF_DEBUG("Project", "Launching configured project.");
	fExecutionEnvironment->Initialise();
	timer.TakeTime("Execution environment initilized");
	LoadProjectItems();
	PreparePAFSelector();
	AddDynamicHistograms();
	
	fExecutionEnvironment->SetOutput(fOutputFile);
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFParams", fInputParameters));
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFSelector", fPAFSelector));
	
	PAFBaseSelector* selector = new PAFBaseSelector(); 
	selector->SetSelectorParams(fInputParameters);
	selector->SetPAFSelector(fPAFSelector);

	timer.TakeTime("Environment ready");
	PAF_DEBUG("PAFProject", "Launching process");
	
	doRun(selector);
	
	timer.TakeTime("Processed");
	PAF_DEBUG("PAFProject", "Process completed.");
	fExecutionEnvironment->Dispose();
}

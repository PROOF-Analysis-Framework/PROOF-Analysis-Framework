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
#include "../util/PAFStopWatch.h"

#include "../PAF.h"

#include "../environments/PAFPROOFLiteEnvironment.h"

ClassImp(PAFProject);

PAFISettings*	DEFAULT_PAFISETTINGS = new PAFEnvironmentVariableSettings();
bool		DEFAULT_COMPILE_ON_SLAVES = false;

PAFProject::PAFProject()
{
	InitMembers();
	
	fExecutionEnvironment = new PAFPROOFLiteEnvironment(2);
}

PAFProject::PAFProject(PAFIExecutionEnvironment* executionEnvironment) 
{
	InitMembers();
	
	fExecutionEnvironment = executionEnvironment;
}


PAFProject::~PAFProject()
{
	delete fExecutionEnvironment;
	delete fInputParameters;
	delete fPAFSelector;
	delete fPackages;
	delete fSelectorPackages;
	delete fLibraries;
	delete fDataFiles;
	delete fDynamicHistograms;
	delete fPAFSettings;
}

void PAFProject::InitMembers()
{
	fInputParameters = new PAFVariableContainer();
	fPackages = new std::vector<PAFPackage*>();
	fSelectorPackages = new std::vector<PAFPackageSelector*>();
	fLibraries = new std::vector<PAFLibrary*>();
	fDataFiles = new TFileCollection("PAFFiles");
	fOutputFile = TString();
	fDynamicHistograms = new std::vector<TString>();
	fPAFSettings = DEFAULT_PAFISETTINGS;
	fCompileOnSlaves = DEFAULT_COMPILE_ON_SLAVES;
}

void PAFProject::AddPackage(TString& packageName)
{
	PAFPackage* result = new PAFPackage(GetPAFSettings(), packageName);
	AddPackage(result);
}

void PAFProject::AddPackage(const char* packageName)
{
	TString tPackageName(packageName);
	AddPackage(tPackageName);
}

void PAFProject::AddPackage(PAFPackage* package)
{
	fPackages->push_back(package);
}

void PAFProject::AddSelectorPackage(TString& packageSelectorName)
{
	PAFPackageSelector* result = new PAFPackageSelector(GetPAFSettings(), packageSelectorName);
	AddSelectorPackage(result);

}

void PAFProject::AddSelectorPackage(const char* packageSelectorName)
{
	TString tPackageSelectorName(packageSelectorName);
	AddSelectorPackage(tPackageSelectorName);
}

void PAFProject::AddSelectorPackage(PAFPackageSelector* packageSelector)
{
	fSelectorPackages->push_back(packageSelector);
}

void PAFProject::AddLibrary(TString& libraryName)
{
	PAFLibrary* result = new PAFLibrary(libraryName);
	AddLibrary(result);
}

void PAFProject::AddLibrary(const char* libraryName)
{
	TString tLibraryName(libraryName);
	AddLibrary(tLibraryName);
}

void PAFProject::AddLibrary(PAFLibrary* library)
{
	fLibraries->push_back(library);
}

void PAFProject::AddDataFile(TString& fileName)
{
	//TFileInfo* result = new TFileInfo(fileName);
	//AddDataFile(result);
	fDataFiles->Add(fileName);
}

void PAFProject::AddDataFile(const char* fileName)
{
	TString tFileName(fileName);
	AddDataFile(tFileName);
}

void PAFProject::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

void PAFProject::SetPAFSettings(PAFISettings* settings)
{
	delete fPAFSettings;
	fPAFSettings = settings;
}

void PAFProject::AddDynamicHistogram(TString& histogram)
{
	fDynamicHistograms->push_back(histogram);
}

void PAFProject::AddDynamicHistogram(const char* histogram)
{
	TString tHistogram(histogram);
	AddDynamicHistogram(tHistogram);
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
		fLibraries->push_back(new PAFLibrary(package->GetLibraryFileName()));
	}
}
void PAFProject::UploadAndEnablePackages(std::vector<PAFPackage*>* packages)
{
	for(unsigned int i = 0; i < packages->size(); i++)
	{
		UploadAndEnablePackage(packages->at(i));
	}
}

void PAFProject::UploadAndEnablePackages(std::vector<PAFPackageSelector*>* packages)
{
	for(unsigned int i = 0; i < packages->size(); i++)
	{
		UploadAndEnablePackage(packages->at(i));
	}
}

void PAFProject::LoadLibraries()
{
	for(unsigned int i = 0; i < fLibraries->size(); i++)
	{
		fExecutionEnvironment->LoadLibrary(fLibraries->at(i));
	}
}

void PAFProject::AddDynamicHistograms()
{
    for (unsigned int i = 0; i < fDynamicHistograms->size(); i++) 
	{
      fExecutionEnvironment->AddFeedback(fDynamicHistograms->at(i));
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

void PAFProject::Run()
{
	PAFStopWatch* timer = new PAFStopWatch();
	timer->Start();
	PAF_DEBUG("Project", "Launching configured project.");
	fExecutionEnvironment->Initialise();
	PrepareEnvironment();
	PreparePAFSelector();
	AddDynamicHistograms();
	timer->TakeTime("Environment ready");
	
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFParams", fInputParameters));
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFSelector", fPAFSelector));
	
	PAFBaseSelector* selector = new PAFBaseSelector(); 
	selector->SetSelectorParams(fInputParameters);
	selector->SetPAFSelector(fPAFSelector);
	
	PAF_DEBUG("PAFProject", "Launching process");
	
	if(fOutputFile.Length() == 0)
	{
		fExecutionEnvironment->Process(fDataFiles, selector);
	}
	else
	{
		fExecutionEnvironment->Process(fDataFiles, selector, fOutputFile);
	}
	timer->TakeTime("Processed");
	PAF_DEBUG("PAFProject", "Process completed.");
	fExecutionEnvironment->Dispose();
}

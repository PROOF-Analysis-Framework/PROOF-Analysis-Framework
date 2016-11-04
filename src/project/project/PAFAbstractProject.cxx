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

#include "PAF.h"
#include "PAFNamedItem.h"
#include "PAFEnvironmentVariableSettings.h"
#include "PAFStopWatch.h"
#include "PAFPROOFLiteEnvironment.h"
#include "PAFProgressUpdatedLogger.h"

ClassImp(PAFAbstractProject);

PAFISettings*		DEFAULT_PAFISETTINGS = new PAFEnvironmentVariableSettings();
PAFIProgressUpdated* 	DEFAULT_PROGRESSUPDATED = new PAFProgressUpdatedLogger();
bool            	DEFAULT_COMPILE_ON_SLAVES = false;
TString			DEFAULT_OUTPUT_FILE = TString("pafoutput.root");

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
	fOutputFile = DEFAULT_OUTPUT_FILE;
	fDynamicHistograms = new std::vector<TString>();
	fPAFSettings = DEFAULT_PAFISETTINGS;
	fCompileOnSlaves = DEFAULT_COMPILE_ON_SLAVES;
	fProgressUpdated = DEFAULT_PROGRESSUPDATED;
}

void PAFAbstractProject::SetExecutionEnvironment(PAFIExecutionEnvironment* executionEnvironment)
{
	fExecutionEnvironment = executionEnvironment;
}

PAFIExecutionEnvironment* PAFAbstractProject::GetExecutionEnvironment()
{
	return fExecutionEnvironment;
}

void PAFAbstractProject::SetPackages(std::vector< PAFPackage* >* packages)
{
	fPackages = packages;
}

std::vector< PAFPackage* >* PAFAbstractProject::GetPackages()
{
	return fPackages;
}

void DefaultProgressUpdatedFunction(Long64_t /*total*/, Long64_t /*proc*/)
{

}

void PAFAbstractProject::AddPackage(const TString& packageName)
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

void PAFAbstractProject::SetSelectorPackages(std::vector< PAFPackageSelector* >* selectorPackages)
{
	fSelectorPackages = selectorPackages;
}

std::vector< PAFPackageSelector* >* PAFAbstractProject::GetSelectorPackages()
{
	return fSelectorPackages;
}

void PAFAbstractProject::AddSelectorPackage(const TString& packageSelectorName)
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

void PAFAbstractProject::SetLibraries(std::vector< PAFLibrary* >* libraries)
{
	fLibraries = libraries;
}

std::vector< PAFLibrary* >* PAFAbstractProject::GetLibraries()
{
	return fLibraries;
}

void PAFAbstractProject::AddLibrary(const TString& libraryName)
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

PAFISettings* PAFAbstractProject::GetPAFSettings()
{
	return fPAFSettings;
}

void PAFAbstractProject::SetOutputFile(const TString& fileName)
{
	fOutputFile = fileName;
}

void PAFAbstractProject::SetOutputFile(const char* fileName)
{
	fOutputFile = TString(fileName);
}

TString PAFAbstractProject::GetOutputFile() const
{
	return fOutputFile;
}

void PAFAbstractProject::SetInputParameters(PAFVariableContainer* inputParameters)
{
	fInputParameters = inputParameters;
}

PAFVariableContainer* PAFAbstractProject::GetInputParameters()
{
	return fInputParameters;
}

void PAFAbstractProject::SetDynamicHistograms(std::vector< TString >* dynamicHistograms)
{
	fDynamicHistograms = dynamicHistograms;
}

std::vector< TString >* PAFAbstractProject::GetDynamicHistograms()
{
	return fDynamicHistograms;
}

void PAFAbstractProject::AddDynamicHistogram(const TString& histogram)
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
    // Return if no dynamic histogram was set
    if (! fDynamicHistograms->size()) return;

    // Add dynamic histograms
    for (unsigned int i = 0; i < fDynamicHistograms->size(); i++) 
    {
      fExecutionEnvironment->AddFeedback(fDynamicHistograms->at(i));
    }

    // Create feedbak so dynamic histograms are shown
    fExecutionEnvironment->CreateDrawFeedback();
}

void PAFAbstractProject::SetCompileOnSlaves(bool compileOnSlaves)
{
	fCompileOnSlaves = compileOnSlaves;
}

bool PAFAbstractProject::GetCompileOnSlaves() const
{
	return fCompileOnSlaves;
}

void PAFAbstractProject::SetProgressUpdated(PAFIProgressUpdated* progressUpdated)
{
	fProgressUpdated = progressUpdated;
}

PAFIProgressUpdated* PAFAbstractProject::GetProgressUpdatedFunction()
{
	return fProgressUpdated;
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
		PAF_FATAL("PAAbstractFProject", "No PAFSelector specified.");
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

TList* PAFAbstractProject::Run()
{
	PAF_DEBUG("PAFAbstractProject", "Checking project configuration.");
	doProjectChecks();


	// Initialize timer
	PAFStopWatch timer;
	timer.Start();


	// Prepare and compile if needed the packages
	PAF_DEBUG("PAFAbstractProject", "Preparing and compiling packages.");
	PreparePackages();
	timer.TakeTime("Packages preparation finished");


	// Starting the environment
	PAF_DEBUG("PAFAbstractProject", "Initializing the selected environment.");
	fExecutionEnvironment->Initialise();
	timer.TakeTime("Execution environment initialized");

	// Loading libraries
	PAF_DEBUG("PAFAbstractProject", "Loading libraries.");
	LoadProjectItems();

	// Deal with selectors
	PAF_DEBUG("PAFAbstractProject", "Compiling and uploading selectors.");	
	PreparePAFSelector();
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFSelector", fPAFSelector));
	PAFBaseSelector* selector = new PAFBaseSelector(); 
	selector->SetSelectorParams(fInputParameters);
	selector->SetPAFSelector(fPAFSelector);
	selector->SetOutputFile(fOutputFile);
	
	// Set dynamic histograms and progress update
	PAF_DEBUG("PAFAbstractProject", "Final settings.");	
	AddDynamicHistograms();
	fExecutionEnvironment->SetProgressUpdated(fProgressUpdated);

	// Upload input parameters
	PAF_DEBUG("PAFAbstractProject", "Upload input parameters.");	
	fExecutionEnvironment->AddInput(new PAFNamedItem("PAFParams", fInputParameters));


	timer.TakeTime("Environment ready");


	PAF_DEBUG("PAFAbstractProject", "Processing data.");
	doRun(selector);
	timer.TakeTime("Processed");

	PAF_DEBUG("PAFAbstractProject", "Process completed. Dispose.");
	fExecutionEnvironment->Dispose();

	return selector->GetOutputList();
}

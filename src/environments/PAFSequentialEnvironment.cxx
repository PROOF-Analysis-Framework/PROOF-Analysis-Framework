/**
	@brief Implementation of PAFIExecutionEnvironment to work in sequential mode.
	@file PAFSequentialEnvironment.cxx
	@class PAFSequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-02-02
*/

#include "PAFSequentialEnvironment.h"
#include "TSystem.h"
#include "TFile.h"
#include "TFileInfo.h"

#include "../PAF.h"

void PAFSequentialEnvironment::AddInput(TObject* obj)
{
	fInputList.Add(obj);
}

void PAFSequentialEnvironment::AddFeedback(const char* name)
{
	//TODO
}

TDrawFeedback* PAFSequentialEnvironment::CreateDrawFeedback()
{
	//TODO
	return NULL;
}

void PAFSequentialEnvironment::Process(TFileCollection* dataFiles, 
										PAFBaseSelector* selector)
{
	selector->SetInputList(&fInputList);
	selector->SlaveBegin(NULL);
	
	for(int i = 0; i < dataFiles->GetNFiles(); i++){
		TFileInfo* fileinfo = (TFileInfo*)dataFiles->GetList()->At(i);
		TFile file(fileinfo->GetCurrentUrl()->GetFile());
		TTree* tree = (TTree*)file.Get("Tree"); //TODO There is a dataFiles->GetDefaultTreeName();

		selector->Init(tree);
		
		for(int entry = 0; entry < tree->GetEntriesFast(); entry++)
			selector->Process(entry);
		
		delete tree;
	}
	
	selector->Terminate();
}

void PAFSequentialEnvironment::Process(TFileCollection* dataFiles,
										PAFBaseSelector* selector,
										TString& outputFile)
{
}

bool PAFSequentialEnvironment::UploadPackage(PAFPackage* package)
{
	//Nothing to do here.
	return true;
}

bool PAFSequentialEnvironment::EnablePackage(PAFPackage* package)
{
	return gSystem->Load(package->GetName()) == 0;
}

bool PAFSequentialEnvironment::LoadLibrary(PAFLibrary* library)
{
	return gSystem->Load(library->GetFileName()) == 0;
}

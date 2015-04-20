/**
	@brief Implementation of PAFIExecutionEnvironment to work in sequential mode.
	@file PAFSequentialEnvironment.cxx
	@class PAFSequentialEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-02
*/

#include "PAFSequentialEnvironment.h"

#include <vector>

#include "TSystem.h"
#include "TFile.h"
#include "TFileInfo.h"
#include "TCanvas.h"
#include "TH1.h"

#include "../PAF.h"

PAFSequentialEnvironment::PAFSequentialEnvironment()
	: PAFIExecutionEnvironment()
{
	InitMembers();
}

PAFSequentialEnvironment::~PAFSequentialEnvironment()
{
	delete fInputList;
	delete fFeedbackCanvas;
}

void PAFSequentialEnvironment::InitMembers()
{
	fOutputFile = TString();
	 fInputList = new TList();
	 fFeedbackCanvas = new PAFVariableContainer();
}

void PAFSequentialEnvironment::SetOutput(TString& outputFile)
{
	fOutputFile = outputFile;
}

void PAFSequentialEnvironment::AddInput(TObject* obj)
{
	fInputList->Add(obj);
}

void PAFSequentialEnvironment::AddFeedback(const char* name)
{
	TObject* result = new TCanvas(name, name);
	fFeedbackCanvas->Add(name, result);
}

TDrawFeedback* PAFSequentialEnvironment::CreateDrawFeedback()
{
	return NULL;
}

void PAFSequentialEnvironment::Process(PAFBaseSelector* selector, Long64_t nentries)
{
	if(fOutputFile.Length() > 0)
	{
		PAF_FATAL("PAFSequentialEnvironment", "Process with output file is not implemented yet");
	}

	selector->SetInputList(fInputList);
	selector->SlaveBegin(NULL);
	//selector->Init(tree);

	for(Long64_t i = 0; i < nentries; i++)
	{
		selector->Process(i);
		if(i % 10000 == 0)
		{
			DrawFeedback(selector);
		}
	}
	
	DrawFeedback(selector);
	selector->Terminate();
}


void PAFSequentialEnvironment::Process(PAFBaseSelector* selector, TFileCollection* dataFiles)
{
	if(fOutputFile.Length() > 0)
	{
		PAF_FATAL("PAFSequentialEnvironment", "Process with output file is not implemented yet");
	}

	selector->SetInputList(fInputList);
	selector->SlaveBegin(NULL);
	for(int i = 0; i < dataFiles->GetNFiles(); i++)
	{
		TFileInfo* fileinfo = (TFileInfo*)dataFiles->GetList()->At(i);
		TFile file(fileinfo->GetCurrentUrl()->GetFile());
		TTree* tree = (TTree*)file.Get("Tree"); //TODO There is a dataFiles->GetDefaultTreeName();

		selector->Init(tree);
		
		for(int entry = 0; entry < tree->GetEntriesFast(); entry++)
		{
			selector->Process(entry);
			if(entry % 10000 == 0)
				DrawFeedback(selector);
		}
		
		delete tree;
	}
	DrawFeedback(selector);
	selector->Terminate();
}

void PAFSequentialEnvironment::DrawFeedback(TSelector* selector)
{
	std::vector<TString>* feedbacks = fFeedbackCanvas->GetKeys();
	for(unsigned int i = 0; i < feedbacks->size(); i++){
		TString item = feedbacks->at(i);
		TCanvas* canvas = fFeedbackCanvas->Get<TCanvas*>(item);
		canvas->cd();
		TH1* th1 = dynamic_cast<TH1*>(selector->GetOutputList()->FindObject(item));
		if(th1) th1->Draw();
		canvas->Update();
	}
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

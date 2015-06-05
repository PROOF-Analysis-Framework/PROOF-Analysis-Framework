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
	fInputList = new TList();
	fFeedbackCanvas = new PAFVariableContainer();
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


void PAFSequentialEnvironment::Process(PAFBaseSelector* selector, TDSet* dataFiles)
{
	selector->SetInputList(fInputList);
	selector->SlaveBegin(NULL);
	
	TDSetElement* item = NULL;
	TList* listDataFiles = dataFiles->GetListOfElements();
	for(int i = 0; i < listDataFiles->GetEntries(); i++)
	{
		item = (TDSetElement*)listDataFiles->At(i);

		TString treePath = TString::Format("%s/%s", item->GetDirectory(), item->GetObjName());

		PAF_DEBUG("PAFSequentialEnvironment", TString::Format("Processing tree \"%s\" in file \"%s\".", treePath.Data(), item->GetFileName()));

		TFile file(item->GetFileName());
		TTree* tree = (TTree*)file.Get(treePath.Data());

		selector->Init(tree);

		Long64_t entries = tree->GetEntriesFast();
		for(int entry = 0; entry < entries; entry++)
		{
			selector->Process(entry);
			if(entry % 10000 == 0)
			{
				DrawFeedback(selector);
			}
		}
		
		delete tree;
	}
	DrawFeedback(selector);
	selector->Terminate();
}

void PAFSequentialEnvironment::DrawFeedback(TSelector* selector)
{
	TList* feedbacks = fFeedbackCanvas->GetKeys();
	for(int i = 0; i < feedbacks->GetEntries(); i++)
	{
		TObjString* item = (TObjString*)feedbacks->At(i);
		TCanvas* canvas = fFeedbackCanvas->Get<TCanvas*>(item->GetTitle());
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

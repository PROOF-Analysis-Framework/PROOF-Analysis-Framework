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

#include "PAF.h"
#include "PAFFindHelper.h"

PAFSequentialEnvironment::PAFSequentialEnvironment()
	: PAFIExecutionEnvironment(), fInputList(0), fFeedbackCanvas(0), fProgressUpdated(0)
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

        //PAF_DEBUG("PAFSequentialEnvironment::AddInput", "Entering");
	// Check that we are not adding again the input parameter
        if (TString(obj->IsA()->GetName()).EqualTo("PAFNamedItem")) {
	  if (TString(obj->GetName()).EqualTo("PAFParams")) {
	    TObject* currentparams = 0;
	    for (unsigned int i = 0; i < fInputList->GetEntries(); i++) {
	      currentparams = fInputList->At(i);
	      if (TString(currentparams->GetName()).EqualTo("PAFParams")) {
		fInputList->Remove(currentparams);
		delete currentparams;
		break;
	      }
	    }
	  }
	}
	
	fInputList->Add(obj);
	//PAF_DEBUG("PAFSequentialEnvironment::AddInput", "Listado de fInputList");
	//fInputList->Dump();
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

void PAFSequentialEnvironment::SetProgressUpdated(PAFIProgressUpdated* progressUpdated)
{
	fProgressUpdated = progressUpdated;
}

PAFIProgressUpdated* PAFSequentialEnvironment::GetProgressUpdated()
{
	return fProgressUpdated;
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

Long64_t PAFSequentialEnvironment::GetEntriesFrom(Long64_t passedEntries, Long64_t firstEvent)
{
	return firstEvent <= passedEntries ? 0 : firstEvent - passedEntries;
}

Long64_t PAFSequentialEnvironment::GetEntriesTo(Long64_t entriesTree, Long64_t passedEntries, Long64_t firstEvent, Long64_t nEvents)
{
	if (nEvents == -1)
	{
		return entriesTree;
	}
	Long64_t lastEvent = firstEvent + nEvents;
	Long64_t lastEventThisTree = lastEvent - passedEntries;
	return lastEventThisTree > entriesTree ? entriesTree : lastEventThisTree;
}

Long64_t PAFSequentialEnvironment::GetEntriesTotal(TDSet* dataFiles)
{
	Long64_t result = 0;

	TList* listDataFiles = dataFiles->GetListOfElements();
	for(int i = 0; i < listDataFiles->GetEntries(); i++)
	{
		TDSetElement* item = (TDSetElement*)listDataFiles->At(i);

		TString treePath(item->GetObjName());
		if(!TString(item->GetDirectory()).IsNull())
		{
			treePath.Insert(0, TString::Format("%s/", item->GetDirectory()));
		}

		PAF_DEBUG("PAFSequentialEnvironment", TString::Format("Getting tree \"%s\" in file \"%s\".", treePath.Data(), item->GetFileName()));

		TFile file(item->GetFileName());
		TTree* tree = (TTree*)file.Get(treePath.Data());	
		result += tree->GetEntriesFast();

		delete tree;
		file.Close();
	}

	return result;
}

void PAFSequentialEnvironment::Process(PAFBaseSelector* selector, TDSet* dataFiles, Long64_t firstEvent, Long64_t nEvents)
{
	selector->SetInputList(fInputList);
	selector->SlaveBegin(NULL);
	
	Long64_t total = nEvents == -1 ? GetEntriesTotal(dataFiles) - firstEvent : nEvents;
	Long64_t processedEvents = 0;
	Long64_t passedEntries = 0;
	
	TList* listDataFiles = dataFiles->GetListOfElements();
	for(Int_t i = 0; i < listDataFiles->GetEntries(); i++)
	{
		TDSetElement* item = (TDSetElement*)listDataFiles->At(i);

		TString treePath(item->GetObjName());
		if(!TString(item->GetDirectory()).IsNull())
		{
			treePath.Insert(0, TString::Format("%s/", item->GetDirectory()));
		}

		PAF_DEBUG("PAFSequentialEnvironment", TString::Format("Processing tree \"%s\" in file \"%s\".", treePath.Data(), item->GetFileName()));

		TFile file(item->GetFileName());
		TTree* tree = (TTree*)file.Get(treePath.Data());

		selector->Init(tree);

		Long64_t from = GetEntriesFrom(passedEntries, firstEvent);
		Long64_t to = GetEntriesTo(tree->GetEntriesFast(), passedEntries, firstEvent, nEvents);
		fProgressUpdated->ProgressUpdated(total, processedEvents);

		//Rate at which progress is printed in the terminal set to
		//happen every ~1%
		int updateRate = total < 100? 1:total/100; 

		//Loop over the events
		for(Long64_t entry = from; entry < to; entry++)
		{
			selector->Process(entry);
			processedEvents++;
			if(processedEvents % updateRate == 0)
			{
				DrawFeedback(selector);
				fProgressUpdated->ProgressUpdated(total, processedEvents);
			}	
		}

		passedEntries = passedEntries + tree->GetEntriesFast();

		delete tree;
		file.Close();
	}
	// Print and plot results at the end
	fProgressUpdated->ProgressUpdated(total, processedEvents);
	DrawFeedback(selector);

	selector->Terminate();
}

void PAFSequentialEnvironment::DrawFeedback(TSelector* selector)
{
	TList* feedbacks = fFeedbackCanvas->GetKeys();
	for(Int_t i = 0; i < feedbacks->GetEntries(); i++)
	{
		TObjString* item = (TObjString*)feedbacks->At(i);
		TCanvas* canvas = fFeedbackCanvas->Get<TCanvas*>(item->GetTitle());
		canvas->cd();
		TH1* th1 = dynamic_cast<TH1*>(selector->GetOutputList()->FindObject(item));
		if(th1) th1->Draw();
		canvas->Update();
	}
}

bool PAFSequentialEnvironment::UploadPackage(PAFPackage* /*package*/)
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

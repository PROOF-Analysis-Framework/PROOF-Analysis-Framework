/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
 */

#include "PAFProject.h"

#include "PAFStringUtil.h"

ClassImp(PAFProject);

PAFProject::PAFProject()
	: PAFAbstractProject()
{
	InitMembers();
}

PAFProject::PAFProject(PAFIExecutionEnvironment* executionEnvironment) 
	: PAFAbstractProject(executionEnvironment)
{
	InitMembers();
}

void PAFProject::InitMembers()
{
        fSampleCollection = new PAFSampleCollection;
	fFirstEvent = 0;
	fNEvents = -1;
}

PAFProject::~PAFProject()
{
	delete fSampleCollection;
}


void PAFProject::SetDefaultTreeName(const TString& defaultTreeName) {
  if (!fSampleCollection)
    PAF_FATAL("PAFProject", "You tried to set the default tree name before adding input files or samples");
  if (fSampleCollection->GetNSamples() == 0)
    PAF_FATAL("PAFProject", "You tried to set the default tree name before adding input files or samples");
    
  fSampleCollection->SetDefaultTreeName(defaultTreeName);
}


TDSet* PAFProject::GetDataFiles(const char* samplename)
{
        return fSampleCollection->GetDataFiles(samplename);
}

void PAFProject::SetDataFiles(TDSet* dataFiles, const char* samplename)
{
       if (!fSampleCollection)
	 fSampleCollection = new PAFSampleCollection;

       PAFSample* thesample = CheckAndCreateSample(samplename);
       thesample->SetDataFiles(dataFiles);
}

void PAFProject::AddDataFile(const TString& fileName, const char* objname, const char* samplename)
{
	if (!fSampleCollection)
	  fSampleCollection = new PAFSampleCollection;
	
	PAFSample* thesample = CheckAndCreateSample(samplename);
	thesample->AddDataFile(fileName, objname);
}


void PAFProject::AddDataFile(TFileInfo* dataFile, 
			     const char* samplename)
{
	if (!fSampleCollection)
	  fSampleCollection = new PAFSampleCollection;
	
	PAFSample* thesample = CheckAndCreateSample(samplename);
	thesample->AddDataFile(dataFile);
}

void PAFProject::AddDataFiles(const std::vector<TString>& files, const char* objname, 
			      const char* samplename)
{
        for(std::vector<TString>::const_iterator it = files.begin(); it != files.end(); ++it) 
	{
	  AddDataFile(*it, objname, samplename);
	}
}


PAFSampleCollection* PAFProject::AddSample(PAFSample* sample) {

	if (!fSampleCollection)
	  fSampleCollection = new PAFSampleCollection;

	fSampleCollection->AddSample(sample);

	return fSampleCollection;
}

void PAFProject::SetFirstEvent(Long64_t firstEvent)
{
	fFirstEvent = firstEvent;
}

Long64_t PAFProject::GetFirstEvent() const
{
	return fFirstEvent;
}

void PAFProject::SetNEvents(Long64_t nEvents)
{
	fNEvents = nEvents;
}

Long64_t PAFProject::GetNEvents() const
{
	return fNEvents;
}

bool PAFProject::ExistsTree(TFile* rootFile, const char* treeName)
{
	TObject* result = rootFile->Get(treeName);

	if(result == NULL)
	{
		return kFALSE;
	}
	
	if(result->IsA() == TTree::Class())
	{
		return kTRUE;
	}

	return kFALSE;
}

void PAFProject::GetListOfTrees(TDirectory* directory, TList* resultTrees, const char* path)
{
	THashList* trees = (THashList*)directory->GetListOfKeys();

	TIterator* it = trees->MakeIterator();
	TObject* item = 0;
	while( (item = it->Next()) )
	{
		TObject* obj = directory->Get(item->GetName());
		TString current_item = (directory->IsA() == TFile::Class()) ? 
			TString(item->GetName()) : TString::Format("%s/%s", path, item->GetName());
		
		if(obj->IsA() == TTree::Class())
		{
			resultTrees->Add(new TObjString(current_item.Data()));
		}
		else if (obj->IsA() == TDirectoryFile::Class() ||
				obj->IsA() == TDirectory::Class())
		{
			GetListOfTrees((TDirectory*)obj, resultTrees, current_item.Data());
		}
	}
}

PAFSample* PAFProject::CheckAndCreateSample(const char* samplename) const {
	PAFSample* thesample = fSampleCollection->GetSampleByName(samplename);
	if (!thesample) {
	  PAF_WARN("PAFProject", 
		    TString::Format("PAFSample \"%s\" did not exist. Creating it",samplename));
	  thesample = new PAFSample(samplename);
	  fSampleCollection->AddSample(thesample);
	}
	return thesample;
}






void PAFProject::CheckFileTrees(TDSet* tdset)
{
  	TDSetElement* firstElement = (TDSetElement*)tdset->GetListOfElements()->First();
	if(firstElement == NULL)
	{
	 	PAF_FATAL("PAFProject", "There is no ROOT file specified.");
	}
	
        //If there is a Tree name specified, return.
        // if(tdset->GetObjName())
        // {
        //         PAF_DEBUG("PAFProject", 
	// 		  TString::Format("+ Tree already specified \"%s\"", tdset->GetObjName()));
        //         return;
        // }

	
	//If the first file has a Tree specified, return.
	if(!TString(firstElement->GetObjName()).IsNull())
	{
                PAF_DEBUG("PAFProject", "+ Tree specified in first element");
		return;
	}
	
	TFile file(firstElement->GetFileName());
	
	if(ExistsTree(&file, "Tree"))
	{
		PAF_DEBUG("PAFProject", "Automatic selection of \"Tree\" tree");
		SetDefaultTreeName("Tree");
	}
	else if (ExistsTree(&file, "tree"))
	{
		PAF_DEBUG("PAFProject", "Automatic selection of \"tree\" tree");
		SetDefaultTreeName("tree");
	}
	else
	{
		TList* trees = new TList();
		GetListOfTrees(&file, trees, "");
		
		if(trees->GetEntries() == 0)
		{
			PAF_FATAL("PAFProject", "The ROOT file specified does not have any Tree.");
		}
		else if (trees->GetEntries() == 1)
		{
			const char* treeName = trees->First()->GetName();
			PAF_DEBUG("PAFProject", TString::Format("Using Tree called \"%s\".", treeName).Data());
			SetDefaultTreeName(treeName);
		}
		else
		{
			TString trees_message("There are more than one Tree on ROOT files specified:\n");
			for(int i = 0; i < trees->GetEntries(); i++)
			{
				trees_message.Append("\t-");
				trees_message.Append(trees->At(i)->GetName());
				trees_message.Append("\n");
			}
			PAF_ERROR("PAFProject", trees_message.Data());
			PAF_FATAL("PAFProject", "The ROOT files specified have more than one tree. No tree has a common name, please, specify with PAFProject::SetDefaultTreeName.");
		}
		
		trees->Clear();
		delete trees;
	}
}







void PAFProject::doProjectChecks() {
  PAF_DEBUG("PAFProject", "Checking project for each sample");
  for (unsigned int i = 0; i < fSampleCollection->GetNSamples(); i++) {
    PAF_DEBUG("PAFProject", TString::Format("+ Sample Collection: %s",fSampleCollection->GetSample(i)->GetName()));
    PAF_DEBUG("PAFProject", TString::Format("+ Default Tree Name: %s",fSampleCollection->GetDefaultTreeName(i).Data()));
    CheckFileTrees(fSampleCollection->GetSample(i)->GetDataFiles());
  }
}





void PAFProject::doRun(PAFBaseSelector* selector)
{
        // Create variable containter with the input parameters in the project and in the
        // sample collection
        PAF_DEBUG("PAFProject", "Creating input parameters from PAFProject and PAFSampleCollection");
	PAFVariableContainer* globalinputparams = new PAFVariableContainer();
	globalinputparams->Add(fInputParameters);
	globalinputparams->Add(fSampleCollection->GetParameters());


	unsigned int nSamples = fSampleCollection->GetNSamples();
        PAF_INFO("PAFProject", 
		  TString::Format("Iterating over %d samples", nSamples));
	for (unsigned int i = 0; i < nSamples; i++) {

	  PAFSample* currentsample = fSampleCollection->GetSample(i);
	  PAF_DEBUG("PAFProject", 
		    TString::Format("Processing sample %s", currentsample->GetName()));

	  TDSet* dataFiles = currentsample->GetDataFiles();

	  PAF_DEBUG("PAFProject", 
		    TString::Format("Merging input parameters from sample %s", currentsample->GetName()));
	  PAFVariableContainer* allinputparams = new PAFVariableContainer();
	  allinputparams->Add(globalinputparams);
	  allinputparams->Add(currentsample->GetParameters());
	  //allinputparams->GetKeys()->Dump();

	  PAF_DEBUG("PAFProject", "Setting input parameters in selector");
	  selector->SetSelectorParams(allinputparams);
	  fExecutionEnvironment->AddInput(new PAFNamedItem("PAFParams", allinputparams));

	  PAF_DEBUG("PAFProject", "Setting output file in selector");
	  TString outputfile(fOutputFile);
	  if (nSamples > 1)
	    outputfile = PAFStringUtil::InsertStringInROOTFile(fOutputFile, currentsample->GetName());
	  selector->SetOutputFile(outputfile);
	  PAF_DEBUG("PAFProject", TString::Format("+ Output file: %s", outputfile.Data()));

	  PAF_DEBUG("PAFProject", "... and finally processing the data");
	  fExecutionEnvironment->Process(selector, dataFiles, fFirstEvent, fNEvents);
	}
}


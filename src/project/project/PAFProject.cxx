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
	fDataFiles = new TDSet("PAFFiles", "");
	fFirstEvent = 0;
	fNEvents = -1;
}

PAFProject::~PAFProject()
{
	delete fDataFiles;
}

TString PAFProject::GetDefaultTreeName() const
{
	return TString(fDataFiles->GetObjName());
}

void PAFProject::SetDefaultTreeName(const TString& defaultTreeName)
{
	TDSet* tmp = fDataFiles;
	fDataFiles = new TDSet("PAFFiles", "");

	fDataFiles->SetDirectory(GetDirectoryFromObjName(defaultTreeName));
	fDataFiles->SetObjName(GetNameFromObjName(defaultTreeName));

	TList* oldDataFiles = tmp->GetListOfElements();
	for(Int_t i = 0; i < oldDataFiles->GetEntries(); i++)
	{
		TDSetElement* item = (TDSetElement*)oldDataFiles->At(i);
		const char* dir = TString(item->GetDirectory()).EqualTo("/") ? 0 : item->GetDirectory();
		const char* obj = TString(item->GetObjName()).IsNull() ? 0 : item->GetObjName();
		fDataFiles->Add(item->GetFileName(), obj, dir);
	}
}

void PAFProject::SetDefaultTreeName(const char* defaultTreeName)
{
	TString tDefaultTreeName(defaultTreeName);	
	SetDefaultTreeName(tDefaultTreeName);
}

TDSet* PAFProject::GetDataFiles()
{
	return fDataFiles;
}

void PAFProject::SetDataFiles(TDSet* dataFiles)
{
	fDataFiles = dataFiles;
}

void PAFProject::AddDataFile(const TString& fileName, const char* objname)
{
        TString tObjName(objname);
	TString directory = GetDirectoryFromObjName(tObjName);
	TString name = GetNameFromObjName(tObjName);
	
	fDataFiles->Add(fileName, 
			name.IsNull() ? NULL : name.Data(),
			directory.IsNull() ? NULL : directory.Data());
}

void PAFProject::AddDataFile(const char* fileName, const char* objname)
{
	AddDataFile(TString(fileName), objname);
}

void PAFProject::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

void PAFProject::AddDataFiles(const std::vector<TString>& files, const char* objname)
{
        for(std::vector<TString>::const_iterator it = files.begin(); it != files.end(); ++it) 
	{
	        AddDataFile(*it, objname);
	}
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

void PAFProject::doProjectChecks()
{
	TDSetElement* firstElement = (TDSetElement*)GetDataFiles()->GetListOfElements()->First();
	if(firstElement == NULL)
	{
		PAF_FATAL("PAFProject", "There is no ROOT file specified.");
	}
	
	//If there is a Tree name specified, return.
	if(!GetDefaultTreeName().IsNull())
	{
		return;
	}
	
	//If the first file has a Tree specified, return.
	if(!TString(firstElement->GetObjName()).IsNull())
	{
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

void PAFProject::doRun(PAFBaseSelector* selector)
{
	fExecutionEnvironment->Process(selector, fDataFiles, fFirstEvent, fNEvents);
}

TString PAFProject::GetDirectoryFromObjName(const TString& objName)
{
	TString tObjName = objName;
	std::vector<TString*>* parts = PAFStringUtil::Split(&tObjName, "/");
	
	TString result;
	
	if(parts->size() > 0)
	{
		for(unsigned int i = 0; i < parts->size() - 1; i++)
		{
			result.Append(parts->at(i)->Data());
		}
	}
	
	parts->clear();
	delete parts;
	
	return result;
}

TString PAFProject::GetNameFromObjName(const TString& objName)
{
	TString tObjName = objName;
	std::vector<TString*>* parts = PAFStringUtil::Split(&tObjName, "/");
	
	TString result;
	
	if(parts->size() > 0)
	{
		result = (parts->at(parts->size() - 1))->Copy();
	}
	
	parts->clear();
	delete parts;
	
	return result;
}

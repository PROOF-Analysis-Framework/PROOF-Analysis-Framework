/**
	@brief Class to create a PAFProject which should be configured (although it has default values) and launched to get results. 
	@file PAFProject.cxx
	@class PAFProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFProject.h"

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
}

PAFProject::~PAFProject()
{
	delete fDataFiles;
}

TString PAFProject::GetDefaultTreeName()
{
	return TString(fDataFiles->GetObjName());
}

void PAFProject::SetDefaultTreeName(TString& defualtTreeName)
{
	SetDefaultTreeName(defualtTreeName.Data());
}

void PAFProject::SetDefaultTreeName(const char* defaultTreeName)
{
	fDataFiles->SetObjName(defaultTreeName);
}

TDSet* PAFProject::GetDataFiles()
{
	return fDataFiles;
}

void PAFProject::SetDataFiles(TDSet* dataFiles)
{
	fDataFiles = dataFiles;
}

void PAFProject::AddDataFile(TString& fileName, const char* objname)
{
	AddDataFile(fileName.Data(), objname);
}

void PAFProject::AddDataFile(const char* fileName, const char* objname)
{
	fDataFiles->Add(fileName, objname);
}

void PAFProject::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

bool PAFProject::ExistsTree(TFile* rootFile, const char* treeName)
{
	TObject* result = rootFile->Get(treeName);

	if(result->IsA() == TTree::Class())
	{
		return kTRUE;
	}

	return kFALSE;
}

TList* PAFProject::GetListOfTrees(TFile* rootFile)
{
	TList* result = new TList();

	THashList* trees = (THashList*)rootFile->GetListOfKeys();

	TIterator* it = trees->MakeIterator();
	TObject* item = 0;
	while( (item = it->Next()) )
	{
		result->Add(item);
	}

	return result;
}

void PAFProject::doProjectChecks()
{
	//If there is a Tree name specified, return.
	if(!GetDefaultTreeName().IsNull())
	{
		return;
	}
	
	TDSetElement* firstElement = (TDSetElement*)GetDataFiles()->GetListOfElements()->First();
	if(firstElement == NULL)
	{
		PAF_FATAL("Project", "There is no ROOT file specified.");
	}
	
	//If the first file has a Tree specified, return.
	if(!TString(firstElement->GetObjName()).IsNull())
	{
		return;
	}
	
	TFile file(firstElement->GetFileName());
	
	if(ExistsTree(&file, "Tree"))
	{
		PAF_DEBUG("Project", "Automatic selection of \"Tree\" tree");
		SetDefaultTreeName("Tree");
	}
	else if (ExistsTree(&file, "tree"))
	{
		PAF_DEBUG("Project", "Automatic selection of \"tree\" tree");
		SetDefaultTreeName("tree");
	}
	else
	{
		TList* trees = GetListOfTrees(&file);
		int ntrees = trees->GetEntries();
		
		if(ntrees == 0)
		{
			PAF_FATAL("Project", "The ROOT file specified does not have any Tree.");
		}
		else if (ntrees == 1)
		{
			SetDefaultTreeName(trees->First()->GetName());
		}
		else
		{
			TString trees_message("There are more than one Tree on ROOT files specified:\n");
			for(int i = 0; i < ntrees; i++)
			{
				trees_message.Append("\t-");
				trees_message.Append(trees->At(i)->GetName());
				trees_message.Append("\n");
			}
			PAF_ERROR("Project", trees_message.Data());
			PAF_FATAL("Project", "The ROOT files specified have more than one tree. No tree has a common name, please, specify with PAFProject::SetDefaultTreeName.");
		}
		
		delete trees;
	}
}

void PAFProject::doRun(PAFBaseSelector* selector)
{
	fExecutionEnvironment->Process(selector, fDataFiles);
}

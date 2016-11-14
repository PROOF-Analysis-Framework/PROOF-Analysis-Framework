/**
	@brief Class to store a data sample with the parameters associated to it. 
	@file PAFSample.cxx
	@class PAFSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2016-11-09
 */

#include "PAFSample.h"

#include "PAF.h"
#include "PAFStringUtil.h"

ClassImp(PAFSample);

PAFSample::PAFSample(const char* name):
  TNamed(name,name),
  fParameters(0) {
  fDataFiles = new TDSet(name, "");
}



PAFSample::~PAFSample() {
  delete fDataFiles;
  delete fParameters;
}



void PAFSample::AddDataFile(const TString& fileName, const char* objname)
{
        TString tObjName(objname);
	TString directory = PAFStringUtil::GetDirectoryFromObjName(tObjName);
	TString name = PAFStringUtil::GetNameFromObjName(tObjName);
	fDataFiles->Add(fileName, 
			name.IsNull() ? NULL : name.Data(),
			directory.IsNull() ? NULL : directory.Data());
}

void PAFSample::AddDataFile(TFileInfo* dataFile)
{
	fDataFiles->Add(dataFile);
}

void PAFSample::AddDataFiles(const std::vector<TString>& files, const char* objname)
{
        for(std::vector<TString>::const_iterator it = files.begin(); it != files.end(); ++it) 
	{
	        AddDataFile(*it, objname);
	}
}


void PAFSample::SetDefaultTreeName(const TString& defaultTreeName)
{
	TDSet* tmp = fDataFiles;
	fDataFiles = new TDSet("PAFFiles", "");

	fDataFiles->SetDirectory(PAFStringUtil::GetDirectoryFromObjName(defaultTreeName));
	fDataFiles->SetObjName(PAFStringUtil::GetNameFromObjName(defaultTreeName));

	TList* oldDataFiles = tmp->GetListOfElements();
	for(Int_t i = 0; i < oldDataFiles->GetEntries(); i++)
	{
		TDSetElement* item = (TDSetElement*)oldDataFiles->At(i);
		const char* dir = TString(item->GetDirectory()).EqualTo("/") ? 0 : item->GetDirectory();
		const char* obj = TString(item->GetObjName()).IsNull() ? 0 : item->GetObjName();
		fDataFiles->Add(item->GetFileName(), obj, dir);
	}
}




/**
	@brief Utility class to deal with strings.
	@file PAFStringUtil.cxx
	@class PAFStringUtil
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-12
 */


// PAF includes
#include "PAF.h"
#include "PAFStringUtil.h"

// ROOT includes
#include "TSystemFile.h"

std::vector< TString* >* PAFStringUtil::Split(TString* string, const char* cs)
{
	std::vector<TString*>* result = new std::vector<TString*>();

	while(string->Length() > 0)
	{
		int indexnext = string->First(cs);
		indexnext = indexnext >= 0 ? indexnext : string->Length();
		TString* dir = new TString(string->Data(), indexnext);
		if(!dir->IsNull())
		{
			result->push_back(dir);
		}
		string->Remove(0, indexnext + 1);
	}

	return result;
}


TString PAFStringUtil::GetDirectoryFromObjName(const TString& objName)
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


TString PAFStringUtil::GetNameFromObjName(const TString& objName)
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



TString PAFStringUtil::InsertStringInROOTFile(const TString& file, const TString& sampleName) {

  TString finalname = file;

  // Let's do the official case first
  if (file.Contains("%PAFSAMPLENAME%")) {
    finalname.ReplaceAll("%PAFSAMPLENAME%",sampleName);
  }


  // If the pattern is not there, then deal with different cases
  else {
    TString prefix("");
    TString suffix(".root");

    // + If the file name is empty then we will have sampleName.root as output file
    if (file.IsNull()) {
      PAF_INFO("PAFStringUtil", "Output file name is empty. Using sample name in current directory for the output file.");
    }
    // + Otherwise try to add the sampleName before .root
    else {
      // - If it is a directoy store sampleName.root there
      TSystemFile f;
      if (f.IsDirectory(sampleName)) {
	  prefix = sampleName;
	  if (sampleName[sampleName.Sizeof()-2] != '/')
	    prefix += '/';
      }
      else {
	Ssiz_t pos = file.Last('.');
	// - If the name is ill-formed (not even a dot), add it to the end
	if (pos < 0) {
	  PAF_WARN("PAFStringUtil", "Output file has no root suffix. It will be added");
	  prefix = file + "_";
	}
	// - Otherwise look for .root
	else {
	  TString suffix = file.SubString("root", pos);
	  // * If we don't find .root, then it will be added
	  if (suffix.IsNull()) {
	    PAF_WARN("PAFStringUtil", "Output file has no root suffix. It will be added");
	    prefix=file;
	  }
	  // * Otherwise the name before .root will be used as a base for the name
	  else {
	    prefix = file(0,pos);
	  }
	}
      }
    }
    finalname = prefix + "_" + sampleName + suffix;
  }

  return finalname; 

}

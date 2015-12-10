//
// Created by noe on 4/12/15.
//


#pragma once

#include "TString.h"
#include "TFileInfo.h"
#include "TDSet.h"
#include "Rtypes.h"



class PAFAbstractSample{

public :

    PAFAbstractSample();
    void AddDataFile(const char *fileName, const char* objname);
    void AddDataFile(TString& fileName, TString& objName);
    void AddDataFile(TFileInfo* dataFile);

    void SetSampleName(TString sampleName);
    TString GetSampleName();

    TString GetDirectoryFromObjName(TString& objName);
    TString GetNameFromObjName(TString& objName);


    virtual void Check() = 0;
    virtual ~PAFAbstractSample();

protected:
    TString sampleName;
    TDSet* sample;

ClassDef(PAFAbstractSample,1);

};

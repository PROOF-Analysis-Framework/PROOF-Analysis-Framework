//
// Created by noe on 4/12/15.
//


#pragma once

#include "TString.h"
#include "TFileInfo.h"
#include "TDSet.h"
#include "Rtypes.h"
#include "PAFIExecutionEnvironment.h"
#include "PAFBaseSelector.h"


class PAFAbstractSample {

public :

    PAFAbstractSample();

    void AddDataFile(const char *fileName, const char *objname);

    void AddDataFile(TString &fileName, TString &objName);

    void AddDataFile(TFileInfo *dataFile);

    void SetSampleName(TString sampleName);

    TString GetSampleName();

    TString GetDirectoryFromObjName(TString &objName);

    TString GetNameFromObjName(TString &objName);

    virtual void doRun(PAFIExecutionEnvironment *executionEnvironment, PAFBaseSelector *selector) = 0;


    virtual void Check() = 0;

    virtual ~PAFAbstractSample();

protected:
    TString sampleName;
    TDSet *sample;
    Long64_t fFirstEvent;
    Long64_t fNEvents;

ClassDef(PAFAbstractSample, 1);

};

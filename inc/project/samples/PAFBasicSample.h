/**
	@brief ...
	@file PAFBasicSample.h
	@class PAFBasicSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez, N. Fernández  Álvarez
	@version 1.0
	@date 2015-12-08
 */


#pragma once

#include "PAFAbstractSample.h"
#include "TList.h"
#include "TDirectory.h"
#include "TFile.h"
#include "Rtypes.h"

class PAFBasicSample : public PAFAbstractSample {

public:

    PAFBasicSample();

    void Check();

    void doRun(PAFIExecutionEnvironment *executionEnvironment, PAFBaseSelector *selector);

    virtual ~PAFBasicSample();


protected:
    TString GetDefaultTreeName();

    bool ExistsTree(TFile *rootFile, const char *treeName);

    void SetDefaultTreeName(const char *defaultTreeName);

    void GetListOfTrees(TDirectory *directory, TList *resultTrees, const char *path);

    ClassDef(PAFBasicSample,1);

};

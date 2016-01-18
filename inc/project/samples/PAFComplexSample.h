//
// Created by root on 13/12/15.
//

#pragma once

#include "PAFAbstractSample.h"
#include "TList.h"
#include "TDirectory.h"
#include "TFile.h"
#include "Rtypes.h"
#include <vector>

class PAFComplexSample : public PAFAbstractSample {

public:

    PAFComplexSample();

    void Check();

    void doRun(PAFIExecutionEnvironment *executionEnvironment, PAFBaseSelector *selector);

    virtual ~PAFComplexSample();

    void AddSample(PAFAbstractSample* sample);
    std::vector<PAFAbstractSample*>*    GetSamples();

protected:
    std::vector<PAFAbstractSample *> *samples;


ClassDef(PAFComplexSample, 1);

};
//
// Created by root on 13/12/15.
//


#include "PAFComplexSample.h"

ClassImp(PAFComplexSample);


PAFComplexSample::PAFComplexSample() {
    this->samples = new std::vector<PAFAbstractSample *>();
}

void PAFComplexSample::Check() {
    for (unsigned int i = 0; i < this->samples->size(); i++) {
        this->samples->at(i)->Check();
    }
}

void PAFComplexSample::doRun(PAFIExecutionEnvironment *executionEnvironment, PAFBaseSelector *selector) {
    for (unsigned int i = 0; i < this->samples->size(); i++) {
        this->samples->at(i)->doRun(executionEnvironment, selector);
    }
}


PAFComplexSample::~PAFComplexSample() {
    delete this->samples;

}

void PAFComplexSample::AddSample(PAFAbstractSample *sample) {
    this->samples->push_back(sample);
}

std::vector<PAFAbstractSample *> *PAFComplexSample::GetSamples() {
    return this->samples;
}
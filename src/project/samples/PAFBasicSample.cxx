//
// Created by root on 4/12/15.
//

#include "PAFBasicSample.h"

ClassImp(PAFBasicSample);

PAFBasicSample::PAFBasicSample() {
    this->sample = new TDSet("PAFFiles", "");
    this->samples = new std::vector<PAFAbstractSample *>();
    this->fFirstEvent = 0;
    this->fNEvents = -1;
    this->sampleOutputNameFormat = new TString("%s");    // if no formate is provided, the default output name will be the name of the sample

}

PAFBasicSample::PAFBasicSample(TDSet *fDataFiles) {
    this->sample = fDataFiles;
    this->samples = new std::vector<PAFAbstractSample *>();
    this->fFirstEvent = 0;
    this->fNEvents = -1;
    this->sampleOutputNameFormat = new TString("%s");

}


PAFBasicSample::~PAFBasicSample() {
    delete this->sample;
    delete this->samples;
}

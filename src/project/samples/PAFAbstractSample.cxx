//
// Created by noe on 4/12/15.
//

#include <PAFStringUtil.h>
#include "PAFAbstractSample.h"

ClassImp(PAFAbstractSample);


PAFAbstractSample::PAFAbstractSample() {

}

PAFAbstractSample::~PAFAbstractSample() {

}

void PAFAbstractSample::Add(PAFAbstractSample *sample) {
    this->samples->push_back(sample);
}

void PAFAbstractSample::Add(const char *fileName) {
    AddDataFile(fileName, "Tree");
}


void PAFAbstractSample::SetSampleName(TString sampleName) {

    this->sampleName = sampleName;
}


TString PAFAbstractSample::GetSampleName() {
    return this->sampleName;
}

void PAFAbstractSample::AddDataFile(TString &fileName, TString &objname) {
    TString directory = GetDirectoryFromObjName(objname);
    TString name = GetNameFromObjName(objname);

    sample->Add(fileName,
                name.IsNull() ? NULL : name.Data(),
                directory.IsNull() ? NULL : directory.Data());
}

void PAFAbstractSample::AddDataFile(const char *fileName, const char *objname) {
    TString tFileName(fileName);
    TString tObjName(objname);
    AddDataFile(tFileName, tObjName);
}

void PAFAbstractSample::AddDataFile(TFileInfo *dataFile) {
    sample->Add(dataFile);
}

TString PAFAbstractSample::GetDirectoryFromObjName(TString &objName) {
    TString tObjName = objName;
    std::vector<TString *> *parts = PAFStringUtil::Split(&tObjName, "/");

    TString result;

    if (parts->size() > 0) {
        for (unsigned int i = 0; i < parts->size() - 1; i++) {
            result.Append(parts->at(i)->Data());
        }
    }

    parts->clear();
    delete parts;

    return result;
}

TString PAFAbstractSample::GetNameFromObjName(TString &objName) {
    TString tObjName = objName;
    std::vector<TString *> *parts = PAFStringUtil::Split(&tObjName, "/");

    TString result;

    if (parts->size() > 0) {
        result = (parts->at(parts->size() - 1))->Copy();
    }

    parts->clear();
    delete parts;

    return result;
}

TDSet *PAFAbstractSample::GetDataFiles() {
    TDSet *files = new TDSet("PAFFiles", "");
    files->Add(this->sample);

    for (unsigned long i = 0; i < this->samples->size(); i++) {
        files->Add(this->samples->at(i)->GetDataFiles());
    }

    return files;
}

void PAFAbstractSample::SetOutputNameFormat(const char *format) {
    this->sampleOutputNameFormat = new TString(format);
}


TString PAFAbstractSample::GetFormattedName() {
    return TString::Format(this->sampleOutputNameFormat->Data(), this->GetSampleName().Data());
}


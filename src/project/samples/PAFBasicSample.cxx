//
// Created by root on 4/12/15.
//

#include "PAFBasicSample.h"
#include "PAF.h"
#include "TFile.h"
#include "TTree.h"
#include "THashList.h"

ClassImp(PAFBasicSample);

PAFBasicSample::PAFBasicSample() {
    this->sample = new TDSet("PAFFiles", "");
    this->fFirstEvent = 0;
    this->fNEvents = -1;

}


PAFBasicSample::~PAFBasicSample() {
    delete this->sample;
}

void PAFBasicSample::Check() {
    PAF_INFO("SAMPLE", "CHECKING SAMPLE");
    TDSetElement *firstElement = (TDSetElement *) this->sample->GetListOfElements()->First();

    if (firstElement == NULL) {
        PAF_FATAL("Project", "There is no ROOT file specified.");
    }

    /**
     * If there is a tree name specified, breaks the function
     */

    //If there is a Tree name specified, return.
    if (!GetDefaultTreeName().IsNull()) {
        PAF_INFO("SAMPLE", "TREE NAME HAS BEEN SPECIFIED");
        return;
    }

    //If the first file has a Tree specified, return.
    if (!TString(firstElement->GetObjName()).IsNull()) {
        PAF_INFO("SAMPLE", "TREE NAME HAS BEEN SPECIFIED");
        return;
    }

    TFile file(firstElement->GetFileName());

    if (ExistsTree(&file, "Tree")) {
        PAF_DEBUG("Project", "Automatic selection of \"Tree\" tree");
        SetDefaultTreeName("Tree");
    }
    else if (ExistsTree(&file, "tree")) {
        PAF_DEBUG("Project", "Automatic selection of \"tree\" tree");
        SetDefaultTreeName("tree");
    }
    else {
        TList *trees = new TList();
        GetListOfTrees(&file, trees, "");

        if (trees->GetEntries() == 0) {
            PAF_FATAL("SAMPLE", "The ROOT file specified does not have any Tree.");
        }
        else if (trees->GetEntries() == 1) {
            const char *treeName = trees->First()->GetName();
            PAF_DEBUG("SAMPLE", TString::Format("Using Tree called \"%s\".", treeName).Data());
            SetDefaultTreeName(treeName);
        }
        else {
            TString trees_message("There are more than one Tree on ROOT files specified:\n");
            for (int i = 0; i < trees->GetEntries(); i++) {
                trees_message.Append("\t-");
                trees_message.Append(trees->At(i)->GetName());
                trees_message.Append("\n");
            }
            PAF_ERROR("sample", trees_message.Data());
            PAF_FATAL("SAMPLE",
                      "The ROOT files specified have more than one tree. No tree has a common name, please, specify with PAFProject::SetDefaultTreeName.");
        }

        trees->Clear();
        delete trees;
    }

    PAF_INFO("SAMPLE", "SAMPLE CHECKING HAS TERMINTED SUCCESFULY");
}

TString PAFBasicSample::GetDefaultTreeName() {
    return TString{this->sample->GetObjName()};
}

bool PAFBasicSample::ExistsTree(TFile *rootFile, const char *treeName) {

    TObject *result = rootFile->Get(treeName);

    if (result == NULL) {
        return kFALSE;
    }

    if (result->IsA() == TTree::Class()) {
        return kTRUE;
    }

    return kFALSE;

}

void PAFBasicSample::SetDefaultTreeName(const char *defaultTreeName) {

    TString tDefaultTreeName(defaultTreeName);
    SetDefaultTreeName(tDefaultTreeName);

}

void PAFBasicSample::GetListOfTrees(TDirectory *directory, TList *resultTrees, const char *path) {

    THashList *trees = (THashList *) directory->GetListOfKeys();

    TIterator *it = trees->MakeIterator();
    TObject *item = 0;
    while ((item = it->Next())) {
        TObject *obj = directory->Get(item->GetName());
        TString current_item = (directory->IsA() == TFile::Class()) ?
                               TString(item->GetName()) : TString::Format("%s/%s", path, item->GetName());

        if (obj->IsA() == TTree::Class()) {
            resultTrees->Add(new TObjString(current_item.Data()));
        }
        else if (obj->IsA() == TDirectoryFile::Class() ||
                 obj->IsA() == TDirectory::Class()) {
            GetListOfTrees((TDirectory *) obj, resultTrees, current_item.Data());
        }
    }

}

void PAFBasicSample::doRun(PAFIExecutionEnvironment *executionEnvironment, PAFBaseSelector *selector) {
    std::cout << "Executing the sample " << this->sampleName << std::endl;
    executionEnvironment->Process(selector, this->sample, fFirstEvent, fNEvents);
    std::cout << "Execution finished" << std::endl;
}


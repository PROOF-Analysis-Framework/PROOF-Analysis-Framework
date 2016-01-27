/**
	@brief Abstract class with common funcionality of different PAFIProjects.
	@file PAFAbstractProject.h
	@class PAFAbstractProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-18
 */

#pragma once

#include <vector>

#include "TString.h"

#include "PAFISettings.h"
#include "PAFIExecutionEnvironment.h"
#include "PAFPackage.h"
#include "PAFPackageSelector.h"
#include "PAFLibrary.h"
#include "PAFISelector.h"
#include "PAFChainSelector.h"
#include "PAFChainItemSelector.h"
#include "PAFBaseSelector.h"
#include "PAFVariableContainer.h"
#include "PAFIProgressUpdated.h"
#include "PAFAbstractSample.h"

class PAFAbstractProject {
public:
    PAFAbstractProject();

    PAFAbstractProject(PAFIExecutionEnvironment *executionEnvironment);

    virtual ~PAFAbstractProject();

    void SetExecutionEnvironment(PAFIExecutionEnvironment *executionEnvironment);

    PAFIExecutionEnvironment *GetExecutionEnvironment();

    void SetPackages(std::vector<PAFPackage *> *packages);

    std::vector<PAFPackage *> *GetPackages();

    void AddPackage(const TString &packageName);

    void AddPackage(const char *packageName);

    void AddPackage(PAFPackage *package);

    void SetSelectorPackages(std::vector<PAFPackageSelector *> *selectorPackages);

    std::vector<PAFPackageSelector *> *GetSelectorPackages();

    void AddSelectorPackage(const TString &packageSelectorName);

    void AddSelectorPackage(const char *packageSelectorName);

    void AddSelectorPackage(PAFPackageSelector *packageSelector);

    void SetLibraries(std::vector<PAFLibrary *> *libraries);

    std::vector<PAFLibrary *> *GetLibraries();

    void AddLibrary(const TString &libraryName);

    void AddLibrary(const char *libraryName);

    void AddLibrary(PAFLibrary *library);

    void SetPAFSettings(PAFISettings *settings);

    PAFISettings *GetPAFSettings();

    void SetOutputFile(const TString &fileName);

    void SetOutputFile(const char *fileName);

    TString GetOutputFile() const;

    void SetInputParameters(PAFVariableContainer *inputParameters);

    PAFVariableContainer *GetInputParameters();

    template<typename T>
    void SetInputParam(const TString &key, T param);

    template<typename T>
    void SetInputParam(const char *key, T param);

    void SetDynamicHistograms(std::vector<TString> *dynamicHistograms);

    std::vector<TString> *GetDynamicHistograms();

    void AddDynamicHistogram(const TString &histogram);

    void AddDynamicHistogram(const char *histogram);

    void SetCompileOnSlaves(bool compileOnSlaves);

    bool GetCompileOnSlaves() const;

    void SetProgressUpdated(PAFIProgressUpdated *progressUpdated);

    PAFIProgressUpdated *GetProgressUpdatedFunction();

    void AddSample(PAFAbstractSample *sample);

    TList *Run();

    virtual void doProjectChecks() = 0;

    virtual void doRun(PAFBaseSelector *selector) = 0;

protected:
    void InitMembers();

    template<typename T>
    T CreateObject(const char *className);

    void PreparePackage(PAFPackage *package);

    void PreparePackages();

    void LoadProjectItems();

    void PreparePAFSelector();

    void AddDynamicHistograms();

protected:
    PAFIExecutionEnvironment *fExecutionEnvironment;
    PAFVariableContainer *fInputParameters;
    PAFISelector *fPAFSelector;
    std::vector<PAFPackage *> *fPackages; //!
    std::vector<PAFPackageSelector *> *fSelectorPackages; //!
    std::vector<PAFLibrary *> *fLibraries; //!
    TString fOutputFile;
    std::vector<TString> *fDynamicHistograms;
    PAFISettings *fPAFSettings;
    bool fCompileOnSlaves;
    PAFIProgressUpdated *fProgressUpdated;
    std::vector<PAFAbstractSample *> *fSamples;

ClassDef(PAFAbstractProject, 1);
};

template<typename T>
inline void PAFAbstractProject::SetInputParam(const TString &key, T param) {
    SetInputParam(key.Data(), param);
}

template<typename T>
inline void PAFAbstractProject::SetInputParam(const char *key, T param) {
    fInputParameters->Add(key, param);
}

template<>
inline void PAFAbstractProject::SetInputParam(const TString &key, const char *param) {
    TString tparam(param);
    SetInputParam(key.Data(), tparam);
}

template<>
inline void PAFAbstractProject::SetInputParam(const char *key, const char *param) {
    TString tparam(param);
    SetInputParam(key, tparam);
}

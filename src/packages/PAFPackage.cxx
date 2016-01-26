/**
	@brief Generic PAFPackage which will contain items to load in environments.
	@file PAFPackage.cxx
	@class PAFPackage
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
 */

#include <sys/stat.h>
#include "TFile.h"
#include "PAFPackage.h"

#include "TSystem.h"

#include "PAF.h"

#include <iostream>
#include <fstream>

ClassImp(PAFPackage);

PAFPackage::PAFPackage()
        : fPAFSettings(0), fName() {

}

PAFPackage::PAFPackage(PAFISettings *pafsettings, const char *name)
        : fPAFSettings(pafsettings), fName(name) {

}

PAFPackage::~PAFPackage() {

}

void PAFPackage::PreparePackage() const {
    if (!isCompiled()) {
        TString packages_dir = GetPackagesDir();
        gSystem->MakeDirectory(packages_dir);

        TString build_command = GetPreparePackageCommand();
        TString response_build_command = gSystem->GetFromPipe(build_command);
        PAF_DEBUG("PAFPackage", response_build_command);
    }
}

TString PAFPackage::GetPreparePackageCommand() const {
    TString package_dir = GetPackageDir();
    if (package_dir == "") {
        PAF_FATAL("PAFPackage", TString::Format("Package \"%s\" not found in repositories.", fName.Data()).Data());
    }
    return TString::Format("%s/bin/PreparePackage.sh -s -d %s -r %s %s", fPAFSettings->GetPAFPATH()->Data(),
                           GetPackagesDir().Data(), package_dir.Data(), GetName());
}

void PAFPackage::CreateParFile() const {
    TString creteparfile_command = TString::Format("%s/bin/MakeParFile.sh -s -d %s %s",
                                                   fPAFSettings->GetPAFPATH()->Data(), GetPackagesDir().Data(),
                                                   GetName());
    TString response_createparfile_command = gSystem->GetFromPipe(creteparfile_command);
    PAF_DEBUG("PAFPackage", response_createparfile_command);
}

void PAFPackage::CompileAsLibrary() const {
    if (!isCompiled()) {
        TString compileaslibrary_command = TString::Format("%s/bin/CompileLibrary.sh -s -d %s %s",
                                                           fPAFSettings->GetPAFPATH()->Data(), GetPackagesDir().Data(),
                                                           GetName());
        PAF_INFO("compiling", compileaslibrary_command.Data());
        TString response_compileaslibrary_command = gSystem->GetFromPipe(compileaslibrary_command);
        if (response_compileaslibrary_command.Index("Successful compilation") ==
            response_compileaslibrary_command.Length() - 22) {
            PAF_DEBUG("PAFPackage", TString::Format("%s compiled.", fName.Data()).Data());
        }
        else {
            PAF_ERROR("PAFPackage", response_compileaslibrary_command);
            PAF_FATAL("PAFPackage", TString::Format("Compilation of %s failed.", fName.Data()).Data());
        }
    } else {
        PAF_INFO("PAFPackage", "Package already compiled");
    }
}

const char *PAFPackage::GetName() const {
    return fName.Data();
}

void PAFPackage::SetName(const char *name) {
    fName = name;
}

PAFISettings *PAFPackage::GetSettings() {
    return fPAFSettings;
}

void PAFPackage::SetSettings(PAFISettings *pafsettings) {
    fPAFSettings = pafsettings;
}

TString PAFPackage::GetLibraryFileName() const {
    return TString::Format("%s%s/lib%s.so", GetPackagesDir().Data(), GetName(), GetName());
}

TString PAFPackage::GetParFileName() const {
    return TString::Format("%s%s.par", GetPackagesDir().Data(), GetName());
}

TString PAFPackage::GetPackageDir() const {
    std::vector<TString *> *package_directories = fPAFSettings->GetPackagesDirectories();

    for (unsigned int i = 0; i < package_directories->size(); i++) {
        TString package_filename = TString::Format("%s/%s", package_directories->at(i)->Data(), fName.Data());
        if (gSystem->OpenDirectory(package_filename)) {
            return *(package_directories->at(i));
        }
    }
    return TString("");
}

TString PAFPackage::GetPackagesDir() const {
    return TString::Format("%s/packages/", gSystem->GetBuildDir());
}

bool PAFPackage::isCompiled() const {

    /**
     *TODO: CAmbiar por GetPathInfo en TSYSTEM
     *
     */
    TString libPath = TString::Format("%s%s/lib%s.so", GetPackagesDir().Data(), GetName(), GetName());
    ifstream file(libPath.Data(), std::ios::binary | std::ios::ate);

    return file.tellg() != -1;
}


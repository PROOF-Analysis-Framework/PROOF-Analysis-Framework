/**
	@brief Generic PAFPackage which will contain items to load in environments.
	@file PAFPackage.h
	@class PAFPackage
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "TObject.h"

#include "TString.h"
#include "../settings/PAFISettings.h"

class PAFPackage : public TObject {
	public:
		PAFPackage() : fName() {}
		PAFPackage(PAFISettings* pafsettings, const char* name) : fPAFSettings(pafsettings), fName(name) {}
		virtual ~PAFPackage() {}

		void PreparePackage();
		void CreateParFile();
		void CompileAsLibrary();

		TString GetName() { return fName; }
		void SetName(const char* name) { fName = TString(name); }
		
		TString GetLibraryFileName();
		TString GetParFileName();
		
		void SetSettings(PAFISettings* pafsettings) { fPAFSettings = pafsettings; }
		PAFISettings* GetSettings() { return fPAFSettings; }
		
	protected:
		virtual TString GetPreparePackageCommand();
		
		TString GetPackagesDir();
		TString GetBuildDir();
		
	protected:
		PAFISettings* fPAFSettings;
		TString fName;
		
	ClassDef(PAFPackage, 1);
};


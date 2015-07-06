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
                PAFPackage() : fPAFSettings(0), fName() {}
		PAFPackage(PAFISettings* pafsettings, const char* name) : fPAFSettings(pafsettings), fName(name) {}
		virtual ~PAFPackage() {}

		void PreparePackage() const;
		void CreateParFile() const;
		void CompileAsLibrary() const;

		virtual const char* GetName() const { return fName.Data(); }
		void SetName(const char* name) { fName = name; }
		
		TString GetLibraryFileName() const;
		TString GetParFileName() const;
		
		void SetSettings(PAFISettings* pafsettings) { fPAFSettings = pafsettings; }
		PAFISettings* GetSettings() { return fPAFSettings; }
		
	protected:
		virtual TString GetPreparePackageCommand() const;
		
		TString GetPackageDir() const;
		TString GetPackagesDir() const;
		
	protected:
		PAFISettings* fPAFSettings;
		TString fName;
		
	ClassDef(PAFPackage, 1);
};


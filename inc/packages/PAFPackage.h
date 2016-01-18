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
#include "PAFISettings.h"

class PAFPackage : public TObject 
{
	public:
		PAFPackage();
		PAFPackage(PAFISettings* pafsettings, const char* name);
		virtual ~PAFPackage();

		void PreparePackage() const;
		void CreateParFile() const;
		void CompileAsLibrary() const;

		bool isCompiled() const;

		void SetName(const char* name);
		virtual const char* GetName() const;

		TString GetLibraryFileName() const;
		TString GetParFileName() const;

		void SetSettings(PAFISettings* pafsettings);
		PAFISettings* GetSettings();

	protected:
		virtual TString GetPreparePackageCommand() const;

		TString GetPackageDir() const;
		TString GetPackagesDir() const;

	protected:
		PAFISettings* 	fPAFSettings;
		TString 	fName;

	ClassDef(PAFPackage, 1);
};

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

class PAFPackage : public TObject {
	public:
		PAFPackage() : fName() {}
		PAFPackage(const char* name) : fName(name) {}
		virtual ~PAFPackage() {}

		void PreparePackage();
		void CreateParFile();
		void CompileAsLibrary();

		TString GetName() { return fName; }
		
		TString GetLibraryFileName();
		TString GetParFileName();
		
	protected:
		virtual TString GetPreparePackageCommand();
		TString fName;
		
		TString GetPackagesDir();
		TString GetBuildDir();
		
		
	ClassDef(PAFPackage, 1);
};


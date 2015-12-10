/**
	@brief PAFLibrary which will contain libraries to load in environments.
	@file PAFLibrary.h
	@class PAFLibrary
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-17
 */

#pragma once

#include "TObject.h"

#include "TString.h"

#include "PAFISettings.h"

class PAFLibrary : public TObject 
{
	public:
                PAFLibrary(PAFISettings* pafsettings = 0, const char* fileName = 0);
		virtual ~PAFLibrary();

		TString GetFileName() const;
		TString GetLibraryName() const;

		void CreatePARFile() const;
		TString GetPARFileName() const;

		void SetSettings(PAFISettings* pafsettings);
		PAFISettings* GetSettings();

	private:
		PAFISettings* 	fPAFSettings;
		TString 	fFileName;

	ClassDef(PAFLibrary, 1);
};

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

#include "../settings/PAFISettings.h"

class PAFLibrary : public TObject {
	public:
		PAFLibrary();
		PAFLibrary(PAFISettings* pafsettings, const char* fileName);
		virtual ~PAFLibrary() {}
	
		TString GetFileName();
		TString GetLibraryName();
		
		void CreatePARFile();
		TString GetPARFileName();
		
		void SetSettings(PAFISettings* pafsettings);
		PAFISettings* GetSettings();
	private:
		PAFISettings* 	fPAFSettings;
		TString 	fFileName;

	ClassDef(PAFLibrary, 1);
};


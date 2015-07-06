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
                PAFLibrary(PAFISettings* pafsettings = 0, const char* fileName = 0):
                  fPAFSettings(pafsettings), fFileName(fileName) {}
		virtual ~PAFLibrary() {}
	
		TString GetFileName() const {return fFileName;}
		TString GetLibraryName() const;
		
		void CreatePARFile() const;
		TString GetPARFileName() const;
		
		void SetSettings(PAFISettings* pafsettings) {fPAFSettings = pafsettings;}
		PAFISettings* GetSettings() {return fPAFSettings;}
	private:
		PAFISettings* 	fPAFSettings;
		TString 	fFileName;

	ClassDef(PAFLibrary, 1);
};


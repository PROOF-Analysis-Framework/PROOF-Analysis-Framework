/**
	@brief PAFEnvironmentVariableSettings class which gets the EnvironmentVariables.
	@file PAFEnvironmentVariableSettings.h
	@class PAFEnvironmentVariableSettings
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-07
*/

#pragma once

#include "PAFISettings.h"

#include "TString.h"

class PAFEnvironmentVariableSettings : public PAFISettings {
	public:
		PAFEnvironmentVariableSettings() : fPAFPATH(0), fPackagesDirectories(0) {}
		virtual ~PAFEnvironmentVariableSettings();

		virtual TString* GetPAFPATH();
		virtual std::vector<TString*>* GetPackagesDirectories();

	protected:
		TString* GetEnvironmentVariable(const char* variable);
		
	protected:
		TString* fPAFPATH;
		std::vector<TString*>* fPackagesDirectories;

	ClassDef(PAFISettings, 1);
};
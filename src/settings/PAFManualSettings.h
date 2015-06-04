/**
	@brief PAFManualSettings class which holds the variables the user specifies.
	@file PAFManualSettings.h
	@class PAFManualSettings
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#pragma once

#include "PAFISettings.h"

#include "TString.h"

class PAFManualSettings : public PAFISettings 
{
	public:
		PAFManualSettings(TString* pafPath, std::vector<TString*>* packagesDirectories);

		virtual TString* GetPAFPATH();
		virtual std::vector< TString* >* GetPackagesDirectories();

	protected:
		TString 		fPAFPath;
		std::vector<TString*> 	fPackagesDirectories;

	ClassDef(PAFManualSettings, 1);
};

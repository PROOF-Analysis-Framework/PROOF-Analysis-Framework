/**
	@brief PAFISettings class which defines several values required by PAF.
	@file PAFISettings.h
	@class PAFISettings
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-07
 */

#pragma once

#include "TObject.h"

#include "TString.h"

class PAFISettings : public TObject 
{
	public:
		PAFISettings();
		virtual ~PAFISettings();

		virtual TString* GetPAFPATH() = 0;
		virtual std::vector<TString*>* GetPackagesDirectories()= 0;

	ClassDef(PAFISettings, 1);
};

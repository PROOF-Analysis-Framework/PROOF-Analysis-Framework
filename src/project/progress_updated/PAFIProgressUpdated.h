/**
	@brief Interface to provide the method to call when the analysis progress is updated. 
	@file PAFIProgressUpdated.h
	@class PAFIProgressUpdated
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-18
*/

#pragma once

#include "TObject.h"

class PAFIProgressUpdated : public TObject
{
	public:
		virtual void ProgressUpdated(Long64_t total, Long64_t processed) {}

	ClassDef(PAFIProgressUpdated, 1);
};


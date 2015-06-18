/**
	@brief Implementation of PAFIProgressUpdated which uses the logger to show the information.
	@file PAFProgressUpdatedLogger.h
	@class PAFProgressUpdatedLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-18
*/

#pragma once

#include "PAFIProgressUpdated.h"

class PAFProgressUpdatedLogger : public PAFIProgressUpdated
{
	public:
		void ProgressUpdated(Long64_t total, Long64_t processed);

	ClassDef(PAFProgressUpdatedLogger, 1);
};


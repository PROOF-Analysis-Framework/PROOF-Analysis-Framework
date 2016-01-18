/**
	@brief Implementation of PAFIProgressUpdated which uses the logger to show the information.
	@file PAFProgressUpdatedLogger.cxx
	@class PAFProgressUpdatedLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-18
 */

#include "PAFProgressUpdatedLogger.h"

#include "TString.h"

#include "PAF.h"

ClassImp(PAFProgressUpdatedLogger);

void PAFProgressUpdatedLogger::ProgressUpdated(Long64_t total, Long64_t processed)
{
	PAF_INFO("Progress", TString::Format("Completed: %.2f%% of %lld events-.", (processed*100)/((double)total), total).Data());
}

/**
	@brief Interface to provide the method to call when the analysis progress is updated. 
	@file PAFIProgressUpdated.cxx
	@class PAFIProgressUpdated
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-18
 */

#include "PAFIProgressUpdated.h"

#include "PAF.h"

void PAFIProgressUpdated::ProgressUpdated(Long64_t /*total*/, Long64_t /*processed*/)
{
	PAF_FATAL("PAFIProgressUpdated", "It is being executed an interface method.");
}

/**
	@brief PAFLibrary which will contain libraries to load in environments.
	@file PAFLibrary.cxx
	@class PAFLibrary
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-17
*/

#include "PAFLibrary.h"

ClassImp(PAFLibrary);

TString PAFLibrary::GetFileName()
{
	return fFileName;
}

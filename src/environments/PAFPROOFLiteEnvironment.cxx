/**
	@brief Extension of PAFPROOFEnvironment to work over PROOFLite environments.
	@file PAFPROOFLiteEnvironment.cxx
	@class PAFPROOFLiteEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPROOFLiteEnvironment.h"

PAFPROOFLiteEnvironment::PAFPROOFLiteEnvironment(int nSlots)
	: fNSlots(nSlots)
{}

TProof* PAFPROOFLiteEnvironment::doCreateTProof()
{
	return TProof::Open("lite:///?workers=" + fNSlots);
}

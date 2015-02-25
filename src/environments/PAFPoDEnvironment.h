/**
	@brief Extension of PAFPROOFEnvironment to work over PoD environments.
	@file PAFPoDEnvironment.h
	@class PAFPoDEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#pragma once

#include "PAFPROOFEnvironment.h"

class PAFPoDEnvironment : public PAFPROOFEnvironment 
{
	public:
		PAFPoDEnvironment(int nSlots = 10, int maxSlavesPerNode=9999, int timeOut = 60);

	protected:
		TProof* doCreateTProof();

	protected:
		int fNSlots;
		int fMaxSlavesPerNode;
		int fTimeOut;
};


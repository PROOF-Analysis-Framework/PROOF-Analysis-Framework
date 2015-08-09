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
		PAFPoDEnvironment(Int_t nSlots = 10, Int_t maxSlavesPerNode=9999, Int_t timeOut = 60);
		virtual ~PAFPoDEnvironment();

	protected:
		TProof* doCreateTProof();

	protected:
		Int_t fNSlots;
		Int_t fMaxSlavesPerNode;
		Int_t fTimeOut;
};

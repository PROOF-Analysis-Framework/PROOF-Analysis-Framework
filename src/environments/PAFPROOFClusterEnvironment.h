/**
	@brief Extension of PAFPROOFClusterEnvironment to work over PROOFCluster environments.
	@file PAFPROOFClusterEnvironment.h
	@class PAFPROOFClusterEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-18
*/

#pragma once

#include "PAFPROOFEnvironment.h"

class PAFPROOFClusterEnvironment : public PAFPROOFEnvironment 
{
	public:
		PAFPROOFClusterEnvironment(int nSlots = 10, int maxSlavesPerNode = 9999);
		
	protected:
		TProof* doCreateTProof();
		
	protected:
		int fNSlots;
		int fMaxSlavesPerNode;
};


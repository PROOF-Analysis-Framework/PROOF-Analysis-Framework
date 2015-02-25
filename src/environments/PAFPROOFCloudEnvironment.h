/**
	@brief Extension of PAFPROOFCloudEnvironment to work over PROOFCloud environments.
	@file PAFPROOFCloudEnvironment.h
	@class PAFPROOFCloudEnvironment 
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-18
*/

#pragma once

#include "PAFPROOFEnvironment.h"

class PAFPROOFCloudEnvironment : public PAFPROOFEnvironment 
{
	public:
		PAFPROOFCloudEnvironment(int nSlots, int maxSlavesPerNode, bool proofRequest, const TString& proofServer, int proofServerPort);
	
	protected:
		TProof* doCreateTProof();
		
	protected:
		int fNSlots;
		int fMaxSlavesPerNode;
		int fProofRequest;
		const TString& fProofServer;
		int fProofServerPort;
};


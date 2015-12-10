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
		PAFPROOFCloudEnvironment(Int_t nSlots, Int_t maxSlavesPerNode, Bool_t proofRequest, const TString& proofServer, Int_t proofServerPort);

	protected:
		TProof* doCreateTProof();

	protected:
		Int_t fNSlots;
		Int_t fMaxSlavesPerNode;
		Int_t fProofRequest;
		const TString& fProofServer;
		Int_t fProofServerPort;
};

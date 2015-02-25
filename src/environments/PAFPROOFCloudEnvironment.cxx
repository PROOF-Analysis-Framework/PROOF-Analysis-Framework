/**
	@brief Extension of PAFPROOFCloudEnvironment to work over PROOFCloud environments.
	@file PAFPROOFCloudEnvironment.cxx
	@class PAFPROOFCloudEnvironment 
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-18
*/

#include "PAFPROOFCloudEnvironment.h"

PAFPROOFCloudEnvironment::PAFPROOFCloudEnvironment(int nSlots, int maxSlavesPerNode, bool proofRequest, const TString& proofServer, int proofServerPort)
	: PAFPROOFEnvironment(), fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode), fProofRequest(proofRequest), fProofServer(proofServer), fProofServerPort(proofServerPort)
{}

TProof* PAFPROOFCloudEnvironment::doCreateTProof()
{
	TProof* result = 0;
	
	if (fNSlots < 0)
		fNSlots = 10;
	
	TString proofserverchain = "";
	if ( fProofRequest ) {  // User may disable the request
		if (gSystem->Exec("proofcloud start") != 0) {
			return NULL;
		}
		proofserverchain = gSystem->GetFromPipe("proofcloud getserver");
	} else {
		// Build the full user@proofserver:port string
		proofserverchain = "proof@";
		proofserverchain += fProofServer;
		proofserverchain += ":";
		proofserverchain += fProofServerPort;
	}

	result = TProof::Open(proofserverchain);

	if (result)
		result->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);
	
	return result;
}


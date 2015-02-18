/**
	@brief Extension of PAFPROOFCloudEnvironment to work over PROOFCloud environments.
	@file PAFPROOFCloudEnvironment.cxx
	@class PAFPROOFCloudEnvironment 
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-18
*/

#include "PAFPROOFCloudEnvironment.h"

PAFPROOFCloudEnvironment::PAFPROOFCloudEnvironment(int nSlots, int maxSlavesPerNode, 
													bool proofRequest,
													const TString& proofServer,
													int proofServerPort)
{
	if (nSlots < 0)
		nSlots = 10;
	
	TString proofserverchain = "";
	if ( proofRequest ) {  // User may disable the request
		if (gSystem->Exec("proofcloud start") != 0) {
			return;
		}
		proofserverchain = gSystem->GetFromPipe("proofcloud getserver");
	} else {
		// Build the full user@proofserver:port string
		proofserverchain = "proof@";
		proofserverchain += proofServer;
		proofserverchain += ":";
		proofserverchain += proofServerPort;
	}

	fSession = TProof::Open(proofserverchain);

	if (fSession)
		fSession->SetParameter("PROOF_MaxSlavesPerNode", maxSlavesPerNode);
}

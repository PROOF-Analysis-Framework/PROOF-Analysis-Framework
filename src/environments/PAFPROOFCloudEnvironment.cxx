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

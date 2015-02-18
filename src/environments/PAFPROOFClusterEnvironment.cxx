/**
	@brief Extension of PAFPROOFClusterEnvironment to work over PROOFCluster environments.
	@file PAFPROOFClusterEnvironment.h
	@class PAFPROOFClusterEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-18
*/

#include "PAFPROOFClusterEnvironment.h"

#include <fstream>
#include <string>

PAFPROOFClusterEnvironment::PAFPROOFClusterEnvironment(int nSlots, int maxSlavesPerNode)
{
	if (nSlots < 0 )
		nSlots = 10;
	
	// Ask the desired number of workers:
	TString slots_petition;
	slots_petition.Form("startproof -a %d", nSlots);
	// XXX: think of a better way of doing this, 
	// startproof returns the path where the paf_url file is located
	TString fPAFSessionDir = gSystem->GetFromPipe(slots_petition);
file:///home/javier/Documents/PROOF-Analysis-Framework/src/environments/PAFPROOFCloudEnvironmentLinkDef.h
	ifstream paf_url;
	paf_url.open(fPAFSessionDir + "/paf_url");
	if (!paf_url.is_open()) {
		return;
	}
	std::string line;
	getline(paf_url, line);
	TString proofserverchain(line); 

	fSession = TProof::Open(proofserverchain);


	//Use the maximum possible slaves in each node, independently on the number
	//of real cores or the load
	if (fSession)
		fSession->SetParameter("PROOF_MaxSlavesPerNode", maxSlavesPerNode);
}


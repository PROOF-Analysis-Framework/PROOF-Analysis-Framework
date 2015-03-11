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
	: fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode)
{}

TProof* PAFPROOFClusterEnvironment::doCreateTProof()
{
	TProof* result = 0;
	
	if (fNSlots < 0 )
		fNSlots = 10;
	
	// Ask the desired number of workers:
	TString slots_petition;
	slots_petition.Form("startproof -a %d", fNSlots);
	// XXX: think of a better way of doing this, 
	// startproof returns the path where the paf_url file is located
	TString fPAFSessionDir = gSystem->GetFromPipe(slots_petition);
	std::ifstream paf_url;
	paf_url.open(fPAFSessionDir + "/paf_url");
	if (!paf_url.is_open()) {
		return NULL;
	}
	std::string line;
	getline(paf_url, line);
	TString proofserverchain(line); 

	result = TProof::Open(proofserverchain);


	//Use the maximum possible slaves in each node, independently on the number
	//of real cores or the load
	if (result)
		result->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);

	return result;
}



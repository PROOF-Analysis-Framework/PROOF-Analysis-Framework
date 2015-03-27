/**
	@brief Extension of PAFPROOFEnviroment to work over PoD environments.
	@file PAFPoDEnvironment.cxx
	@class PAFPoDEnvironment
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFPoDEnvironment.h"

#include "TSystem.h"
#include "TMath.h"

PAFPoDEnvironment::PAFPoDEnvironment(int nSlots, int maxSlavesPerNode, int timeOut)
	: PAFPROOFEnvironment(), fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode), fTimeOut(timeOut)
{
}

PAFPoDEnvironment::~PAFPoDEnvironment()
{
	 
}

TProof* PAFPoDEnvironment::doCreateTProof()
{
	TProof* result = 0;
	
	// Interval between checks in seconds
	int wait = 1;

	// Number of waiting cycles
	int n_waits = fTimeOut / wait;

	TString podserverstatus=gSystem->GetFromPipe("pod-server status 2>&1");
	if (podserverstatus.Contains("NOT")){
		TString response_pod_start = gSystem->GetFromPipe("pod-server start");
		PAF_DEBUG("PAFPoDEnvironment", response_pod_start);
	}

	//Find if there are already slots being used
	int activeSlots = gSystem->GetFromPipe("pod-info -n").Atoi();

	//Initially assume no slots have been allocated
	int missingSlots = fNSlots - activeSlots;

	if (missingSlots > 0) {
		TString command = Form ("pod-submit -r pbs -n %d", missingSlots);

		TString response_command = gSystem->GetFromPipe(command);
		PAF_DEBUG("PAFPoDEnvironment", response_command);

		int slotsReady = 0;
		//TODO Implement logger messages.
		//int srmsize = 1;
		//int trmsize = (int) TMath::Log10(fTimeOut) + 1;
		//int rmsize  = srmsize + trmsize + 13;
		do {
			gSystem->Sleep(wait*1000);
			slotsReady = gSystem->GetFromPipe("pod-info -n").Atoi();
			n_waits--;
			//srmsize = (slotsReady == 0?1:(int) TMath::Log10(slotsReady) + 1);
			//trmsize = (int) TMath::Log10(n_waits*wait) + 1;
			//rmsize = srmsize + trmsize + 13;
		} while((slotsReady < fNSlots) && (n_waits > 0) );
	}

	result = TProof::Open(gSystem->GetFromPipe("pod-info -c"));

	//Use the maximum possible slaves in each node, independently on the number
	//of real cores or the load. Not sure of the effect here.
	if (result)
		result->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);

	PAF_DEBUG("PAFPoDEnvironment", "Environment loaded successfully");
	return result;
}




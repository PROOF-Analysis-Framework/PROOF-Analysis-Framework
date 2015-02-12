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
{
	// Interval between checks in seconds
	int wait = 1;

	// Number of waiting cycles
	int n_waits = timeOut / wait;

	TString podserverstatus=gSystem->GetFromPipe("pod-server status 2>&1");
	if (podserverstatus.Contains("NOT")){
		TString response_pod_start = gSystem->GetFromPipe("pod-server start");
		PAF_DEBUG("PAFPoDEnvironment", response_pod_start);
	}

	//Find if there are already slots being used
	int activeSlots = gSystem->GetFromPipe("pod-info -n").Atoi();

	//Initially assume no slots have been allocated
	int missingSlots = nSlots - activeSlots;

	if (missingSlots > 0) {
		TString command = Form ("pod-submit -r pbs -n %d", missingSlots);

		TString response_command = gSystem->GetFromPipe(command);
		PAF_DEBUG("PAFPoDEnvironment", response_command);

		int slotsReady = 0;
		int srmsize = 1;
		int trmsize = (int) TMath::Log10(timeOut) + 1;
		int rmsize  = srmsize + trmsize + 13;
		do {
			gSystem->Sleep(wait*1000);
			slotsReady = gSystem->GetFromPipe("pod-info -n").Atoi();
			n_waits--;
			srmsize = (slotsReady == 0?1:(int) TMath::Log10(slotsReady) + 1);
			trmsize = (int) TMath::Log10(n_waits*wait) + 1;
			rmsize = srmsize + trmsize + 13;
		} while((slotsReady < nSlots) && (n_waits > 0) );
	}

	fSession = TProof::Open(gSystem->GetFromPipe("pod-info -c"));

	//Use the maximum possible slaves in each node, independently on the number
	//of real cores or the load. Not sure of the effect here.
	if (fSession)
		fSession->SetParameter("PROOF_MaxSlavesPerNode", maxSlavesPerNode);

	LoadPAF();
}



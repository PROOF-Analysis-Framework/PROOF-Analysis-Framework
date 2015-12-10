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

PAFPoDEnvironment::PAFPoDEnvironment(Int_t nSlots, Int_t maxSlavesPerNode, Int_t timeOut)
	: PAFPROOFEnvironment(), fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode), fTimeOut(timeOut)
{
	if (!gSystem->Getenv("POD_LOCATION"))
	{
		PAF_FATAL("PAFPoDEnvironment", "PoD is not configured in your session.\nPlease configure PoD and retry\nHint: Look for PoD_env.sh");
	}
	if (fNSlots <=0 )
	{
		PAF_FATAL("PAFPoDEnvironment", "The number of slots requested for PAFPoDEnvironment should be greater than 0.");	       
	}
}

PAFPoDEnvironment::~PAFPoDEnvironment()
{
	 
}

TProof* PAFPoDEnvironment::doCreateTProof()
{
	TProof* result = 0;
	
	// Interval between checks in seconds
	Int_t wait = 1;

	// Number of waiting cycles
	Int_t n_waits = fTimeOut / wait;

	TString podserverstatus=gSystem->GetFromPipe("pod-server status 2>&1");
	if (podserverstatus.Contains("NOT"))
	{
		TString response_pod_start = gSystem->GetFromPipe("pod-server start");
		PAF_DEBUG("PAFPoDEnvironment", response_pod_start);
	}

	//Find if there are already slots being used
	Int_t activeSlots = gSystem->GetFromPipe("pod-info -n").Atoi();
	PAF_DEBUG("PAFPoDEnvironment",
		  Form("'pod-info -n' returns %d slots already in use", activeSlots));

	//Initially assume no slots have been allocated
	Int_t missingSlots = fNSlots - activeSlots;

	if (missingSlots > 0) 
	{
		TString command = Form ("pod-submit -r pbs -n %d", missingSlots);
		PAF_DEBUG("PAFPoDEnvironment",
			  Form("Executing '%s'", command.Data()));

		TString response_command = gSystem->GetFromPipe(command);
		PAF_DEBUG("PAFPoDEnvironment", response_command);

		Int_t slotsReady = 0;
		//TODO Implement logger messages.
		//Int_t srmsize = 1;
		//Int_t trmsize = (Int_t) TMath::Log10(fTimeOut) + 1;
		//Int_t rmsize  = srmsize + trmsize + 13;
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
	{
		result->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);
	}

	PAF_DEBUG("PAFPoDEnvironment", "Environment loaded successfully");
	return result;
}

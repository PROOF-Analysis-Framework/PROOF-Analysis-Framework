#include "PoDPlugin.h"

// PAF includes
#include "PAF.h"

// ROOT includes
#include "TSystem.h"
#include "TMath.h"

// C++ includes
#include <iostream>

#if !defined(__CINT__)
ClassImp(PoDPlugin);
#endif

PoDPlugin::PoDPlugin(int nSlots, int maxSlavesPerNode, int timeOut):
  fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode), fTimeOut(timeOut)  {
#ifdef DEBUGPOD
  std::cout << PAFDEBUG << "=> PoDPlugin::PoDPlugin(" << nSlots << "," 
	    << timeOut << ")" << std::endl;
#endif


  if (nSlots < 0 )
    fNSlots = 10;
  
  std::cout << PAFINFO 
	    << "+ PROOF on Demand (PoD)  mode selected." 
	    << std::endl;


#ifdef DEBUGPOD
  std::cout << PAFDEBUG << "<= PoDPlugin::PoDPlugin(" << nSlots << "," 
	    << timeOut << ")" << std::endl;
#endif
}

PoDPlugin::~PoDPlugin() {}

bool PoDPlugin::InitialChecks() const {
#ifdef DEBUGPOD
  std::cout << PAFDEBUG << "=> PoDPlugin::InitialChecks()" << std::endl;
#endif


  if (!gSystem->Getenv("POD_LOCATION")) {
    std::cerr << PAFERROR 
	      << "PoD path not set. Try to source something like /opt/PoD/PoD_env.sh" 
	      << std::endl
	      << PAFERROR << "Exiting!" << std::endl;
    return false;
  }

#ifdef DEBUGPOD
  std::cout << PAFDEBUG << "<= PoDPlugin::InitialChecks() true" << std::endl;
#endif

  return true;
}

TProof* PoDPlugin::Init() {

#ifdef DEBUGPOD
  std::cout << PAFDEBUG << "=> PoDPlugin::Init()" << std::endl;
#endif

  // Interval between checks in seconds
  int wait = 1;

  // Number of waiting cycles
  int n_waits = fTimeOut / wait;

  
  std::cout << PAFINFO << "+ Using local node for PoD" << std::endl;


  // Start pod-server if it isn't runnign already
  std::cout << PAFINFO << "+ Testing PoD server... " << std::endl;
  TString podserverstatus=gSystem->GetFromPipe("pod-server status 2>&1");
  if (podserverstatus.Contains("NOT")) {
    std::cout << PAFINFO << "+ PoD server not running, starting it: " 
	      << std::endl;
    gSystem->Exec("pod-server start");
  }
  else
    std::cout << PAFINFO << "+ PoD server already running, reusing it" 
	      << std::endl;



  //Find if there are already slots being used
  int activeSlots = gSystem->GetFromPipe("pod-info -n").Atoi();

  if (activeSlots) {
    std::cout << PAFINFO << "+ You already have " << activeSlots 
	      << " slots allocated." << std::endl;
  }

  //Initially assume no slots have been allocated
  int missingSlots = fNSlots - activeSlots;

//   if (missingSlots < 0) {
//     gPAFOptions->SetNSlots(activeSlots);
//   }

  if (missingSlots > 0) {
    std::cout << PAFINFO << "+ Asking for " << missingSlots << " slots" 
	      << std::endl;
    TString command = Form ("pod-submit -r pbs -n %d", missingSlots);

#if DEBUGPOD
    std::cerr << PAFDEBUG << "Executing " << command << std::endl;
#endif
    gSystem->Exec(command);


    //We have to wait until we have all our WNs
    std::cout << PAFINFO << "+ Waiting for batch system. Found 0 slots (" 
	      << fTimeOut << " s)  " << std::flush; 

    int slotsReady = 0;
    int srmsize = 1;
    int trmsize = (int) TMath::Log10(fTimeOut) + 1;
    int rmsize  = srmsize + trmsize + 13;
    do {
      gSystem->Sleep(wait*1000);
      slotsReady = gSystem->GetFromPipe("pod-info -n").Atoi();
      n_waits--;
      for (int i = 0; i < rmsize; i++)
        std::cout << '\b';
      std::cout << slotsReady << " slots (" << n_waits * wait << " s)  "
		<< std::flush;
      srmsize = (slotsReady == 0?1:(int) TMath::Log10(slotsReady) + 1);
      trmsize = (int) TMath::Log10(n_waits*wait) + 1;
      rmsize = srmsize + trmsize + 13;
    } while((slotsReady < fNSlots) && (n_waits > 0) );
    std::cout << std::endl;
  }

  std::cout << PAFINFO << "+ We will use " 
	    << gSystem->GetFromPipe("pod-info -n").Atoi()
	    << " slots" << std::endl;


  // Open proof session using the server we launched with PoD
  std::cout << PAFINFO << "+ Opening Proof session using " 
	    << gSystem->GetFromPipe("pod-info -c") << std::endl;


  fProof = TProof::Open(gSystem->GetFromPipe("pod-info -c"));

  //Use the maximum possible slaves in each node, independently on the number
  //of real cores or the load. Not sure of the effect here.
  if (fProof)
    fProof->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);


#ifdef DEBUGPOD
  std::cerr << PAFDEBUG << "<= PoDPlugin::Init() --> Returning " 
	    << fProof << std::endl;
#endif

  return fProof;

}

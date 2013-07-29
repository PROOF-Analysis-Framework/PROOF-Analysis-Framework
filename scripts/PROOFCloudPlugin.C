#include "PROOFCloudPlugin.h"

// PAF includes
#include "PAF.h"

// ROOT includes
#include "TSystem.h"
#include "TMath.h"

// C++ includes
#include <iostream>
#include <fstream>

PROOFCloudPlugin::PROOFCloudPlugin(int nSlots, int maxSlavesPerNode, 
				   bool proofRequest,
				   const TString& proofServer, 
				   int proofServerPort):
  fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode), 
  fProofRequest(proofRequest),
  fProofServer(proofServer), fProofServerPort(proofServerPort) {
#ifdef DEBUGPROOFCLOUD
  std::cout << PAFDEBUG << "=> PROOFCloudPlugin::PROOFCloudPlugin(" << nSlots
	    << "," << proofRequest 
	    << "," << proofServer << "," << proofServerPort  
	    << ")" << std::endl;
#endif


  if (nSlots < 0 )
    fNSlots = 10;
  
  std::cout << PAFINFO << "+ PROOF Lite mode selected." << std::endl;


#ifdef DEBUGPROOFCLOUD
  std::cout << PAFDEBUG << "<= PROOFCloudPlugin::PROOFCloudPlugin(" << nSlots
	    << "," << proofRequest 
	    << "," << proofServer << "," << proofServerPort  
	    << ")" << std::endl;
#endif
}

PROOFCloudPlugin::~PROOFCloudPlugin() {}

bool PROOFCloudPlugin::InitialChecks() const {
#ifdef DEBUGPROOFCLOUD
  std::cout << PAFDEBUG << "=> PROOFCloudPlugin::InitialChecks()" << std::endl;
#endif

  // XXX - I.G. Nothing to check?
  // XXX - I.G. Perhaps the existance of Cloud utilities in the path?


#ifdef DEBUGPROOFCLOUD
  std::cout << PAFDEBUG << "<= PROOFCloudPlugin::InitialChecks() true" << std::endl;
#endif

  return true;
}

TProof* PROOFCloudPlugin::Init() {

#ifdef DEBUGPROOFCLOUD
  std::cerr << PAFDEBUG << "=> PROOFCloudPlugin::Init()" << std::endl;
#endif

  std::cout << PAFINFO << "+ PROOF Cloud mode selected." << std::endl;
  TString proofserverchain = "";
  if ( fProofRequest ) {  // User may disable the request
#if DEBUGPROOFCLOUD
    std::cerr << PAFDEBUG << "Calling startproof cloud!" << std::endl;
#endif
    if (gSystem->Exec("proofcloud start") != 0) {
      std::cerr << PAFERROR << "ERROR Trying to get machines" << std::endl;
      return 0;
    }
    proofserverchain = gSystem->GetFromPipe("proofcloud getserver");
  } else {
    // Build the full user@proofserver:port string
    proofserverchain = "proof@";
    proofserverchain +=fProofServer;
    proofserverchain +=":";
    proofserverchain +=fProofServerPort;
  }
  std::cout << PAFINFO << "+ Starting PROOF session at " << proofserverchain 
	    << "..." << std::endl;
  //gPAFOptions->proofSession = TProof::Open(proofserverchain);
  //gPAFOptions->proofSession = TProof::Reset(proofserverchain, kTRUE);

  fProof = TProof::Open(proofserverchain);


  //Use the maximum possible slaves in each node, independently on the number
  //of real cores or the load
  if (fProof)
    fProof->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);


#ifdef DEBUGPROOFCLOUD
  std::cerr << PAFDEBUG << "<= PROOFCloudPlugin::Init() --> Returning " 
	    << fProof << std::endl;
#endif

  return fProof;
}

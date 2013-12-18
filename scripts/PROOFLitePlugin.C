#include "PROOFLitePlugin.h"

// PAF includes
#include "PAF.h"

// ROOT includes
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"

// C++ includes
#include <iostream>

PROOFLitePlugin::PROOFLitePlugin(int nSlots):fNSlots(nSlots) {
#ifdef DEBUGPROOFLITE
  std::cout << PAFDEBUG << "=> PROOFLitePlugin::PROOFLitePlugin(" << nSlots 
	    << ")" << std::endl;
#endif


  if (nSlots < 0 )
    fNSlots = 10;
  
  std::cout << PAFINFO << "+ PROOF Lite mode selected." << std::endl;


#ifdef DEBUGPROOFLITE
  std::cout << PAFDEBUG << "<= PROOFLitePlugin::PROOFLitePlugin(" << nSlots
	    << ")" << std::endl;
#endif
}

PROOFLitePlugin::~PROOFLitePlugin() {}

bool PROOFLitePlugin::InitialChecks() const {
#ifdef DEBUGPROOFLITE
  std::cout << PAFDEBUG << "=> PROOFLitePlugin::InitialChecks()" << std::endl;
#endif

  //Nothing to check


#ifdef DEBUGPROOFLITE
  std::cout << PAFDEBUG << "<= PROOFLitePlugin::InitialChecks() true" << std::endl;
#endif

  return true;
}

TProof* PROOFLitePlugin::Init() {

#ifdef DEBUGPROOFLITE
  std::cout << PAFDEBUG << "=> PROOFLitePlugin::Init()" << std::endl;
#endif

  cout << PAFINFO << "Initializing PROOF using local node." << std::endl;

  //String that will be passed to PROOF to start the session
  TString nworkers(""); 


  if (fNSlots > 0) {
    SysInfo_t si;
    Int_t ncpus = 0;

    // Finding out the total number of cpus available
    if (gSystem->GetSysInfo(&si) == 0)
      ncpus = TMath::Min(fNSlots, si.fCpus);
    std::cout << PAFINFO << "+ The system has " << si.fCpus 
	      << " slots available." << std::endl;
      
    if (fNSlots > ncpus)
      std::cerr << PAFWARN << "+ You specified a larger number of slots (" 
		<< fNSlots << ")." << std::endl;
    
    std::cout << PAFINFO << "+ We will try to use " << ncpus << " slots" 
	      << std::endl;

    //The syntax to set the number of slots changed in ROOT 5.30.00
    if (gROOT->GetVersionInt() < 53000)
      nworkers.Form("workers=%d",ncpus);
    else
      nworkers.Form("lite:///?workers=%d",ncpus);


  }


#ifdef DEBUGPROOFLITE
  std::cerr << PAFDEBUG << "nworkers string: " << nworkers << std::endl;
  std::cout << PAFDEBUG << "<= PROOFLitePlugin::Init()" << std::endl;
#endif
  fProof = TProof::Open(nworkers.Data());

#ifdef DEBUGPROOFLITE
  std::cerr << PAFDEBUG << "<= PROOFLitePlugin::Init() --> Returning " 
	    << fProof << std::endl;
#endif
  return fProof;

}

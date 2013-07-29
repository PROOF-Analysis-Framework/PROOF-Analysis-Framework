#include "PROOFClusterPlugin.h"

// PAF includes
#include "PAF.h"

// ROOT includes
#include "TSystem.h"
#include "TMath.h"

// C++ includes
#include <iostream>
#include <fstream>

PROOFClusterPlugin::PROOFClusterPlugin(int nSlots, int maxSlavesPerNode):
  fNSlots(nSlots), fMaxSlavesPerNode(maxSlavesPerNode) {
#ifdef DEBUGPROOFCLUSTER
  std::cout << PAFDEBUG << "=> PROOFClusterPlugin::PROOFClusterPlugin(" << nSlots << "," 
	    << maxSlavesPerNode << ")" << std::endl;
#endif


  if (nSlots < 0 )
    fNSlots = 10;
  
  std::cout << PAFINFO << "+ PROOF Lite mode selected." << std::endl;


#ifdef DEBUGPROOFCLUSTER
  std::cout << PAFDEBUG << "<= PROOFClusterPlugin::PROOFClusterPlugin(" << nSlots << "," 
	    << maxSlavesPerNode << ")" << std::endl;
#endif
}

PROOFClusterPlugin::~PROOFClusterPlugin() {}

bool PROOFClusterPlugin::InitialChecks() const {
#ifdef DEBUGPROOFCLUSTER
  std::cout << PAFDEBUG << "=> PROOFClusterPlugin::InitialChecks()" << std::endl;
#endif

  //Check if startproof is in the path
  TString sp = gSystem->GetFromPipe("type -p startproof");
  if (sp == "") {
    std::cerr << PAFERROR 
	      << "PROOF Cluster environment not set. Make sure the installation directory is in the path."
	      << std::endl
	      << PAFERROR << "Exiting!" << std::endl;
    return false;
  }

    


#ifdef DEBUGPROOFCLUSTER
  std::cout << PAFDEBUG << "<= PROOFClusterPlugin::InitialChecks() true" << std::endl;
#endif

  return true;
}

TProof* PROOFClusterPlugin::Init() {

#ifdef DEBUGPROOFCLUSTER
  std::cout << PAFDEBUG << "=> PROOFClusterPlugin::Init()" << std::endl;
#endif

  cout << PAFINFO << "+ PROOF Cluster mode selected. Using:" << endl
       << PAFINFO << " - N. Slots     = " << fNSlots << endl
       << PAFINFO << " - Max. N. Slav.= " << fMaxSlavesPerNode << endl;

  // Ask the desired number of workers:
  TString slots_petition;
  slots_petition.Form("startproof -a %d", fNSlots);
#if DEBUGPROOFCLUSTER
  cerr << PAFDEBUG << "Slots petition: " << slots_petition  << endl;
#endif
  // XXX: think of a better way of doing this, 
  // startproof returns the path where the paf_url file is located
  fPAFSessionDir = gSystem->GetFromPipe(slots_petition);

  ifstream paf_url;
  paf_url.open(fPAFSessionDir + "/paf_url");
  if (!paf_url.is_open()) {
    cerr << PAFERROR << "Cannot open file with proof master address" << endl;
    return 0;
  }
  string line;
  getline(paf_url, line);
  TString proofserverchain(line); 

  cout << PAFINFO << "+ Starting PROOF session at " << proofserverchain << endl;
  fProof = TProof::Open(proofserverchain);


  //Use the maximum possible slaves in each node, independently on the number
  //of real cores or the load
  if (fProof)
    fProof->SetParameter("PROOF_MaxSlavesPerNode", fMaxSlavesPerNode);


#ifdef DEBUGPROOFCLUSTER
  std::cerr << PAFDEBUG << "<= PROOFClusterPlugin::Init() --> Returning " 
	    << fProof << std::endl;
#endif

  return fProof;
}



void PROOFClusterPlugin::Finish() {
  // XXX: enol, remove the active file, so others can reuse!
  gSystem->Unlink(fPAFSessionDir + "/active");
  cerr << PAFWARN << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << PAFWARN << " REMINDER: If you do not need anymore the slots you asked for" << endl 
       << PAFWARN << " please free them after leaving the ROOT session," << endl
       << PAFWARN << " you can do that just by typing 'endproof' " << endl  
       << PAFWARN << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

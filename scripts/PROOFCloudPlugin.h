#ifndef PROOFCLOUDPLUGIN_H
#define PROOFCLOUDPLUGIN_H

#include "PAFModePlugin.h"

#include "TString.h"


#ifdef DEBUG
#define DEBUGPROOFCLOUD DEBUG
#else
#undef DEBUGPROOFCLOUD
#endif

class PROOFCloudPlugin:public PAFModePlugin {

 public:

  PROOFCloudPlugin(int nSlots = 10, int maxSlavesPerNode=9999, 
		   bool proofRequest = true,
		   const TString& proofServer = "proof.ifca.es",
		   int proofServerPort = 1093);
  virtual ~PROOFCloudPlugin();

  virtual bool InitialChecks() const;
  virtual TProof* Init();


 protected:

  // Number of slots you would like to use
  int fNSlots;
  // Maximum number of slaves per node (use 9999 for all)
  int fMaxSlavesPerNode;
  //+ Perform or not the request for nodes (default is True)
  bool fProofRequest;
  //+ Proof Server name (default is proof.ifca.es)
  TString fProofServer;
  //+ Proof Server port (default is 1093)
  int fProofServerPort;


};


#endif

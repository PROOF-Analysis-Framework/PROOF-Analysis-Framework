#ifndef PROOFCLUSTERPLUGIN_H
#define PROOFCLUSTERPLUGIN_H

#include "PAFModePlugin.h"

#ifdef DEBUG
#define DEBUGPROOFCLUSTER DEBUG
#else
#undef DEBUGPROOFCLUSTER
#endif

class PROOFClusterPlugin:public PAFModePlugin {

 public:

  PROOFClusterPlugin(int nSlots = 10, int maxSlavesPerNode=9999);
  virtual ~PROOFClusterPlugin();

  virtual bool InitialChecks() const;
  virtual TProof* Init();
  virtual void Finish();


 protected:

  // Number of slots you would like to use
  int fNSlots;
  // Maximum number of slaves per node (use 9999 for all)
  int fMaxSlavesPerNode;
  // Internal variable to keep the session dir of PAF
  TString fPAFSessionDir;

};


#endif

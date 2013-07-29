#ifndef PODPLUGIN_H
#define PODPLUGIN_H

#include "PAFModePlugin.h"

#ifdef DEBUG
#define DEBUGPOD DEBUG
#else
#undef DEBUGPOD
#endif

class PoDPlugin:public PAFModePlugin {

 public:

  PoDPlugin(int nSlots = 10, int maxSlavesPerNode=9999, int timeOut = 20);
  virtual ~PoDPlugin();

  virtual bool InitialChecks() const;
  virtual TProof* Init();


 protected:

  // Number of slots you would like to use
  int fNSlots;

  // Max time we will wait to get all slots
  // when using PoD to set up our proof cluster
  int fTimeOut; 
  
  // Maximum number of slaves per node (use 9999 for all)
  int fMaxSlavesPerNode;

  ClassDef(PoDPlugin,1);
};


#endif

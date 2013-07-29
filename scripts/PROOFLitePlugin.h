#ifndef PROOFLITEPLUGIN_H
#define PROOFLITEPLUGIN_H

#include "PAFModePlugin.h"

#ifdef DEBUG
#define DEBUGPROOFLITE DEBUG
#else
#undef DEBUGPROOFLITE
#endif

class PROOFLitePlugin:public PAFModePlugin {

 public:

  PROOFLitePlugin(int nSlots = 10);
  virtual ~PROOFLitePlugin();

  virtual bool InitialChecks() const;
  virtual TProof* Init();


 protected:

  // Number of slots you would like to use
  int fNSlots;

};


#endif

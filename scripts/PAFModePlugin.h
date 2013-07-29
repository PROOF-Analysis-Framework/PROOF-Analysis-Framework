#ifndef PAFMODEPLUGIN_H
#define PAFMODEPLUGIN_H

#include "TProof.h"

class PAFModePlugin {

 public:

  PAFModePlugin():fProof(0) {}
  virtual ~PAFModePlugin() {}

  virtual bool InitialChecks() const = 0;
  virtual TProof* Init() = 0;
  virtual void Finish() {}


 protected:

  TProof* fProof;

  ClassDef(PAFModePlugin,1);
};


#endif

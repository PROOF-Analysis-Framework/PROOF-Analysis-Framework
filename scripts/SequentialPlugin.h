#ifndef SEQUENTIALPLUGIN_H
#define SEQUENTIALPLUGIN_H

#include "PAFModePlugin.h"

#ifdef DEBUG
#define DEBUGSEQUENTIAL DEBUG
#else
#undef DEBUGSEQUENTIAL
#endif

class SequentialPlugin:public PAFModePlugin {

 public:

  SequentialPlugin();
  virtual ~SequentialPlugin() {}

  virtual bool InitialChecks() const {return true;}
  virtual TProof* Init();


 protected:


  ClassDef(SequentialPlugin,1);
};


#endif

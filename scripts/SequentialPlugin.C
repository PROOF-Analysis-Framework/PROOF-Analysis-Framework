#include "SequentialPlugin.h"

// PAF includes
#include "PAF.h"

// C++ includes
#include <iostream>

#if !defined(__CINT__)
ClassImp(SequentialPlugin);
#endif

SequentialPlugin::SequentialPlugin():fProof(0) {
#ifdef DEBUGSEQUENTIAL
  std::cout << PAFDEBUG << "=> SequentialPlugin::SequentialPlugin()" << std::endl;
#endif

  std::cout << PAFINFO << "+ Sequential mode selected." << std::endl;


#ifdef DEBUGSEQUENTIAL
  std::cout << PAFDEBUG << "<= SequentialPlugin::SequentialPlugin()" << std::endl;
#endif
}



TProof* SequentialPlugin::Init() {

#ifdef DEBUGSEQUENTIAL
  std::cout << PAFDEBUG << "=> SequentialPlugin::Init()" << std::endl;
#endif

   cout << PAFINFO << "+ Sequential mode selected. No PROOF will be used." << endl;


#ifdef DEBUGSEQUENTIAL
  std::cerr << PAFDEBUG << "<= SequentialPlugin::Init() --> Returning " 
	    << fProof << std::endl;
#endif

  return fProof; // fProof = 0 

}

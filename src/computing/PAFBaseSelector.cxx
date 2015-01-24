/**
	@brief Internal PAF class to create the required TSelector in Proof.
	@file PAFBaseSelector.cxx
	@class PAFBaseSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFBaseSelector.h"
#include "../util/PAFNamedContainer.h"

ClassImp(PAFBaseSelector);

void PAFBaseSelector::SlaveBegin(TTree* tree)
{
	fPAFISelector = (PAFISelector*) (((PAFNamedContainer*)FindInput("PAFSelector"))->GetObject());	

	fPAFISelector->SetPROOFData(fInput, fOutput);
	fPAFISelector->SetPAFData(fInputParameters, (PAFAnalysis*)this);

	fPAFISelector->Initialise();
}

Bool_t PAFBaseSelector::Process(Long64_t entry)
{
	fChain->GetTree()->GetEntry(entry);

	fPAFISelector->InsideLoop();
	return kTRUE;
}

void PAFBaseSelector::Terminate()
{
	fPAFISelector->SetPROOFData(fInput, fOutput);	
	fPAFISelector->SetPAFData(fInputParameters, (PAFAnalysis*)this);
  	fPAFISelector->Summary();
}

TObject* PAFBaseSelector::FindInput(TString name, TString classname) {              
  TObject* object = 0;                                                              
  TObject* tmpobj = 0 ;                                                             
  for (int i = 0; i < fInput->GetEntries(); i++) {                                  
    tmpobj = fInput->At(i);                                                         
    if (name == tmpobj->GetName())                                                  
      if (classname == "" || classname == tmpobj->IsA()->GetName()) {               
        object = tmpobj;                                                            
        break;                                                                      
      }
  }                                                                                 
  return object;                                                                    
}     



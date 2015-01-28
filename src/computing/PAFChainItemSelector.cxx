/**
	@brief Abstract class where the users should place his own code using inheritance.
	@file PAFChainItemSelector.cxx
	@class PAFChainItemSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-04
*/

#include "PAFChainItemSelector.h"

ClassImp(PAFChainItemSelector);

TTree* PAFChainItemSelector::CreateTree(const char* name, const char* title) {

  TTree* h = new TTree(name, title);
  fOutput->Add(h);
  return h;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
					Int_t nbinsx, Double_t* bins){
	TH1F* result = new TH1F(name, title, nbinsx, bins);
	fOutput->Add(result);
	return result;
}

TH1F* PAFChainItemSelector::CreateH1F(const char* name, const char* title,
                                     Int_t nbinsx, Axis_t xlow, Axis_t xup) {
  TH1F* h = new TH1F(name, title, nbinsx, xlow, xup);
  fOutput->Add(h);
  return h;
}

TObject* PAFChainItemSelector::FindInput(TString name, TString classname) {
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

TObject* PAFChainItemSelector::FindOutput(TString name, TString classname) {
#ifdef DEBUGPAFBASESELECTOR
  std::cerr << PAFDEBUG << "==> PAFBaseSelector::FindOutput("
            << name << ", " << classname << ")" << std::endl;
#endif

  // The object we will return
  TObject* object = 0;
  // XXX This can probably be fixed by reopening the file
  // If we are using merging through files, we cannot find out the objects
  // in the output list. They are already gone
  TNamed* mergeThroughFile = (TNamed*) FindInput("PAF_MergeThroughFile");
  if (!mergeThroughFile) {
    TObject* tmpobj = 0 ;
#if DEBUGPAFBASESELECTOR > 1
    std::cerr << PAFDEBUG << "There are " << fOutput->GetEntries()
              << " entries in fOutput" << std::endl;
    std::cerr << PAFDEBUG << "";
    fOutput->Print();
#endif
    for(int i = 0; i < fOutput->GetEntries(); i++) {
      tmpobj = fOutput->At(i);
      if (name == tmpobj->GetName())
        if (classname == "" || classname == tmpobj->IsA()->GetName()) {
          object = tmpobj;
          break;
        }
      }
    }
    else {
/*
      std::cerr << PAFDEBUG << "Cannot find out variables when merging through file"
                << std::endl
                << "        Returning 0"
                << std::endl;*/
    }

#ifdef DEBUGPAFBASESELECTOR
    std::cerr << PAFDEBUG << "<== PAFBaseSelector::FindOutput("
              << name << ", " << classname << ")"
              << " --> " << object << std::endl;
#endif
  return object;
}


TObject* PAFChainItemSelector::FindOutputByClassName(TString classname) {
  TObject* object = 0;
  TObject* tmpobj = 0 ;
  for (int i = 0; i < fOutput->GetEntries(); i++) {
    tmpobj = fOutput->At(i);
    if (classname == tmpobj->IsA()->GetName()) {
      object = tmpobj;
      break;
    }
  }
  return object;
}

/*TCounterUI* PAFChainItemSelector::InitCounterUI(const char* name, const char* title,
						unsigned int init) {
	TCounterUI* result = new TCounterUI(name, title, init);
	fOutput->Add(result);
	return result;
}*/

void PAFChainItemSelector::SetPROOFData(TList* input, TSelectorList* output)
{
	fInput = input;
	fOutput = output;
}

void PAFChainItemSelector::SetPAFData(InputParameters* inputParameters, PAFAnalysis* data, PAFVariableContainer* selectorParams)
{
	fInputParameters = inputParameters;
	fData = data;
	fSelectorParams = selectorParams;
}

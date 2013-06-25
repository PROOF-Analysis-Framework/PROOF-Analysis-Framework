///////////////////////////////////////////////////////////////////////
//
//    FILE: PAFBaseSelector.h
//   CLASS: PAFBaseSelector
// AUTHORS: A.Y. Rodriguez Marrero, I. Gonzalez Caballero
//    DATE: 2010
//
// CONTENT: Extensions to the TSelector Class to deal with our trees
//
///////////////////////////////////////////////////////////////////////

#ifndef PAFBaseSelector_h
#define PAFBaseSelector_h

// ROOT includes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Forward references for ROOT classes
class TH1F;
class TH1D;
class TH2F;
class TTree;
class TProfile;

// Framework includes that might be also moved to the
// implementation file
#include "TCounterUI.h"
#include "InputParameters.h"

class PAFBaseSelector : public TSelector {
 public :
  /////////////////////////////////////////////////////////
  //Methods from TSelector
  PAFBaseSelector(TTree * /*tree*/ =0):fNEventsProcessed(0),fPrintInputParameters(false) { }
  virtual ~PAFBaseSelector() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  //
  //////////////////////////////////////////////////////////////
  
  //////////////////////////////////////////////////////////////
  // Methods to create counters and histograms
  TCounterUI *InitCounterUI(const char* name, const char* title,
			    unsigned int init);

  //TTree
  TTree* CreateTree(const char* name, const char* title);

  //TH1F
  TH1F* CreateH1F(const char* name, const char* title,
                  Int_t nbinsx, Axis_t xlow, Axis_t xup);
  TH1F* CreateH1F(const char* name, const char* title,
                  Int_t nbinsx, Float_t* bins);
  TH1F* CreateH1F(const char* name, const char* title,
                  Int_t nbinsx, Double_t* bins);

  //TH1D
  TH1D* CreateH1D(const char* name, const char* title,
                  Int_t nbinsx, Axis_t xlow, Axis_t xup);
  TH1D* CreateH1D(const char* name, const char* title,
                  Int_t nbinsx, Double_t* bins);

  //TH2F
  TH2F* CreateH2F(const char* name, const char* title,
                  Int_t nbinsx, Axis_t xlow, Axis_t xup,
                  Int_t nbinsy, Axis_t ylow, Axis_t yup);
  TH2F* CreateH2F(const char* name, const char* title,
		  Int_t nbinsx, Float_t* xbins,
		  Int_t nbinsy, Float_t* ybins);
  
  TH2F* CreateH2F(const char* name, const char* title,
		  Int_t nbinsx, Double_t* xbins,
		  Int_t nbinsy, Double_t* ybins);
  
  TH2F* CreateH2F(const char* name, const char* title,
		  Int_t nbinsx, Double_t* xbins,
		  Int_t nbinsy, Axis_t ylow, Axis_t yup);
  
  //TProfile
  TProfile* CreateProfile(const char* name, const char* title,
			  Int_t nbinsx, Axis_t xlow, Axis_t xup,
			  Axis_t ylow, Axis_t yup);

  //
  //////////////////////////////////////////////////////////////
  
  //////////////////////////////////////////////////////////////
  // Methods to retrieve the objects at the end of the run
  TObject* FindOutput(TString name, TString classname = "");
  TObject* FindInput(TString name, TString classname = "");
  
  TObject* FindOutputByClassName(TString classname);
  //
  /////////////////////////////////////////////////////////////
  
  //////////////////////////////////////////////////////////////
  // Methods related to input parameters
  InputParameters* GetInputParameters() { return fInputParameters;}
  //
  /////////////////////////////////////////////////////////////
  


 protected: 
  //////////////////////////////////////////////////////////////
  // To be implemented in the user analysis...
  //
  virtual void InitialiseParameters() {}
  virtual void Initialise() = 0;
  virtual void InsideLoop() = 0;
  virtual void SetDataMembersAtTermination() {} //OBSOLETE
  virtual void Summary() = 0;
  //
  /////////////////////////////////////////////////////////////
  



 public:
  // From TSelector...
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain


 protected:
  InputParameters* fInputParameters;
  TCounterUI*      fNEventsProcessed;
  bool             fPrintInputParameters;



  ClassDef(PAFBaseSelector,0);

};

#endif


#ifdef PAFBaseSelector_cxx
Bool_t PAFBaseSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef PAFBaseSelector_cxx

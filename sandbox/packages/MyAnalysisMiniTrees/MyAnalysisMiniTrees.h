#pragma once

#include "../PAF/computing/PAFChainItemSelector.h"
#include "../PAFAnalysis/PAFAnalysis.h"

#include <TH1F.h>
#include <TTree.h>

class MyAnalysisMiniTrees : public PAFChainItemSelector {

 public:
   MyAnalysisMiniTrees(TTree *tree=0);
   virtual ~MyAnalysisMiniTrees() {}

 protected:
   virtual void InitialiseParameters();
   virtual void Initialise();
   virtual void InsideLoop();
   virtual void Summary(); 

 protected:
   // My Declarations:
   // Histograms
   TH1F       *myHistogram;

   // Counters
   //TCounterUI *nEvents;

   // Trees
   TTree      *myTree;


   // Variables used to locate Input Parameters
   TString      ss;
   TString      sss;
   Int_t        ii;
   Int_t        iii;
   Float_t      dd;
   Double_t     db;
   Float_t      ddd;
   Double_t     ddb;
   Bool_t       bb;
   Bool_t       bbb;
   
   // 
   Float_t     tMetEt;
 
   ClassDef(MyAnalysisMiniTrees,0);
};


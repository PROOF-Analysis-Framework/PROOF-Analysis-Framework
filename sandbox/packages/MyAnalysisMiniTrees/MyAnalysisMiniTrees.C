#include "MyAnalysisMiniTrees.h"

#include <iostream>

MyAnalysisMiniTrees::MyAnalysisMiniTrees(TTree* tree):
  myHistogram(0), myTree(0) {
}

void MyAnalysisMiniTrees::InitialiseParameters() {
   // Initialise() is called every time parameters are needed and unknown to the class
   // Assign here the values retrieved to some data members.

   // Example of Accessing to different kind of Input Parameters
   if ( fInputParameters->GetString() ) ss = fInputParameters->GetString();
   ii = fInputParameters->TheInt();
   dd = fInputParameters->TheFloat();
   db = fInputParameters->TheDouble();
   bb = fInputParameters->TheBool();
   if ( fInputParameters->TheNamedString("sel1") ) sss = fInputParameters->TheNamedString("sel1");
   fInputParameters->TheNamedInt("i1",iii);
   fInputParameters->TheNamedFloat("d1",ddd);
   fInputParameters->TheNamedDouble("db1",ddb);
   fInputParameters->TheNamedBool("b1",bbb);

}

void MyAnalysisMiniTrees::Initialise() {
   // Initialise() is called at the start of the query at the worker nodes
   // where the analysis is going to run


   // Histograms, counters and trees need to be created here

   /////// Histograms
   // Create a TH1F histogram: myhistogram is a pointer to TH1F
   myHistogram = CreateH1F("myHistogram","#slash{E}_{T}", 100, 0., 200.);
   // Create a TH1D histogram
   // CreateH1D(const char* name, const char* title, 
               // Int_t nbinsx, Axis_t xlow, Axis_t xup)
   // Create a TH2F histogram
   // CreateH2F(const char* name, const char* title,
               // Int_t nbinsx, Axis_t xlow, Axis_t xup,
               // Int_t nbinsy, Axis_t ylow, Axis_t yup)


   /////// Counters
   // Create a counter: nEvents is a TCounterUI
   // InitCounterUI(const char* name, const char* title, unsigned int init)
//   nEvents = InitCounterUI("nEvents","Number of analyzed events",0);


   /////// Trees
   // Create a TTree tree: myTree is a pointer to TTree
   myTree = CreateTree("Tree","my Tree");
   // ... add Branches
   myTree->Branch("METET",&tMetEt,"tMetEt/D");
}

void MyAnalysisMiniTrees::InsideLoop() {
   // The InsideLoop() function is called for each entry in the tree
   // to be processed  

   // Histograms...
   myHistogram->Fill(fData->T_METPF_ET);
//	myHistogram->Fill(T_METPF_ET);
   // Counters...
//   (*nEvents)++;

   // Trees...
   tMetEt = fData->T_METPF_ET;
//	tMetEt = T_METPF_ET;
	myTree->Fill();
}


void MyAnalysisMiniTrees::Summary() {
   
   //   cout << "======" << endl;
   //   cout << "SUMARY" << endl;
   //   cout << "======" << endl;

   cout << "------------------------------------------" << endl;
   //cout << *nEvents << " raw Events (no weighted)  " << endl;
   cout << "------------------------------------------" << endl;
}

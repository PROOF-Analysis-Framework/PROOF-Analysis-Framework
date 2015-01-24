#include "stdio.h"
#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TChain.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TBranchObject.h"
#include "TDirectoryFile.h"
#include "TLeafObject.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TVirtualStreamerInfo.h"
#include "TStreamerElement.h"

TString R__GetBranchPointerName(TLeaf* leaf);

int MakeSimpleSelector(TTree* fTree, FILE* fp, const char* classname);

int MakeSimpleSelector(TTree* fTree, const char* fileName);

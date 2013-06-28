///////////////////////////////////////////////////////////////////////
//
//    FILE: .h
//   CLASS: None
// AUTHORS: I. Gonzalez Caballero, A.Y. Rodriguez Marrero
//    DATE: February, 2011
//
// CONTENT: Implements the functionality needed to run an Analysis
//          using the PROOF Analysis Framework (PAF). This file can
//          (should) be compiled.
//
///////////////////////////////////////////////////////////////////////
#ifndef PAFCompiledUtils_h
#define PAFCompiledUtils_h 1


//ROOT Includes
#include "TString.h"
#include "TLeaf.h"
#include "TTree.h"
#include "TProof.h"

// Uncomment next line to get DEBUG information
// + 1 means some debug information
// + 2 means lots of debug information in the Selector related functions
// #define DEBUGUTILS 2


#ifdef DEBUG
#define DEBUGUTILS
#endif

///////////////////////////////////////////////////////////////////////
//
// Functions of general interest
//

/***********************
 *
 * Silent GetFromPipe. Inspired in TSystem::GetFromPipe()
 *
 ************************/
int GetFromPipe(const char* command, TString& out);

//
///////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////
//
// Functions related to the manipulation of selectors. Some of them are
// based on the code in the MakeSelector method in ROOT.
//


/***********************
 *
 * Create a selector of type selectortype from filename.
 *
 ************************/
bool CreateSelector(const char* filename,
		    TString& pkgName,
		    const TString& treeDir,
		    const TString& treeName,
		    const TString& analysis,
		    const vector<TString>& packages);


/************************
 *
 * Create a selector of type selectortype from filename.
 * Selectorpath is the path in which the selector is located
 * and selectorname its name.
 *
 ************************/
bool CreateSelector(const char* filename, 
		    const TString& treeDir,
		    const TString& treeName,
		    const char* selectorpath,
		    const char* selectorname,
		    const TString& analysis,
		    const vector<TString>& packages);


/************************
 *
 * Inherited from MakeSelector
 *
 ************************/
TString R__GetBranchPointerName(TLeaf *leaf);


/************************
 *
 * Almost completely copied from MakeSelector
 *
 ************************/
int MakeSimpleSelector(TTree* fTree, 
		       FILE *fp,
		       const char *classname);

//
///////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////
//
// Functions to deal with the PAR file creation
//

/************************
 *
 * Upload and enable packages / Load packages
 *
 ************************/
void UploadAndEnablePackages(TProof* proofsession, 
			     const vector<TString>& packages,
			     bool isSelector = false);

/************************
 *
 * Check if a PAR file needs to be built
 *
 ************************/
bool ShouldBuildParFile(const TString& dir, const TString& module);

/************************
 *
 * Build par files if they have been modified.
 * If isSelector is true, the original code is in the session dir 
 * This function uses ShouldBuildParFile() to check whether there are
 * files modified after the par file was built
 *
 ************************/
bool BuildParFile(const TString& module, bool isSelector=false);

//
///////////////////////////////////////////////////////////////////////



#endif

/**
	@brief PAF tool class to add a histogram to a selector.
	@file PAFToolAddHisto.cxx
	@class PAFToolAddHisto
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */


// Includes
// + PAF
#include "PAFToolAddHisto.h"
#include "PAFExceptionCommandExpression.h"
// + ROOT
#include "TSystem.h"
#include "TMath.h"
// + C++
#include <fstream>

static const char* PAFToolHistoTypeNames[] = {"None", "F", "D", "All"};

// Some tool hardcoded information
static const char* TOOL_NAME = "addhistogram";
static const char* SHORT_DESCRIPTION = "Adds a histogram to a selector";
static const char* SHORT_NAME = "ah";
static const char* COMMAND_EXPRESSION = "addhistogram|ah [--help] [selectorname F|D hname [htitle] nbins xmin xmax]";
static const char* PARAMETERS_HELP = "\
\"--help\": Show this help\n\
\t\"selectorname\": Name of the selector to be used\n\
\t\"F|D\" type of histogram [TH1F, TH2F]\n\
\t\"hname\": histogram name\n\
\t\"htitle\": histogram title. If skipped it will take the same value as hname\n\
\t\"nbins\": number of bins\n\
\t\"xmin\": minimum value of the x axis\n\
\t\"xmax\": maximum value of the x axis\n\n\
\tIf any of the parameters is not present, it will be asked interactively";

using namespace std;

PAFToolAddHisto::PAFToolAddHisto()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP),
    fSelectorName(""),
    fType(kPAFToolAddHistoNone),
    fHistogramName(""),
    fTitle(""),
    fNBins(-1),
    fXMin(TMath::Infinity()),
    fXMax(-TMath::Infinity())
    
{

}

void PAFToolAddHisto::Dump() const {
  cout << "The selector \"" << fSelectorName << "\" will be modified to add a new histogram with"
       << endl << "the following properties:" << endl;
  cout << "* Type: " << PAFToolHistoTypeNames[fType] << endl;
  cout << "* Name: " << fHistogramName << endl;
  cout << "* Title: " << fTitle << endl;
  cout << "* N. bins: " << fNBins << endl;
  cout << "* X min: " << fXMin << endl;
  cout << "* X max: " << fXMax << endl;
}

bool PAFToolAddHisto::IsDouble(const char* value) const {
  char* rep;
  strtod(value,&rep);
  if (strlen(rep) == 0)
    return true;
  return false;
}

bool PAFToolAddHisto::IsLongInt(const char* value) const {
  char* rep;
  strtold(value,&rep);
  if (strlen(rep) == 0)
    return true;
  return false;
}


bool PAFToolAddHisto::SetHistoType(const char* htype) {
  for (int k = kPAFToolAddHistoNone+1; k < kAll -1; k++) {
    if (TString(htype) == PAFToolHistoTypeNames[k]) {
      fType = (PAFToolHistoType) k;
      return true;
    }
  }
  return false;
}

bool PAFToolAddHisto::SetNBins(const char* nbins) {
  fNBins = atoi(nbins);
  if (fNBins > 0)
    return true;
  return false;
}

bool PAFToolAddHisto::SetXMin(const char* xmin) {
  if (IsDouble(xmin)) {
    fXMin = atof(xmin);
    return true;
  }
  return false;
}

bool PAFToolAddHisto::SetXMax(const char* xmax) {
  if (IsDouble(xmax)) {
    fXMax = atof(xmax);
    return true;
  }
  return false;
}

TString PAFToolAddHisto::GetHeaderFile() const {
  //FIX FIX FIX Implement looking for selector in the $PAFREPOSITORY list of paths
  return TString::Format("packages/%s/%s.h", fSelectorName.Data(), fSelectorName.Data());
}

TString PAFToolAddHisto::GetImplementationFile() const {
  //FIX FIX FIX Implement looking for selector in the $PAFREPOSITORY list of paths
  return TString::Format("packages/%s/%s.C", fSelectorName.Data(), fSelectorName.Data());
}

TString PAFToolAddHisto::AskForParameter(const TString& question,
					 const TString& suggestion) const {


  TString answer("");
  char stranswer[1000]="";
  while (answer == "") {
    cout << question;
    if (suggestion != "")
      cout << "[" << suggestion << "]";
    cout << ": ";
    cin.getline(stranswer,1000);
    answer = stranswer;
    if (answer == "")
      answer = suggestion;
  }

  return answer;
}

void PAFToolAddHisto::AskForParameters() {

  while (fSelectorName == "") {
    // FIX FIX FIX Could try to find a default value out in the packages folder
    fSelectorName = AskForParameter("Selector Name", "");
  }



  while (fType == kPAFToolAddHistoNone) {
    TString message("Histogram type (");
    for (int k = kPAFToolAddHistoNone+1; k < kAll; k++) {
      message += PAFToolHistoTypeNames[k];
      if (k != (kAll -1))
	message += ", ";
    }
    message += ")";
    TString htype = AskForParameter(message, "F");
    SetHistoType(htype.Data());
  }

  while (fHistogramName == "") {
    fHistogramName = AskForParameter("Histogram Name", "");
  }

  while (fTitle == "") {
    fTitle = AskForParameter("Histogram Title", fHistogramName);
  }
  
  while (fNBins < 0) {
    SetNBins(AskForParameter("Number of bins (bigger than 0)", "10").Data());
  }
  
  while (fXMin == TMath::Infinity()) {
    SetXMin(AskForParameter("Mininum value of the X axis", "0").Data());
  }
  
  while (fXMax == -TMath::Infinity()) {
    TString ssug("");
    Double_t sug = fXMin + fNBins;
    ssug+=sug;
    SetXMax(AskForParameter("Maxinum value of the X axis", ssug.Data()).Data());
  }
  
}

void PAFToolAddHisto::ExecuteTool(TList* params)
{
  
  // Process the command line
  Int_t nparams = params->GetSize();
  
  int iparam = 1;
  if (nparams > iparam)
    fSelectorName = GetParameter(params, iparam);
  
  iparam++;
  if (nparams > iparam) {
    TString par = GetParameter(params,iparam);
    if (!SetHistoType(par))
      cerr << "ERROR: Wrong value of for the histogram type \"" << par
	   << "\". Should be F or D" << endl;
  }
  
  iparam++;
  if (nparams > iparam)
    fHistogramName = GetParameter(params, iparam);
  
  // If it is an integer use it as the number of bins. Otherwise the title
  iparam++;
  if (nparams > iparam) {
    TString value4 = GetParameter(params, iparam);
    if (!IsLongInt(value4.Data())) {
      fTitle = value4;
      iparam++;
      if (nparams > iparam) {
	value4 = GetParameter(params, iparam);
	SetNBins(value4.Data());
      }
    }
    else {
      SetNBins(value4.Data());
      fTitle = fHistogramName;
    }
    
  }
  
  
  iparam++;
  if (nparams > iparam) {
    TString par = GetParameter(params,iparam);
    if (!SetXMin(par))
      cerr << "ERROR: Wrong value for the minimum value in the x axis \"" << par
	   << "\"" << endl;
  }
  
  iparam++;
  if (nparams > iparam) {
    TString par = GetParameter(params,iparam);
    if (!SetXMax(par))
      cerr << "ERROR: Wrong value for the maximum value in the x axis \"" << par
	   << "\"" << endl;
  }
  
  // Require the wrong parameters or those not correctly set
  AskForParameters();

  // Show some output
  Dump();

  // Modify selector
  InsertInHeader();
  InsertInImplementation();

}
 
 
bool PAFToolAddHisto::InsertTextInFile(const TString& inputfile, const TString& outputfile,
				       const TString& searchtext, const TString& newtext) const {
  
  // If outputfile string is empty, assume it to be the same as the input file
  bool rewrite = false;
  if (outputfile == "" || outputfile == inputfile)
    rewrite = true;

  //String holding the contents of the file
  TString file; 
  
  // Open a file and read contents into the string declared above
  std::ifstream fileInput(inputfile.Data());
  if (!fileInput)
    return false; //Should probably handle through exceptions
  file.ReadFile(fileInput);
  fileInput.close();
  
  // Insert newtext in front of searchtext
  TString from = searchtext;
  TString to = newtext + "\n  " + searchtext + "\n";
  file.ReplaceAll(from, to);
  
  // Write output to a new file	
  // + If input and output are the same, use a temporary
  TString ofile(outputfile);
  if (rewrite)
    ofile = inputfile + ".tmp";

  // Write to file
  std::ofstream fileOutput(ofile.Data());
  if (!fileOutput)
    return false; //Should probably handle through exceptions
  fileOutput << file.Data();
  fileOutput.flush();
  fileOutput.close();

  // Some file gimnastics
  if (rewrite) {
    TString bakfile = inputfile + ".pafbak";
    // Move original to bak
    gSystem->Rename(inputfile.Data(), bakfile.Data());
    // Move temporary to original
    gSystem->Rename(ofile.Data(), inputfile.Data());
  }

  return true;
}


bool PAFToolAddHisto::InsertInHeader() const {
  // String to be searched for insertion
  TString rep("// %ENDDATAMEMBERS%");

  // String to be inserted
  TString inc("TH1");
  inc += PAFToolHistoTypeNames[fType];
  inc += "* ";
  inc += fHistogramName;
  inc += ";";

  // Define the files to use
  TString ifile = GetHeaderFile();   // Header file


  // Perform the insertion
  if (!InsertTextInFile(ifile, ifile, rep, inc)) {
    cerr << "ERROR: Could not add the histogram to the header file!" << endl;
    return false;
  }

  return true;
}


bool PAFToolAddHisto::InsertInImplementation() const {

  TString ifile = GetImplementationFile();

  if ( ! (InsertInConstructor(ifile) &&
	  InsertInInitialization(ifile) &&
	  InsertInSummary(ifile))) {

    cerr << "ERROR: Could not add the histogram to the implemention file!" << endl;
    gSystem->Unlink(ifile);
    return false;
  }


  return true;
}



bool PAFToolAddHisto::InsertInConstructor(const TString& ifile) const {
  // String to be searched for insertion
  TString rep("// %ENDCONSTRUCTOR%");

  // String to be inserted
  TString inc = TString::Format("%s = 0;", fHistogramName.Data());

  // Perform the insertion
  if (!InsertTextInFile(ifile, ifile, rep, inc)) {
    cerr << "ERROR: Could not initialize histogram in the constructor!" << endl;
    return false;
  }

  return true;
}


bool PAFToolAddHisto::InsertInInitialization(const TString& ifile) const {
  // String to be searched for insertion
  TString rep("// %ENDHISTOINIT%");

  // String to be inserted
  TString inc = TString::Format("%s = CreateH1%s(\"%s\", \"%s\", %i, %f, %f);",
			       	fHistogramName.Data(),
				PAFToolHistoTypeNames[fType],
				fHistogramName.Data(),
				fTitle.Data(),
				fNBins,
				fXMin,
				fXMax);

  // Perform the insertion
  if (!InsertTextInFile(ifile, ifile, rep, inc)) {
    cerr << "ERROR: Could not create the histogram in Initialise()!" << endl;
    return false;
  }

  return true;
}

bool PAFToolAddHisto::InsertInSummary(const TString& ifile) const {

  // String to be searched for insertion
  TString rep("// %ENDSUMMARY%");

  // String to be inserted
  TString inc = TString::Format("%s = FindOutput<TH1%s>(\"%s\");",
			       	fHistogramName.Data(),
				PAFToolHistoTypeNames[fType],
				fHistogramName.Data()
				);

  // Perform the insertion
  if (!InsertTextInFile(ifile, ifile, rep, inc)) {
    cerr << "ERROR: Could not retrieve the histogram in the Summary()!" << endl;
    return false;
  }

  return true;
}
 



/**
	@brief PAF tool class to add a histogram to a selector.
	@file PAFToolCreateSelector.h
	@class PAFToolCreateSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */

#pragma once

#include "PAFAbstractTool.h"

enum PAFToolHistoType {kNone, kF, kD, kAll};

class PAFToolAddHisto : public PAFAbstractTool
{
 public:


  PAFToolAddHisto();
  virtual ~PAFToolAddHisto() {}
  
  virtual void ExecuteTool(TList* params);

  void Dump() const;

  bool IsDouble(const char* value) const;
  bool IsLongInt(const char* value) const;

  bool SetHistoType(const char* htype);
  bool SetNBins(const char* nbins);
  bool SetXMin(const char* xmin);
  bool SetXMax(const char* xmax);


  
 protected:

  TString GetHeaderFile() const;
  TString GetImplementationFile() const;
  TString AskForParameter(const TString& question, const TString& suggestion) const;

  void AskForParameters();

  bool InsertTextInFile(const TString& inputfile, const TString& outputfile,
			const TString& searchtext, const TString& newtext) const;

  bool InsertInHeader() const;
  bool InsertInImplementation() const;
  bool InsertInConstructor(const TString& ifile) const;
  bool InsertInInitialization(const TString& ifile) const;
  bool InsertInSummary(const TString& ifile) const;
  
  
 protected:
  // Data members
  TString          fSelectorName;
  PAFToolHistoType fType;
  TString          fHistogramName;
  TString          fTitle;
  Int_t            fNBins;
  Double_t         fXMin;
  Double_t         fXMax;


  
};

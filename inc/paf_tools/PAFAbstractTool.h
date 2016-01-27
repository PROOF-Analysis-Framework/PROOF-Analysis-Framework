/**
	@brief Abstract class to provides a default implementation of PAFItool.
	@file PAFAbstractTool.h
	@class PAFAbstractTool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

// Includes
// + PaF
#include "PAFITool.h"
// + ROOT
#include "Rtypes.h"
// + C++
#include <iostream>

class PAFAbstractTool : public PAFITool
{
	public:
                PAFAbstractTool(const TString& toolName,
				const TString& shortDescription, 
				const TString& shortToolName,
				const TString& commandExpression,
				const TString& parametersHelp = "");

                // Returns the tool name
		virtual TString GetToolName() const;
		// Returns a shorter accepted version of the tool
		virtual TString GetToolShortName() const;
		// Returns a shorter accepted version of the tool
		virtual TString GetShortDescription() const;
		// Returns help on tool parameters
		virtual TString GetParametersHelp() const;
		// Returns the command expression
		virtual TString GetCommandExpression() const;

		// Print the help message
		virtual std::ostream& PrintHelp(std::ostream& os = std::cout) const;

	protected:
		virtual void Exit(const TString& message, Int_t error = -1);
		virtual TString GetParameter(TList* params, Int_t i) const;
		virtual TString GetParameter(TList* params, const TString& keys, const TString& keyl) const;
		virtual Bool_t ExistsParam(TList* params, const TString& keys, const TString& keyl) const;

		// Printing methods
		virtual std::ostream& PrintMessage(const TString& message, 
						   std::ostream& os = std::cout) const;
		virtual std::ostream& PrintMessage(const char* message, 
						   std::ostream& os = std::cout) const;

		TString	fToolName;           // Tool name
		TString	fShortDescription;   // Short description about the tool
		TString	fToolShortName;      // Tool short name
		TString	fCommandExpression;  // Full command expression
		TString	fParametersHelp;     // Help for the parameters
};

/**
	@brief Interface defining a PAFTool behavior.
	@file PAFITool.h
	@class PAFITool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

// Includes
// + ROOT 
#include "TList.h"
#include "TString.h"
// + C++
#include <iostream>

class PAFITool
{
	public:
                // Returns the tool name
		virtual TString GetToolName() const = 0;
		// Returns a short description of the tool
		virtual TString GetToolShortName() const = 0;
		// Returns a shorter accepted version of the tool
		virtual TString GetShortDescription() const = 0;
		// Returns help on tool parameters
		virtual TString GetParametersHelp() const = 0;
		// Returns the command expression
		virtual TString GetCommandExpression() const = 0;
		// Print the help message
		virtual std::ostream& PrintHelp(std::ostream& os = std::cout) const = 0;


		// Executes the tool with the parameters in the list
		virtual void ExecuteTool(TList* params) = 0;
};

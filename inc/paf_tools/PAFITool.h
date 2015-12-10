/**
	@brief Interface defining a PAFTool behavior.
	@file PAFITool.h
	@class PAFITool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

#include "TList.h"
#include "TString.h"

class PAFITool
{
	public:
		virtual TString GetToolName() = 0;
		virtual TString GetHelpMessage() = 0;
		virtual TString GetCommandExpression() = 0;

		virtual void ExecuteTool(TList* params) = 0;
};

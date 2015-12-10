/**
	@brief PAF tool class to clean the environment used.
	@file PAFToolReset.h
	@class PAFToolReset
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

#include "PAFAbstractTool.h"

#include "TFile.h"
#include "TTree.h"

class PAFToolReset : public PAFAbstractTool
{
	public:
		PAFToolReset();
		virtual ~PAFToolReset();

		virtual void ExecuteTool(TList* params);

	protected:
		static const char* TOOL_NAME;
		static const char* HELP_MESSAGE;
		static const char* COMMAND_EXPRESSION;
};

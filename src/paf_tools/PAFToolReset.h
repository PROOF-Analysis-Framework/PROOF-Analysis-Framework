#pragma once

#include "PAFAbstractTool.h"

#include "TFile.h"
#include "TTree.h"

class PAFToolReset : public PAFAbstractTool
{
	public:
		PAFToolReset();
		virtual ~PAFToolReset();
	
		virtual void Execute(TList* params);
	
	protected:
		static const char* TOOL_NAME;
		static const char* HELP_MESSAGE;
		static const char* COMMAND_EXPRESSION;
};
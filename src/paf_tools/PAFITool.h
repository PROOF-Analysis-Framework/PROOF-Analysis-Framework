#pragma once

#include "TList.h"
#include "TString.h"

class PAFITool
{
	public:
		virtual TString GetToolName() = 0;
		virtual TString GetHelpMessage() = 0;
		virtual TString GetCommandExpression() = 0;
	
		virtual void Execute(TList* params) = 0;
};
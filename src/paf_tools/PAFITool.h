#pragma once

#include "TList.h"
#include "TString.h"

class PAFITool
{
	public:
		virtual ~PAFITool() = 0;
	
		virtual TString GetToolName() = 0;
		virtual TString GetHelp() = 0;
		virtual TString GetCommandExpression() = 0;
	
		virtual void Execute(TList* params) = 0;
};
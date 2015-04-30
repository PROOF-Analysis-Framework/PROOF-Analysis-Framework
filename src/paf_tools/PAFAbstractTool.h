#pragma once

#include "PAFITool.h"

class PAFAbstractTool : public PAFITool
{
	public:
		PAFAbstractTool(TString toolName, TString helpMessage, TString commandExpression);
	
		virtual TString GetToolName();
		virtual TString GetHelpMessage();
		virtual TString GetCommandExpression();
	
	protected:
		virtual TString GetParam(TList* params, int i);
		virtual void PrintMessage(TString& message);
		virtual void PrintMessage(const char* message);
	
		TString fToolName;
		TString fHelpMessage;
		TString fCommandExpression;
};
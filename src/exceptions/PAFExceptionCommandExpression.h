#pragma once

#include "PAFIException.h"

#include "TString.h"

class PAFExceptionCommandExpression : public PAFIException
{
	public:
		PAFExceptionCommandExpression(TString toolName);

		virtual TString GetMessage();
	
	protected:
		TString fToolName;
};
/**
	@brief PAF exception to those cases when the command is not a valid expression.
	@file PAFExceptionCommandExpression.h
	@class PAFExceptionCommandExpression
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

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

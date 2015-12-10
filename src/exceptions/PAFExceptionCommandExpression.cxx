/**
	@brief PAF exception to those cases when the command is not a valid expression.
	@file PAFExceptionCommandExpression.cxx
	@class PAFExceptionCommandExpression
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#include "PAFExceptionCommandExpression.h"

PAFExceptionCommandExpression::PAFExceptionCommandExpression(TString toolName)
	: fToolName(toolName)
{

}

TString PAFExceptionCommandExpression::GetMessage()
{
	return TString::Format("%s command is not a valid expression.", fToolName.Data());
}

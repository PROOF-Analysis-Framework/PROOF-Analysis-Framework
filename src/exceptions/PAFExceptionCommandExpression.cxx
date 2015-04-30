#include "PAFExceptionCommandExpression.h"

PAFExceptionCommandExpression::PAFExceptionCommandExpression(TString toolName)
	: fToolName(toolName)
{

}

TString PAFExceptionCommandExpression::GetMessage()
{
	return TString::Format("%s command is not a valid expression.", fToolName.Data());
}

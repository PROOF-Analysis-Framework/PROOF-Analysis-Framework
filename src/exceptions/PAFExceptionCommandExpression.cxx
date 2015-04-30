#include "PAFExceptionCommandExpression.h"

PAFExceptionCommandExpression::PAFExceptionCommandExpression(TString toolName)
	: fToolName(toolName)
{

}

TString PAFExceptionCommandExpression::GetMessage()
{
	return TString::Format("%s command requires more information.", fToolName.Data());
}

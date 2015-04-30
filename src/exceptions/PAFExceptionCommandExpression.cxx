#include "PAFExceptionCommandExpression.h"

PAFExceptionCommandExpression::PAFExceptionCommandExpression(TString toolName)
	: fToolName(toolName)
{

}

TString PAFExceptionCommandExpression::GetMessage()
{
	return fToolName;
}

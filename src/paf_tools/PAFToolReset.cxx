/**
	@brief PAF tool class to clean the environment used.
	@file PAFToolReset.cxx
	@class PAFToolReset
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#include "PAFToolReset.h"

#include "PAFExceptionCommandExpression.h"

static const char* TOOL_NAME = "reset";
static const char* SHORT_DESCRIPTION = "Resets the PAF environment by closing any session that might be opened and deleting any file created";
static const char* SHORT_NAME = 0;
static const char* COMMAND_EXPRESSION = "reset [-a | --aggresive]";
static const char* PARAMETERS_HELP = "\"-a | --aggresive\" Aggressive cleaning of files in the packages not in the official list. If this is not specified the Makefile and the PROOF-INFO directory are left untouched. Note that unless these files already exist, they are created by PAF.";



PAFToolReset::PAFToolReset()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP)
{

}

PAFToolReset::~PAFToolReset()
{

}

void PAFToolReset::ExecuteTool(TList* params)
{
	int result = 0;

	if(params->GetSize() > 2)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}

	if(params->GetSize() == 1)
	{
		result = system("resetpaf");
	}
	else
	{
		TString param1 = GetParameter(params, 1);
		if(param1.EqualTo("-a") || param1.EqualTo("--aggresive"))
		{
			result = system("resetpaf -a");
		}
		else
		{
			throw PAFExceptionCommandExpression(TOOL_NAME);
		}
	}

	if (result != 0)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}
}

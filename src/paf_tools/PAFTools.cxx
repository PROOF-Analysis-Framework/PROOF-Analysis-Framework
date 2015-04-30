#include "PAFTools.h"

#include "TObjString.h"

#include "PAFToolInspectTree.h"

#include "../exceptions/PAFExceptionCommandExpression.h"

#include <iostream>

int main(int argc, const char* argv[])
{
	PAFTools tools;
	
	tools.Execute(argc, argv);
}

const char* PAFTools::TOOL_NAME = "paf";

const char* PAFTools::HELP_MESSAGE = "paf tools launcher";

const char* PAFTools::COMMAND_EXPRESSION = "paf tool_name [tool_parameters]";


PAFTools::PAFTools()
	: PAFAbstractTool(TOOL_NAME, HELP_MESSAGE, COMMAND_EXPRESSION)
{
	InitMembers();
}

PAFTools::~PAFTools()
{
	
}

void PAFTools::InitMembers()
{
	InitTools();
}

void PAFTools::InitTools()
{
	PAFToolInspectTree* inspectree = new PAFToolInspectTree();
	fTools[inspectree->GetToolName()] = inspectree;
}

void PAFTools::Execute(int argc, const char* argv[])
{
	TList params;
	for(int i = 1; i < argc; i++)
	{
		params.Add(new TObjString(argv[i]));
	}
	Execute(&params);
}

void PAFTools::Execute(TList* params)
{
	if(params->IsEmpty())
	{
		PrintMessage(GetCommandExpression());
		PrintMessage(GetHelpMessage());
		return;
	}
	
	TString param0 = GetParam(params, 0);
	if(param0.EqualTo("-h") || param0.EqualTo("--help"))
	{
		PrintMessage(GetCommandExpression());
		PrintMessage(GetHelpMessage());
		return;
	}

	if(fTools.find(param0) == fTools.end())
	{
		PrintMessage(TString::Format("Tool \"%s\" not found.\n", param0.Data()));
		return;
	}
	
	PAFITool* tool = fTools[param0];
	if(params->GetSize() == 2)
	{
		TString param1 = GetParam(params, 1);
		if (param1.EqualTo("-h") || param1.EqualTo("--help"))
		{
			PrintMessage(tool->GetHelpMessage());
			return;
		}
	}
	
	try
	{
		tool->Execute(params);
	}
	catch (PAFExceptionCommandExpression& ex)
	{
		PrintMessage(ex.GetMessage());
		PrintMessage("Command expression:");
		PrintMessage(tool->GetCommandExpression());
	}
}

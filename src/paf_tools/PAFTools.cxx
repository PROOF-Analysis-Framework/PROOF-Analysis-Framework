/**
	@brief PAF tool executable that holds all paf tools.
	@file PAFTools.cxx
	@class PAFTools
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#include "PAFTools.h"

#include "TObjString.h"

#include "PAFToolInspectTree.h"
#include "PAFToolReset.h"
#include "PAFToolCreateSelector.h"
#include "PAFToolAddHisto.h"

#include "PAFExceptionCommandExpression.h"

#include <iostream>

int main(int argc, const char* argv[])
{
	PAFTools tools;

	tools.ExecuteTool(argc, argv);
}

static const char* TOOL_NAME = "paf";
static const char* SHORT_DESCRIPTION = "PROOF Analysis Framework (PAF) tools launcher";
static const char* SHORT_NAME = "N/A";
static const char* COMMAND_EXPRESSION = "paf [--help] <tool> [tool_parameters]\n\tpaf <tool> --help";
static const char* PARAMETERS_HELP = "N/A";


PAFTools::PAFTools()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP)
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
	PAFITool* inspectree = new PAFToolInspectTree();
	fTools[inspectree->GetToolName()] = inspectree;
	fToolsShort[inspectree->GetToolShortName()] = inspectree;
	
	PAFITool* pafreset = new PAFToolReset();
	fTools[pafreset->GetToolName()] = pafreset;
	
	PAFITool* createselector = new PAFToolCreateSelector();
	fTools[createselector->GetToolName()] = createselector;
	fToolsShort[createselector->GetToolShortName()] = createselector;

	PAFITool* addhisto = new PAFToolAddHisto();
	fTools[addhisto->GetToolName()] = addhisto;
	fToolsShort[addhisto->GetToolShortName()] = addhisto;

}

std::ostream& PAFTools::PrintHelp(std::ostream& os) const
{
        TString name("PROOF Analysis Framework tools command\n\t");
	name += fToolName;
	name += " - ";
	name += fShortDescription;
	name += "\n\n";

	TString usage("USAGE\n\t");
	usage += fCommandExpression;
	usage += "\n\n";

	TString result("\t<tool> can take any of the following values:\n");
	for (std::map<TString, PAFITool*>::const_iterator it = fTools.begin();
                it != fTools.end(); it++)
        {
                PAFITool* tool = it->second;
                result.Append(TString::Format("\t* %s", it->first.Data()));
		if (tool->GetToolShortName() != "")
		  result.Append(TString::Format(" (%s)", tool->GetToolShortName().Data()));
                result.Append(TString::Format(" - %s \n", tool->GetShortDescription().Data()));
        }

	TString final("\n\t'paf <tool> --help' will show more detailed help on each tool\n");

	PrintMessage(name, os);
	PrintMessage(usage, os);
	PrintMessage(result, os);
	PrintMessage(final,os);

	return os;
}

void PAFTools::ExecuteTool(int argc, const char* argv[])
{
	TList params;
	for(int i = 1; i < argc; i++)
	{
		params.Add(new TObjString(argv[i]));
	}
	ExecuteTool(&params);
}

void PAFTools::ExecuteTool(TList* params)
{
	if(params->IsEmpty())
	{
		PrintHelp();
		return;
	}

	TString param0 = GetParameter(params, 0);
	if(param0.EqualTo("-h") || param0.EqualTo("--help"))
	{
		PrintHelp();
		return;
	}

	if(fTools.find(param0) == fTools.end() && 
	   fToolsShort.find(param0) == fToolsShort.end())
	{
		PrintMessage(TString::Format("ERROR: Tool \"%s\" not found.\n", param0.Data()));
		PrintHelp();
		return;
	}

	PAFITool* tool = fTools[param0];
	if (!tool)
	  tool = fToolsShort[param0];
	if(params->GetSize() == 2)
	{
		TString param1 = GetParameter(params, 1);
		if (param1.EqualTo("-h") || param1.EqualTo("--help"))
		{
			tool->PrintHelp();
			return;
		}
	}

	try
	{
		tool->ExecuteTool(params);
	}
	catch (PAFExceptionCommandExpression& ex)
	{
		PrintMessage(ex.GetMessage());
		PrintMessage("Command syntax:");
		PrintMessage(TString::Format("paf %s", tool->GetCommandExpression().Data()));
	}
}

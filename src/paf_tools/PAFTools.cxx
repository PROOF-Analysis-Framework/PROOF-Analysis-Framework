#include "PAFTools.h"

#include "TObjString.h"

#include "PAFToolInspectTree.h"

#include <iostream>

int main(int argc, const char* argv[])
{
	PAFTools tools;
	
	tools.Execute(argc, argv);
}

PAFTools::PAFTools()
{
	InitMembers();
}

PAFTools::~PAFTools()
{
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
		return; //TODO: We should launch PAFTools help.
	}
	
	TString tool = ((TObjString*)params->First())->GetString();
	if(fTools.find(tool) == fTools.end())
	{
		std::cout << "Tool \"" << tool.Data() << "\" not found." << std::endl;
	}
	else
	{
		fTools[tool]->Execute(params);
	}
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

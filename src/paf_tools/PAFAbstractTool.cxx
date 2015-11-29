/**
	@brief Abstract class to provides a default implementation of PAFItool.
	@file PAFAbstractTool.cxx
	@class PAFAbstractTool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */


// Includes
// + PAF
#include "PAFAbstractTool.h"
// + ROOT
#include "TObjString.h"

PAFAbstractTool::PAFAbstractTool(const TString& toolName,
				 const TString& shortDescription, 
				 const TString& shortToolName,
				 const TString& commandExpression,
				 const TString& parametersHelp)

  : fToolName(toolName), 
    fShortDescription(shortDescription),
    fToolShortName(shortToolName),
    fCommandExpression(commandExpression),
    fParametersHelp(parametersHelp)
{
	
}

TString PAFAbstractTool::GetToolName() const
{
	return fToolName;
}

TString PAFAbstractTool::GetToolShortName() const
{
	return fToolShortName;
}

TString PAFAbstractTool::GetShortDescription() const
{
	return fShortDescription;
}

TString PAFAbstractTool::GetCommandExpression() const 
{
	return fCommandExpression;
}

TString PAFAbstractTool::GetParametersHelp() const
{

	return fParametersHelp;
}

void PAFAbstractTool::Exit(const TString& message, Int_t error)
{
        PrintMessage(message.Data(), std::cerr);
	exit(error);
}

TString* PAFAbstractTool::GetParam(TList* params, Int_t i)
{
	return new TString(((TObjString*)params->At(i))->GetString());
}

TString* PAFAbstractTool::GetParam(TList* params, const TString& keys, const TString& keyl)
{
	for (Int_t i = 0; i < params->GetEntries(); i++)
	{
		TString* item = GetParam(params, i);
		if (item->EqualTo(keys) || item->EqualTo(keyl))
		{
			if (i < params->GetEntries() - 1)
			{
				delete item;
				return GetParam(params, i + 1);
			}
		}
		delete item;
	}
	return NULL;
}

Bool_t PAFAbstractTool::ExistsParam(TList* params, const TString& keys, const TString& keyl)
{
	for (Int_t i = 0; i < params->GetEntries(); i++)
	{
		TString* item = GetParam(params, i);
		if (item->EqualTo(keys) || item->EqualTo(keyl))
		{
			delete item;
			return kTRUE;
		}
		delete item;
	}
	return kFALSE;
}

std::ostream& PAFAbstractTool::PrintHelp(std::ostream& os) const
{
	TString name("TOOL\n\t");
	name += fToolName;
	name += " - ";
	name += fShortDescription;
	name += "\n\n";

	TString usage("USAGE\n\tpaf ");
	usage += fCommandExpression;
	usage += "\n\n";

	TString pdescription("PARAMETERS\n\t");
	pdescription += fParametersHelp;
	pdescription += "\n";
	
	PrintMessage(name, os);
	PrintMessage(usage, os);
	PrintMessage(pdescription, os);

	return os;
}


std::ostream& PAFAbstractTool::PrintMessage(const TString& message, std::ostream& os) const
{
        return PrintMessage(message.Data(), os);
}

std::ostream& PAFAbstractTool::PrintMessage(const char* message, std::ostream& os) const
{
	os << message << std::endl;
	return os;
}

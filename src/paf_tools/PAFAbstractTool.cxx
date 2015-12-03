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

TString PAFAbstractTool::GetParameter(TList* params, Int_t i)
{
        TObjString* objstr = (TObjString*) params->At(i);
	if (!objstr)
	  return TString("");
	return TString(objstr->GetString());
}

TString PAFAbstractTool::GetParameter(TList* params, const TString& keys, const TString& keyl)
{
	for (Int_t i = 0; i < params->GetEntries(); i++)
	{
		TString item = GetParameter(params, i);
		if (item.EqualTo(keys) || item.EqualTo(keyl))
		{
			if (i < params->GetEntries() - 1)
			{
				return GetParameter(params, i + 1);
			}
		}
	}
	return TString("");
}


TString* PAFAbstractTool::GetParam(TList* params, Int_t i)
{
        TObjString* objstr = (TObjString*) params->At(i);
	if (!objstr)
	  return 0;
	return new TString(objstr->GetString());
}

TString* PAFAbstractTool::GetParam(TList* params, const TString& keys, const TString& keyl)
{
	for (Int_t i = 0; i < params->GetEntries(); i++)
	{
		TString item = GetParameter(params, i);
		if (item.EqualTo(keys) || item.EqualTo(keyl))
		{
			if (i < params->GetEntries() - 1)
			{
				return GetParam(params, i + 1);
			}
		}
	}
	return NULL;
}

Bool_t PAFAbstractTool::ExistsParam(TList* params, const TString& keys, const TString& keyl)
{
	for (Int_t i = 0; i < params->GetEntries(); i++)
	{
		TString item = GetParameter(params, i);
		if (item.EqualTo(keys) || item.EqualTo(keyl))
		{
			return kTRUE;
		}
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

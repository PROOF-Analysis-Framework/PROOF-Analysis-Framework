/**
	@brief Abstract class to provides a default implementation of PAFItool.
	@file PAFAbstractTool.cxx
	@class PAFAbstractTool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#include "PAFAbstractTool.h"

#include <iostream>

#include "TObjString.h"

PAFAbstractTool::PAFAbstractTool(TString toolName, TString helpMessage, TString commandExpression)
	: fToolName(toolName), fHelpMessage(helpMessage), fCommandExpression(commandExpression)
{
	
}

TString PAFAbstractTool::GetToolName()
{
	return fToolName;
}

TString PAFAbstractTool::GetCommandExpression()
{
	return fCommandExpression;
}

TString PAFAbstractTool::GetHelpMessage()
{
	return fHelpMessage;
}

void PAFAbstractTool::Exit(const TString& message, Int_t error)
{
	PrintMessage(message.Data());
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

void PAFAbstractTool::PrintMessage(TString& message)
{
	PrintMessage(message.Data());
}

void PAFAbstractTool::PrintMessage(const char* message)
{
	std::cout << message << std::endl;
}

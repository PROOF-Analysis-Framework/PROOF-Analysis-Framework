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

TString PAFAbstractTool::GetParam(TList* params, int i)
{
	return ((TObjString*)params->At(i))->GetString();
}

void PAFAbstractTool::PrintMessage(TString& message)
{
	PrintMessage(message.Data());
}

void PAFAbstractTool::PrintMessage(const char* message)
{
	std::cout << message << std::endl;
}


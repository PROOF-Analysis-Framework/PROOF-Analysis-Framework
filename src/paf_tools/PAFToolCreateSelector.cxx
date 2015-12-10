/**
	@brief PAF tool class to create the skeleton selector.
	@file PAFToolCreateSelector.cxx
	@class PAFToolCreateSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */

#include "PAFToolCreateSelector.h"

#include "PAFExceptionCommandExpression.h"

#include "TSystem.h"

#include <fstream>

const char* PAFToolCreateSelector::TOOL_NAME = "createselector";

const char* PAFToolCreateSelector::HELP_MESSAGE = "Creates the skeleton of a selector in the first PAF repository with the name specified.";

const char* PAFToolCreateSelector::COMMAND_EXPRESSION = "createselector selector_name";

const char* PAFToolCreateSelector::PAFREPOSITORIES_ENV = "PAFREPOSITORIES";
const char* PAFToolCreateSelector::PAFPATH_ENV = "PAFPATH";
const char* PAFToolCreateSelector::FIELDS_SEPARATOR = ":";

const char* PAFToolCreateSelector::TEMPLATE_SELECTOR_NAME = "DefaultSelector";
const char* PAFToolCreateSelector::TEMPLATE_EXTENSION = ".in";
const char* PAFToolCreateSelector::HEADER_EXTENSION = ".h";
const char* PAFToolCreateSelector::SOURCE_EXTENSION = ".C";
const char* PAFToolCreateSelector::DIRECTORY = "/";

PAFToolCreateSelector::PAFToolCreateSelector()
	: PAFAbstractTool(TOOL_NAME, HELP_MESSAGE, COMMAND_EXPRESSION)
{

}

PAFToolCreateSelector::~PAFToolCreateSelector()
{

}

void PAFToolCreateSelector::ExecuteTool(TList* params)
{
	if(params->GetSize() != 2)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}

	TString fromString("%NAME%");
	TString* selectorName = GetParam(params, 1);

	TString pathDirectory = TString::Format("%s/etc", gSystem->Getenv(PAFPATH_ENV));
	TString repositoryPaths(gSystem->Getenv(PAFREPOSITORIES_ENV));
	int firstRepositoryLength = repositoryPaths.First(FIELDS_SEPARATOR) == -1 ? repositoryPaths.Length() : repositoryPaths.First(FIELDS_SEPARATOR);
	TString repositoryPath = TString(gSystem->Getenv(PAFREPOSITORIES_ENV), firstRepositoryLength);
	repositoryPath.Append(DIRECTORY).Append(selectorName->Data());
	
	gSystem->mkdir(repositoryPath, kTRUE);

	TString fileNameTemplateHeader = pathDirectory.Copy().Append(DIRECTORY).Append(TEMPLATE_SELECTOR_NAME).Append(HEADER_EXTENSION).Append(TEMPLATE_EXTENSION);
	TString fileNameTargetHeader = repositoryPath.Copy().Append(DIRECTORY).Append(selectorName->Data()).Append(HEADER_EXTENSION);

	TString fileNameTemplateSource = pathDirectory.Copy().Append(DIRECTORY).Append(TEMPLATE_SELECTOR_NAME).Append(SOURCE_EXTENSION).Append(TEMPLATE_EXTENSION);
	TString fileNameTargetSource = repositoryPath.Copy().Append(DIRECTORY).Append(selectorName->Data()).Append(SOURCE_EXTENSION);

	CreateFileTemplated(fileNameTemplateHeader, fileNameTargetHeader, fromString, *selectorName);
	CreateFileTemplated(fileNameTemplateSource, fileNameTargetSource, fromString, *selectorName);
}


void PAFToolCreateSelector::CreateFileTemplated(TString& iFileName, TString& oFileName, TString& from, TString& to)
{
	std::fstream fileInput(iFileName.Data(), std::fstream::in);
	TString file;
	file.ReadFile(fileInput);
	fileInput.close();
	
	file.ReplaceAll(from, to);
	
	std::fstream fileOutput(oFileName.Data(), std::fstream::out);
	fileOutput << file.Data();
	fileOutput.flush();
	fileOutput.close();
}

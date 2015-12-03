/**
	@brief PAF tool class to create the skeleton selector.
	@file PAFToolCreateSelector.cxx
	@class PAFToolCreateSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */


// Includes
// + PAF
#include "PAFToolCreateSelector.h"
#include "PAFExceptionCommandExpression.h"
// + ROOT
#include "TSystem.h"
// + C++
#include <fstream>


// Some tool hardcoded information
static const char* TOOL_NAME = "createselector";
static const char* SHORT_DESCRIPTION = "Creates the skeleton of a selector";
static const char* SHORT_NAME = "cs";
static const char* COMMAND_EXPRESSION = "createselector|cs selector_name";
static const char* PARAMETERS_HELP = "selector_name: Name of the selector (mandatory)";


static const char* PAFREPOSITORIES_ENV = "PAFREPOSITORIES";
static const char* PAFPATH_ENV = "PAFPATH";
static const char* FIELDS_SEPARATOR = ":";

static const char* TEMPLATE_SELECTOR_NAME = "DefaultSelector";
static const char* TEMPLATE_EXTENSION = ".in";
static const char* HEADER_EXTENSION = ".h";
static const char* SOURCE_EXTENSION = ".C";
static const char* DIRECTORY = "/";

PAFToolCreateSelector::PAFToolCreateSelector()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP)
{

}

void PAFToolCreateSelector::ExecuteTool(TList* params)
{
	if(params->GetSize() != 2)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}

	TString fromString("%NAME%");
	TString selectorName = GetParameter(params, 1);

	TString pathDirectory = TString::Format("%s/etc", gSystem->Getenv(PAFPATH_ENV));
	TString repositoryPaths(gSystem->Getenv(PAFREPOSITORIES_ENV));
	int firstRepositoryLength = repositoryPaths.First(FIELDS_SEPARATOR) == -1 ? repositoryPaths.Length() : repositoryPaths.First(FIELDS_SEPARATOR);
	TString repositoryPath = TString(gSystem->Getenv(PAFREPOSITORIES_ENV), firstRepositoryLength);
	repositoryPath.Append(DIRECTORY).Append(selectorName.Data());
	
	gSystem->mkdir(repositoryPath, kTRUE);

	TString fileNameTemplateHeader = pathDirectory.Copy().Append(DIRECTORY).Append(TEMPLATE_SELECTOR_NAME).Append(HEADER_EXTENSION).Append(TEMPLATE_EXTENSION);
	TString fileNameTargetHeader = repositoryPath.Copy().Append(DIRECTORY).Append(selectorName.Data()).Append(HEADER_EXTENSION);

	TString fileNameTemplateSource = pathDirectory.Copy().Append(DIRECTORY).Append(TEMPLATE_SELECTOR_NAME).Append(SOURCE_EXTENSION).Append(TEMPLATE_EXTENSION);
	TString fileNameTargetSource = repositoryPath.Copy().Append(DIRECTORY).Append(selectorName.Data()).Append(SOURCE_EXTENSION);

	CreateFileTemplated(fileNameTemplateHeader, fileNameTargetHeader, fromString, selectorName);
	CreateFileTemplated(fileNameTemplateSource, fileNameTargetSource, fromString, selectorName);
}


void PAFToolCreateSelector::CreateFileTemplated(const TString& iFileName, const TString& oFileName, 
						const TString& from, const TString& to) const
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

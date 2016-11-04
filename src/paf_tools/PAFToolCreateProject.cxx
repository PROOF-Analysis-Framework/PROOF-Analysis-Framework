/**
	@brief PAF tool class to create the skeleton selector.
	@file PAFToolCreateProject.cxx
	@class PAFToolCreateProject
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */


// Includes
// + PAF
#include "PAFToolCreateProject.h"
#include "PAFExceptionCommandExpression.h"
// + ROOT
#include "TSystem.h"
// + C++
#include <fstream>


// Some tool hardcoded information
static const char* TOOL_NAME = "createproject";
static const char* SHORT_DESCRIPTION = "Creates the skeleton of a PAF Project";
static const char* SHORT_NAME = "cp";
static const char* COMMAND_EXPRESSION = "createproject|cp project_name";
static const char* PARAMETERS_HELP = "project_name: Name of the PAF Project (mandatory)";

static const char* PAFPATH_ENV = "PAFPATH";

static const char* TARGETPATH = ".";

static const char* TEMPLATE_SELECTOR_NAME = "DefaultProject";
static const char* TEMPLATE_EXTENSION = ".in";
static const char* SOURCE_EXTENSION = ".C";
static const char* DIRECTORY = "/";

PAFToolCreateProject::PAFToolCreateProject()
  : PAFAbstractTool(TOOL_NAME, SHORT_DESCRIPTION, SHORT_NAME, COMMAND_EXPRESSION, PARAMETERS_HELP)
{

}

void PAFToolCreateProject::ExecuteTool(TList* params)
{
	if(params->GetSize() != 2)
	{
		throw PAFExceptionCommandExpression(TOOL_NAME);
	}

	TString fromString("%NAME%");
	TString selectorName = GetParameter(params, 1);

	TString pathDirectory = TString::Format("%s/etc", gSystem->Getenv(PAFPATH_ENV));

	TString fileNameTemplateSource = pathDirectory.Copy().Append(DIRECTORY).Append(TEMPLATE_SELECTOR_NAME).Append(SOURCE_EXTENSION).Append(TEMPLATE_EXTENSION);
	TString fileNameTargetSource = TString(TARGETPATH).Append(DIRECTORY).Append(selectorName.Data()).Append(SOURCE_EXTENSION);

	CreateFileTemplated(fileNameTemplateSource, fileNameTargetSource, fromString, selectorName);
}


void PAFToolCreateProject::CreateFileTemplated(const TString& iFileName, const TString& oFileName, 
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

/**
	@brief PAF tool class to create the skeleton selector.
	@file PAFToolCreateSelector.h
	@class PAFToolCreateSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */

#pragma once

#include "PAFAbstractTool.h"

class PAFToolCreateSelector : public PAFAbstractTool
{
	public:
		PAFToolCreateSelector();
		virtual ~PAFToolCreateSelector();

		virtual void ExecuteTool(TList* params);

	protected:
		void CreateFileTemplated(TString& iFileName, TString& oFileName, TString& from, TString& to);

	protected:
		static const char* TOOL_NAME;
		static const char* HELP_MESSAGE;
		static const char* COMMAND_EXPRESSION;

		static const char* PAFREPOSITORIES_ENV;
		static const char* PAFPATH_ENV;
		static const char* FIELDS_SEPARATOR;

		static const char* TEMPLATE_SELECTOR_NAME;
		static const char* TEMPLATE_EXTENSION;
		static const char* HEADER_EXTENSION;
		static const char* SOURCE_EXTENSION;
		static const char* DIRECTORY;
};

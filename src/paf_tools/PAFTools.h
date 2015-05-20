/**
	@brief PAF tool executable that holds all paf tools.
	@file PAFTools.h
	@class PAFTools
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

#include "PAFAbstractTool.h"

#include "TList.h"
#include "TString.h"
#include "TApplication.h"

#include <map>

int main(int argc, const char* argv[]);

class PAFTools : public PAFAbstractTool, public TApplication
{
	public:
		PAFTools();
		virtual ~PAFTools();
	
		virtual TString GetHelpMessage();
	
		void Execute(int argc, const char* argv[]);
		void Execute(TList* params);
	
	protected:
		std::map<TString, PAFITool*> fTools;
	
		void InitMembers();
		void InitTools();
	
		static const char* TOOL_NAME;
		static const char* HELP_MESSAGE;
		static const char* COMMAND_EXPRESSION;
};
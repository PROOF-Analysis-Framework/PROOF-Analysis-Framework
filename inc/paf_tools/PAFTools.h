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

class PAFTools : public PAFAbstractTool
{
	public:
		PAFTools();
		virtual ~PAFTools();

		// Print the help message
		virtual std::ostream& PrintHelp(std::ostream& os = std::cout) const;

		void ExecuteTool(int argc, const char* argv[]);
		void ExecuteTool(TList* params);

	protected:
		std::map<TString, PAFITool*> fTools;
		std::map<TString, PAFITool*> fToolsShort;

		void InitMembers();
		void InitTools();
};

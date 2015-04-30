#pragma once

#include "PAFAbstractTool.h"

#include "TList.h"
#include "TString.h"

#include <map>

int main(int argc, const char* argv[]);

class PAFTools : public PAFAbstractTool
{
	public:
		PAFTools();
		virtual ~PAFTools();

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
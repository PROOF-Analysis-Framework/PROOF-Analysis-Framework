#pragma once

#include "PAFITool.h"

#include "TList.h"
#include "TString.h"

#include <map>

int main(int argc, const char* argv[]);

class PAFTools
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
};
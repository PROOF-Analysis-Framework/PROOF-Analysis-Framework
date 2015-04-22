/**
	@brief Class to create a PAFProjectGeneric which should be configured (although it has some default values) and launched to get results. 
	@file PAFProjectGeneric.h
	@class PAFProjectGeneric
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-21
*/

#pragma once

#include "PAFAbstractProject.h"

class PAFProjectGeneric : public PAFAbstractProject
{
	public:
		PAFProjectGeneric();
		PAFProjectGeneric(Long64_t nentries);
		PAFProjectGeneric(PAFIExecutionEnvironment* executionEnvironment);
		PAFProjectGeneric(PAFIExecutionEnvironment* executionEnvironment, Long64_t nentries);
		virtual ~PAFProjectGeneric();
		
		void SetNEntries(Long64_t nentries);
		Long64_t GetNEntries();
		
		void doRun(PAFBaseSelector* selector);      

	protected:
		Long64_t fNEntries;
		
	ClassDef(PAFProjectGeneric, 1);
};

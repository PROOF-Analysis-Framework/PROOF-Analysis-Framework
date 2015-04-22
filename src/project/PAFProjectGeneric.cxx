/**
	@brief Class to create a PAFProjectGeneric which should be configured (although it has some default values) and launched to get results. 
	@file PAFProjectGeneric.cxx
	@class PAFProjectGeneric
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-21
*/

#include "PAFProjectGeneric.h"

ClassImp(PAFProjectGeneric);

PAFProjectGeneric::PAFProjectGeneric()
	: PAFAbstractProject(), fNEntries(0)
{

}

PAFProjectGeneric::PAFProjectGeneric(Long64_t nentries)
	: PAFAbstractProject(), fNEntries(nentries)
{

}

PAFProjectGeneric::PAFProjectGeneric(PAFIExecutionEnvironment* executionEnvironment)
	: PAFAbstractProject(executionEnvironment), fNEntries(0)
{

}

PAFProjectGeneric::PAFProjectGeneric(PAFIExecutionEnvironment* executionEnvironment, Long64_t nentries)
	: PAFAbstractProject(executionEnvironment), fNEntries(nentries)
{

}

PAFProjectGeneric::~PAFProjectGeneric()
{

}

void PAFProjectGeneric::SetNEntries(Long64_t nentries)
{
	fNEntries = nentries;
}

Long64_t PAFProjectGeneric::GetNEntries()
{
	return fNEntries;
}

void PAFProjectGeneric::doRun(PAFBaseSelector* selector)
{
	fExecutionEnvironment->Process(selector, fNEntries);
}

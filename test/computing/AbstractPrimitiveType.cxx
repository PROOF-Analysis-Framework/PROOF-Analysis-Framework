/**rand0
	@brief Abstract PAF test class to provides some common functionality in primitive type tests.
	@file AbstractPrimitiveType.cxx
	@class AbstractPrimitiveType
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-03
 */

#include "AbstractPrimitiveType.h"

#include "PAFManualSettings.h"

#include "TSystem.h"

PAFISettings* AbstractPrimitiveType::GetPAFISettings()
{
	TString* pafPath = new TString("$PAFPATH");
	
	std::vector< TString* >* repositories = new std::vector< TString* >();
	repositories->push_back(new TString(TString::Format("%s/test/selectors_testing", gSystem->Getenv("PAFPATH"))));
	
	return new PAFManualSettings(pafPath, repositories);
}


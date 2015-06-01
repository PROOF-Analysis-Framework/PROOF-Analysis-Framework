/**
	@brief PAF test exception to manage the asserts.
	@file PAFTestExpectedException.cxx
	@class PAFTestExpectedException
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#include "PAFTestExpectedException.h"

PAFTestExpectedException::PAFTestExpectedException(TString type, TString expected, TString value)
	: fType(type), fExpected(expected), fValue(value)
{

}

TString PAFTestExpectedException::GetMessage()
{
	return TString::Format("Expected: <%s> but was <%s>. Type: %s.", fExpected.Data(), fValue.Data(), fType.Data());
}

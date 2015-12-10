/**
	@brief PAF test exception to manage the asserts.
	@file PAFTestExpectedException.h
	@class PAFTestExpectedException
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#pragma once

#include "PAFTestIException.h"

class PAFTestExpectedException : public PAFTestIException
{
	public:
		PAFTestExpectedException(TString type, TString expected, TString value);

		virtual TString GetMessage();

	protected:
		TString fType;
		TString fExpected;
		TString fValue;
};

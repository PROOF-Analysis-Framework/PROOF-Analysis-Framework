/**
	@brief PAF test exception interface.
	@file PAFTestIException.h
	@class PAFTestIException
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#pragma once

#include "TString.h"

class PAFTestIException
{
	public:
		virtual TString GetMessage() = 0;
};

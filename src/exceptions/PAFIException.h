/**
	@brief PAF exception interface.
	@file PAFIException.h
	@class PAFIException
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

#include "TString.h"

class PAFIException
{
	public:
		virtual TString GetMessage() = 0;
};
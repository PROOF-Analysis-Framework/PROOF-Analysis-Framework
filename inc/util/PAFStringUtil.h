/**
	@brief Utility class to deal with strings.
	@file PAFStringUtil.h
	@class PAFStringUtil
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-12
 */

#pragma once

#include "TString.h"
#include <vector>

class PAFStringUtil 
{
	public:
		static std::vector< TString* >* Split(TString* string, const char* cs);
};

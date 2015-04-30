#pragma once

#include "TString.h"

class PAFIException
{
	public:
		virtual TString GetMessage() = 0;
};
/**
	@brief Implementation of PAFILogger with standard output behavior.
	@file PAFConsoleLogger.h
	@class PAFConsoleLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
*/

#pragma once

#include "PAFILogger.h"

class PAFConsoleLogger : public PAFILogger
{
	public:
		virtual void Log(PAFLogLevel level, const char* module, const char* msg);
		virtual void Flush() {}
};

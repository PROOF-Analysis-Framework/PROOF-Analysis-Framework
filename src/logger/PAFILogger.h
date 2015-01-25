/**
	@brief Interface to implement different behaviours of loggers. 
	@file PAFILogger.h
	@class PAFILogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-01-25
*/

#pragma once

#include "PAFLoggerEnum.h"

class PAFILogger
{
	public:
		virtual void Log(PAFLogLevel level, const char* module, const char* msg) = 0;
		virtual void Flush() = 0;
};

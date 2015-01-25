/**
	@brief Implementation of PAFILogger with standard output behavior.
	@file PAFConsoleLogger.h
	@class PAFConsoleLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
*/

#include "PAFConsoleLogger.h"

#include <iostream>

void PAFConsoleLogger::Log(PAFLogLevel level, const char * module, const char * msg)
{
	std::cout << PAFLogLevelStrings[level] << ": [" << module << "] " << msg << std::endl;
}

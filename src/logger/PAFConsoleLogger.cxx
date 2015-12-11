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

// Colors for the different levels copied from https://root.cern.ch/doc/master/MsgLogger_8cxx_source.html
static const char* PAFLogLevelColor[]   = { "\033[34m"      /*Blue       for DEBUG*/,
					    ""              /*Nothing    for INFO*/,
					    "\033[1;31m"    /*Red bold   for WARN*/,
					    "\033[31m"      /*Red        for ERROR*/,
					    "\033[37;41;1m" /*Gray & Red for FATAL*/};

void PAFConsoleLogger::Log(PAFLogLevel level, const char * module, const char * msg)
{
        //std::cout << PAFLogLevelStrings[level] << ": [" << module << "] " << msg << std::endl;
	std::cout 
	  // Change color
	  << PAFLogLevelColor[level]
	  // Print text
	  << PAFLogLevelStrings[level] << ": [" << module << "] " << msg 
	  // Reset color
	  << "\033[0m" 
	  << std::endl;
}

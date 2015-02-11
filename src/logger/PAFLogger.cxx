/**
	@brief Logger singleton to facilitate interaction from PAF.
	@file PAFLogger.cxx
	@class PAFLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
*/

#include "PAFLogger.h"

#include "PAFConsoleLogger.h"

//Default values
PAFILogger* PAFLogger::fLogger = new PAFConsoleLogger();
PAFLogLevel PAFLogger::fLogLevel = DEBUG;

void PAFLogger::Log(PAFLogLevel loglevel, const char* module, const char* msg)
{
	if (loglevel >= PAFLogger::fLogLevel)
	{
		PAFILogger* logger = GetLogger();
		logger->Log(loglevel, module, msg);
	}
}

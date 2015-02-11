/**
	@brief Implementation of PAF which will hold PAF variables and PAF relevant methods.  
	@file PAF.cxx
	@class PAF
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
*/

#include "PAF.h"

#include "logger/PAFLogger.h"

PAFLogger* fLogger = new PAFLogger();

void PAF_DEBUG(const char* module, const char* msg)
{
	fLogger->Log(DEBUG, module, msg);
}

void PAF_INFO(const char* module, const char* msg)
{
	fLogger->Log(INFO, module, msg);
}

void PAF_WARN(const char* module, const char* msg)
{
	fLogger->Log(WARN, module, msg);
}

void PAF_ERROR(const char* module, const char* msg)
{
	fLogger->Log(ERROR, module, msg);
}

void PAF_FATAL(const char* module, const char* msg)
{
	fLogger->Log(FATAL, module, msg);
}

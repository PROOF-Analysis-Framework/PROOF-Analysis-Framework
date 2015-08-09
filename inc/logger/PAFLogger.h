/**
	@brief Logger singleton to facilitate interaction from PAF.
	@file PAFLogger.h
	@class PAFLogger
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
 */

#pragma once

#include "PAFILogger.h"

class PAFLogger
{
	public:
		static void Log(PAFLogLevel loglevel, const char* module, const char* msg);

	protected:
		static PAFILogger* GetLogger() { return fLogger; }
		static void SetLogger(PAFILogger* logger) { fLogger = logger; }

		static PAFLogLevel GetLogLevel() { return fLogLevel; }
		static void SetLogLevel(PAFLogLevel loglevel) { fLogLevel = loglevel; }

	private:
		static PAFILogger* fLogger;
		static PAFLogLevel fLogLevel;
};

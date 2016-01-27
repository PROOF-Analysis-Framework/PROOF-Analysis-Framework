/**
	@brief PAFLogLevel enum and string array to make its translations to string.
	@file PAFLoggerEnum.h
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-01-25
 */

#pragma once

#pragma GCC diagnostic ignored "-Wunused-variable" //To avoid warnings with PAFLogLevelStrings.

enum PAFLogLevel { DEBUG, INFO, WARN, ERROR, FATAL};
static const char* PAFLogLevelStrings[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };

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
  static PAFLogger* GetInstance();

  void Log(PAFLogLevel loglevel, const char* module, const char* msg);
  
  PAFILogger* GetLogger() { return fLogger; }
  void SetLogger(PAFILogger* logger) { fLogger = logger; }
  
  PAFLogLevel GetLogLevel() const { return fLogLevel; }
  void SetLogLevel(PAFLogLevel loglevel) { fLogLevel = loglevel; }
  
 protected:
  PAFLogger();  //Hide constructor to make this class a singleton
  virtual ~PAFLogger();

 protected:
  static PAFLogger*  fTheLogger;
  PAFILogger* fLogger;
  PAFLogLevel fLogLevel;
};

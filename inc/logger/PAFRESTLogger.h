/**
	@brief PAFRESTLogger Operation to interact with the rest api.
	@file PAFRESTLogger.h
	@author I. Gonzalez Caballero, J. Delgado Fernandez, N. Fernandez Alvarez
	@version 1.0
	@date 2016-07-02
 */
#pragma once

#include "PAFILogger.h"
#include "PAFLoggerEnum.h"
#include "TString.h"
#include <map>

class PAFRESTLogger : public PAFILogger{

public:

    virtual void Log(PAFLogLevel level, const char *module, const char *msg);

    virtual void Log(const char *module, const char *msg);

    virtual void Flush();

    static PAFRESTLogger *GetInstance();

    virtual ~PAFRESTLogger();

private:
    PAFRESTLogger();

    virtual void LoadConfiguration();
    virtual void GetNewLogId();
    virtual bool isServerAvailable();
    
    static PAFRESTLogger *instance;
    TString    logId;
    bool 	isServerReachable;
    std::map<TString, TString> properties;

};
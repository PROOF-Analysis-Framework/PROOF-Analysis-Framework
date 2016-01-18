//
// Created by root on 6/01/16.
//

#pragma once

#include "PAFMonitorParameter.h"
#include "TString.h"

class PAFMonitorEvent {

public:
    PAFMonitorEvent();

    virtual ~PAFMonitorEvent() = 0;

    virtual void AddParameter(PAFMonitorParameter *parameter) = 0;

    virtual void SetEventType(TString *eventType) = 0;

    virtual TString* GetEventType() = 0;

protected:
    std::vector<PAFMonitorParameter *> *parameters;
    TString *eventType;

};
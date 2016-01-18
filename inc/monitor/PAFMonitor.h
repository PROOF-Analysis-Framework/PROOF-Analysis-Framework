//
// Created by root on 6/01/16.
//

#pragma once

#include "PAFMonitorEvent.h"

class PAFMonitor {

public:

    PAFMonitor();

    virtual ~PAFMonitor() = 0;

    virtual void RegisterEvent(PAFMonitorEvent *monitorEvent) = 0;

    virtual void SendData() = 0;

    virtual void ClearData() = 0;

protected:
    std::vector<PAFMonitorEvent *> *pafMonitorEvents;
};
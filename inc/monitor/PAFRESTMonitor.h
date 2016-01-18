//
// Created by root on 6/01/16.
//

#pragma once

#include "PAFMonitor.h"

class PAFRESTMonitor : public PAFMonitor {

public:

    PAFRESTMonitor();

    virtual ~PAFRESTMonitor() = 0;

    void RegisterEvent(PAFMonitorEvent *monitorEvent) = 0;

    void SendData() = 0;

    void ClearData() = 0;

};
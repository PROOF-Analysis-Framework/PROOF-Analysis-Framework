//
// Created by root on 6/01/16.
//

#include <PAF.h>
#include <iostream>
#include "PAFMonitor.h"

PAFMonitor::PAFMonitor() {
}

void PAFMonitor::RegisterEvent(PAFMonitorEvent *monitorEvent) {
}

/**
 * This method will send all the data, now it will just print what we have
 */
void PAFMonitor::SendData() {


    for (int i = 0; i < this->pafMonitorEvents->size(); i++) {
        PAF_INFO("PAF MON", this->pafMonitorEvents->at(i)->GetEventType()->Data());
    }
}

void PAFMonitor::ClearData() {
    this->pafMonitorEvents->clear();
}

PAFMonitor::~PAFMonitor() {
    delete pafMonitorEvents;
}
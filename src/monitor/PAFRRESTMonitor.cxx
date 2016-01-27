//
// Created by root on 6/01/16.
//

#include <PAF.h>
#include "PAFRESTMonitor.h"

PAFRESTMonitor::PAFRESTMonitor() {
    this->pafMonitorEvents = new std::vector<PAFMonitorEvent *>();
}

void PAFRESTMonitor::RegisterEvent(PAFMonitorEvent *monitorEvent) {
    this->pafMonitorEvents->push_back(monitorEvent);
}

/**
 * This method will send all the data, now it will just print what we have
 */
void PAFRESTMonitor::SendData() {
    for (unsigned int i = 0; i < pafMonitorEvents->size(); i++) {
        PAF_INFO("PAF MON", this->pafMonitorEvents->at(i)->GetEventType()->Data());
    }
}

void PAFRESTMonitor::ClearData() {
    this->pafMonitorEvents->clear();
}

PAFRESTMonitor::~PAFRESTMonitor() {
    delete pafMonitorEvents;
}
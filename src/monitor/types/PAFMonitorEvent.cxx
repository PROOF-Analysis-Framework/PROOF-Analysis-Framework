//
// Created by root on 6/01/16.
//

#include "PAFMonitorEvent.h"

PAFMonitorEvent::PAFMonitorEvent() {
    this->parameters = new std::vector<PAFMonitorParameter *>();
}

void PAFMonitorEvent::AddParameter(PAFMonitorParameter *parameter) {
    this->parameters->push_back(parameter);
}

void PAFMonitorEvent::SetEventType(TString *eventType) {
    this->eventType = eventType;
}

PAFMonitorEvent::~PAFMonitorEvent() {
    delete parameters;
    delete eventType;
}


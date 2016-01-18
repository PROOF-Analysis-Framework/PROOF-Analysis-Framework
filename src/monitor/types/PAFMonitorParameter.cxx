//
// Created by root on 6/01/16.
//

#include "PAFMonitorParameter.h"

PAFMonitorParameter::PAFMonitorParameter() {

}

void PAFMonitorParameter::SetCode(TString *code) {
    this->Code = code;
}

void PAFMonitorParameter::setValue(TString *value) {
    this->Value = value;
}

PAFMonitorParameter::~PAFMonitorParameter() {
    delete Code;
    delete Value;
}
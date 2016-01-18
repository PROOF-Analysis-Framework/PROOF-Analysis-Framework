//
// Created by root on 6/01/16.
//

#pragma once

#include "TString.h"

class PAFMonitorParameter {

public:

    PAFMonitorParameter();
    virtual ~PAFMonitorParameter() = 0;
    void SetCode(TString *code);

    void setValue(TString *value);

protected:
    TString *Code;
    TString *Value;


};
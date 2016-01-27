/**
	@brief ...
	@file PAFBasicSample.h
	@class PAFBasicSample
	@author I. Gonzalez Caballero, J. Delgado Fernandez, N. Fernández  Álvarez
	@version 1.0
	@date 2015-12-08
 */


#pragma once

#include "PAFAbstractSample.h"
#include "TList.h"
#include "TDirectory.h"
#include "TFile.h"
#include "Rtypes.h"

class PAFBasicSample : public PAFAbstractSample {

public:

    PAFBasicSample();

    PAFBasicSample(TDSet *fDataFiles);

    virtual ~PAFBasicSample();


ClassDef(PAFBasicSample, 1);

};

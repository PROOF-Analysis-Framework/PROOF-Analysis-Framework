/**
	@brief PAFLibrary which will contain libraries to load in environments.
	@file PAFLibrary.h
	@class PAFLibrary
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2014-12-17
*/

#pragma once

#include <TProof.h>
#include <TString.h>

class PAFLibrary {
	public:
		PAFLibrary() : fFileName() {}
		PAFLibrary(const char* fileName) : fFileName(fileName) {}
		virtual ~PAFLibrary() {}
	
		TString GetFileName();
	private:
		TString fFileName;

	ClassDef(PAFLibrary, 1);
};


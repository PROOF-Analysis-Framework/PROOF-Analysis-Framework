/**
	@brief PAF test class to test the AddDataFiles method of PAFProject.
	@file AddDataFiles.h
	@class AddDataFiles
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-02
 */

#pragma once

#include "PAFTest.h"

class AddDataFiles : public PAFTest
{
	public:
		virtual void Initialise();
		virtual void Test();

	protected:
		void CreateROOTFile(const char* fileName, const char* treeName);
};

/**
	@brief PAF tool class to create the skeleton selector.
	@file PAFToolCreateSelector.h
	@class PAFToolCreateSelector
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-05-28
 */

#pragma once

#include "PAFAbstractTool.h"

class PAFToolCreateSelector : public PAFAbstractTool
{
	public:
		PAFToolCreateSelector();
		virtual ~PAFToolCreateSelector() {}

		virtual void ExecuteTool(TList* params);

	protected:
		void CreateFileTemplated(TString& iFileName, TString& oFileName, TString& from, TString& to);

};

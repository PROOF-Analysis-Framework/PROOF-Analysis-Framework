/**
	@brief Abstract class to provides a default implementation of PAFItool.
	@file PAFAbstractTool.h
	@class PAFAbstractTool
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-04-30
 */

#pragma once

#include "PAFITool.h"

#include "Rtypes.h"

class PAFAbstractTool : public PAFITool
{
	public:
		PAFAbstractTool(TString toolName, TString helpMessage, TString commandExpression);

		virtual TString GetToolName();
		virtual TString GetHelpMessage();
		virtual TString GetCommandExpression();

	protected:
		virtual void Exit(const TString& message, Int_t error = -1);
		virtual TString* GetParam(TList* params, Int_t i);
		virtual TString* GetParam(TList* params, const TString& keys, const TString& keyl);
		virtual Bool_t ExistsParam(TList* params, const TString& keys, const TString& keyl);
		virtual void PrintMessage(TString& message);
		virtual void PrintMessage(const char* message);

		TString	fToolName;
		TString	fHelpMessage;
		TString	fCommandExpression;
};

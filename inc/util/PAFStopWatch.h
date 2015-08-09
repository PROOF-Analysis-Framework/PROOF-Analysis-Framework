/**
	@brief Class that allow PAF to take time of some process.
	@file PAFStopWatch.h
	@class PAFStopWatch
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-02-22
 */

#pragma once

#include "TList.h"
#include "TString.h"
#include "TStopwatch.h"
#include "TParameter.h"

class PAFStopWatch 
{
	public:
                PAFStopWatch();
		virtual ~PAFStopWatch();

		virtual void Start();
		virtual void Resume();
		virtual void Stop();

		void TakeTime(const char* key);

		TParameter<double>* GetTimeAt(int index) const;
		TList* GetTimes();
		void PrintTimes() const;

	protected:
		void InitMembers();

		void PrintTime(TParameter<double>* time) const;

	protected:
		TList*		fTimes;
		TStopwatch*	fWatch;

	ClassDef(PAFStopWatch, 1);
};

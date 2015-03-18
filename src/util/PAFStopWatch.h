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

		void Start();
		void Resume();
		void Stop();

		void TakeTime(const char* key);

		TParameter<double>* GetTimeAt(int index);
		TList* GetTimes();
		void PrintTimes();

	protected:
		void InitMembers();
		
		void PrintTime(TParameter<double>* time);

	protected:
		TList*		fTimes;
		TStopwatch*	fWatch;
	
	ClassDef(PAFStopWatch, 1);
};


#pragma once

#include "TList.h"
#include "TString.h"
#include "TStopwatch.h"
#include "TParameter.h"

class PAFStopWatch 
{
	public:
                PAFStopWatch() { InitMembers();}
		virtual ~PAFStopWatch();

		inline void Start();
		inline void Resume();
		inline void Stop();

		void TakeTime(const char* key);

		TParameter<double>* GetTimeAt(int index) const;
		TList* GetTimes() {return fTimes;}
		void PrintTimes() const;

	protected:
		void InitMembers();
		
		void PrintTime(TParameter<double>* time) const;

	protected:
		TList*		fTimes;
		TStopwatch*	fWatch;
	
	ClassDef(PAFStopWatch, 1);
};

void PAFStopWatch::Start()
{
	fWatch->Start(kTRUE);
}
void PAFStopWatch::Resume()
{
	fWatch->Continue();
}

void PAFStopWatch::Stop()
{
	fWatch->Stop();
}

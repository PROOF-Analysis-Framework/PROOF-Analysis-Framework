#include "PAFStopWatch.h"

#include "../PAF.h"

ClassImp(PAFStopWatch);

PAFStopWatch::PAFStopWatch()
{
	InitMembers();
}

PAFStopWatch::~PAFStopWatch()
{
	delete fTimes;
	delete fWatch;
}

void PAFStopWatch::InitMembers()
{
	fTimes = new TList();
	fWatch = new TStopwatch();
}

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

void PAFStopWatch::TakeTime(const char* key)
{
	double timePrevious = 0;
	if(!fTimes->IsEmpty())
	{
		timePrevious = GetTimeAt(fTimes->GetEntries() - 1)->GetVal();
	}
	double time = fWatch->RealTime() - timePrevious;	
	Resume();
	TParameter<double>* result = new TParameter<double>(key, time);
	fTimes->Add(result);
	PrintTime(result);

}

TParameter<double>* PAFStopWatch::GetTimeAt(int index)
{
	return (TParameter<double>*)fTimes->At(index);
}

TList* PAFStopWatch::GetTimes()
{
	return fTimes;
}

void PAFStopWatch::PrintTimes()
{
	for(int i = 0; i < fTimes->GetEntries(); i++)
	{
		PrintTime(GetTimeAt(i));
	}
}

void PAFStopWatch::PrintTime(TParameter<double>* time)
{
	PAF_INFO("PAFStopWatch", TString::Format("%s: %fs", time->GetName(), time->GetVal()));
}


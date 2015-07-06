#include "PAFStopWatch.h"

#include "../PAF.h"

ClassImp(PAFStopWatch);


PAFStopWatch::~PAFStopWatch()
{
  //FIXME FIXME
  //fTimes may need to be iterated to delete the objects contained.
	delete fTimes;
	delete fWatch;
}

void PAFStopWatch::InitMembers()
{
	fTimes = new TList();
	fWatch = new TStopwatch();
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

TParameter<double>* PAFStopWatch::GetTimeAt(int index) const
{
	return (TParameter<double>*)fTimes->At(index);
}


void PAFStopWatch::PrintTimes() const
{
	for(int i = 0; i < fTimes->GetEntries(); i++)
	{
		PrintTime(GetTimeAt(i));
	}
}

void PAFStopWatch::PrintTime(TParameter<double>* time) const
{
	PAF_INFO("PAFStopWatch", TString::Format("%s: %fs", time->GetName(), time->GetVal()));
}


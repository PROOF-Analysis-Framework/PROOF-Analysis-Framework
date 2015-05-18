#include "VariableGetter.h"

ClassImp(VariableGetter)

void VariableGetter::InsideLoop() {
	TString variable = GetParam<TString>("Variable");
	float result = Get<float>("T_METPF_ET");
	SetParam("Result", result);
}

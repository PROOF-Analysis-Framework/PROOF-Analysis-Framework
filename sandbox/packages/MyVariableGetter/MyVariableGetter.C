#include "MyVariableGetter.h"

ClassImp(MyVariableGetter)

void MyVariableGetter::InsideLoop() {
	TString variable = GetParam<TString>("Variable");
	float result = GetFloat("T_METPF_ET");
	SetParam("Result", result);
}

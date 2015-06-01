/**
	@brief PAF test to check the behaviour of VariableContainer with primitive types.
	@file PrimitiveTypes.cxx
	@class PrimitiveTypes
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#include "PrimitiveTypesSerialization.h"

#include "PAF/variable_container/PAFVariableContainer.h"

#include "TBufferXML.h"

int main()
{
	PrimitiveTypesSerialization test;
	return PAFTest::Evaluate(&test);
}

void PrimitiveTypesSerialization::Test()
{
	PAFVariableContainer containerSource;

	containerSource.Add("boolean", kTRUE);
	containerSource.Add("integer", 37);
	containerSource.Add("longint", 90000000000l);
	containerSource.Add("float", 21.1f);
	containerSource.Add("double", 32.754);

	TString containerSourceString = TBufferXML::ConvertToXML(&containerSource);

	PAFVariableContainer* containerRestored = (PAFVariableContainer*)TBufferXML::ConvertFromXML(containerSourceString.Data());

	AssertEquals(kTRUE, containerRestored->Get<bool>("boolean"));
	AssertEquals(37, containerRestored->Get<int>("integer"));
	AssertEquals(90000000000l, containerRestored->Get<long>("longint"));
	AssertEquals(21.1f, containerRestored->Get<float>("float"));
	AssertEquals(32.754, containerRestored->Get<double>("double"));

	delete containerRestored;
}

/**
	@brief PAF test class to check the behaviour of VariableContainer with primitive types.
	@file PrimitiveTypes.cxx
	@class PrimitiveTypes
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#include "PrimitiveTypes.h"

#include "PAFVariableContainer.h"

int main()
{
	PrimitiveTypes test;
	return PAFTest::Evaluate(&test);
}

void PrimitiveTypes::Test()
{
	PAFVariableContainer container;

	container.Add("boolean", kTRUE);
	container.Add("integer", 73);
	container.Add("longint", 2222222222222l);
	container.Add("float", 12.2f);
	container.Add("double", 24.2);
	container.Add("pointer", (void*)&container);

	AssertEquals(kTRUE, container.Get<bool>("boolean"));
	AssertEquals(73, container.Get<int>("integer"));
	AssertEquals(2222222222222l, container.Get<long>("longint"));
	AssertEquals(12.2f, container.Get<float>("float"));
	AssertEquals(24.2, container.Get<double>("double"));
	AssertEquals(&container, container.Get<void*>("pointer"));
}

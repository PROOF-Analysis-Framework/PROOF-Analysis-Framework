/**
	@brief PAF abstract test class to provide some common functions and main method.
	@file PAFTest.cxx
	@class PAFTest
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-01
 */

#include "PAFTest.h"

#include "PAFTestIException.h"
#include "PAFTestExpectedException.h"

#include <iostream>

int PAFTest::Evaluate(PAFTest* test)
{
	int result = 0;
	
	test->Initialise();
	try
	{
		test->Test();
	}
	catch (PAFTestIException& ex)
	{
		std::cout << ex.GetMessage().Data() << std::endl;
		result = -1;
	}
	test->Finalize();
	return result;
}

void PAFTest::Initialise()
{

}

void PAFTest::Test()
{

}

void PAFTest::Finalize()
{

}

void PAFTest::AssertEquals(bool expected, bool value)
{
	if(expected != value)
	{
		TString tExpected (expected ? "True" : "False");
		TString tValue (value ? "True" : "False");

		throw PAFTestExpectedException(TString("bool"), tExpected, tValue);
	}
}

void PAFTest::AssertEquals(int expected, int value)
{
	if(expected != value)
	{
		TString tType("int");
		TString tExpected = TString::Format("%d", expected);
		TString tValue = TString::Format("%d", value);
		
		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

void PAFTest::AssertEquals(long expected, long value)
{
	if(expected != value)
	{
		TString tType("long");
		TString tExpected = TString::Format("%ld", expected);
		TString tValue = TString::Format("%ld", value);
		
		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

void PAFTest::AssertEquals(float expected, float value)
{
	if(expected != value)
	{
		TString tType("float");
		TString tExpected = TString::Format("%f", expected);
		TString tValue = TString::Format("%f", value);

		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

void PAFTest::AssertEquals(double expected, double value)
{
	if(expected != value)
	{
		TString tType("double");
		TString tExpected = TString::Format("%f", expected);
		TString tValue = TString::Format("%f", value);

		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

void PAFTest::AssertEquals(void* expected, void* value)
{
	if(expected != value)
	{
		TString tType("pointer");
		TString tExpected = TString::Format("%p", expected);
		TString tValue = TString::Format("%p", value);

		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

void PAFTest::AssertEquals(TObject* expected, TObject* value)
{
	if(!expected->IsEqual(value))
	{
		TString tType("TObject*");
		TString tExpected(expected->GetTitle());
		TString tValue(value->GetTitle());

		throw PAFTestExpectedException(tType, tExpected, tValue);
	}
}

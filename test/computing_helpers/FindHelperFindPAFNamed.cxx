/**
	@brief PAF test class to test the FindPAFNamed method of FindHelper class in computing_helpers package.
	@file FindHelperFindPAFNamed.cxx
	@class FindHelperFindPAFNamed
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#include "FindHelperFindPAFNamed.h"

#include "PAFFindHelper.h"

#include "TObjString.h"

int main()
{
	FindHelperFindPAFNamed test;
	return PAFTest::Evaluate(&test);
}

void FindHelperFindPAFNamed::Test()
{
	TList* testList = new TList();

	AssertEquals(NULL, PAFFindHelper::FindPAFNamed<void*>(testList, "none"));

	TObjString* obj1 = new TObjString("test_1");
	PAFNamedItem* named1 = new PAFNamedItem("Test1", obj1);
	testList->Add(named1);

	AssertEquals(obj1, PAFFindHelper::FindPAFNamed<TObject*>(testList, "Test1"));
	AssertEquals(NULL, PAFFindHelper::FindPAFNamed<void*>(testList, "test_1"));

	delete named1;
	delete obj1;
	delete testList;
}

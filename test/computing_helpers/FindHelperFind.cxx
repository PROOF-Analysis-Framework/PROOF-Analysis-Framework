/**
	@brief PAF test class to test the Find method of FindHelper class in computing_helpers package.
	@file FindHelperFind.cxx
	@class FindHelperFind
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-08
 */

#include "FindHelperFind.h"

#include "PAF/computing_helpers/PAFFindHelper.h"

#include "TObjString.h"

int main()
{
	FindHelperFind test;
	return PAFTest::Evaluate(&test);
}

void FindHelperFind::Test()
{
	TList* testList = new TList();

	AssertEquals(NULL, PAFFindHelper::Find<void*>(testList, "none"));

	TObjString* obj1 = new TObjString("Test1");
	testList->Add(obj1);

	AssertEquals(obj1, PAFFindHelper::Find<TObject*>(testList, "Test1"));

	TObjString* obj2 = new TObjString("Test2");
	testList->Add(obj2);
	AssertEquals(obj1, PAFFindHelper::Find<TObject*>(testList, "Test1"));
	AssertEquals(obj2, PAFFindHelper::Find<TObject*>(testList, "Test2"));

	testList->Clear();
	AssertEquals(NULL, PAFFindHelper::Find<void*>(testList, "Test1"));
	AssertEquals(NULL, PAFFindHelper::Find<void*>(testList, "Test2"));

	TObjString* obj3 = new TObjString("Test3");
	testList->Add(obj1);
	testList->Add(obj2);
	testList->Add(obj3);
	AssertEquals(obj1, PAFFindHelper::Find<TObject*>(testList, "Test1"));
	AssertEquals(obj2, PAFFindHelper::Find<TObject*>(testList, "Test2"));
	AssertEquals(obj3, PAFFindHelper::Find<TObject*>(testList, "Test3"));

	testList->Remove(obj2);
	AssertEquals(NULL, PAFFindHelper::Find<void*>(testList, "Test2"));

	delete obj3;
	delete obj2;
	delete obj1;
	delete testList;
}

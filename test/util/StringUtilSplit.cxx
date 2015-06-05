/**
	@brief PAF test class to test the split method of strings.
	@file StringUtilSplit.cxx
	@class StringUtilSplit
	@author I. Gonzalez Caballero, J. Delgado Fernandez
	@version 1.0
	@date 2015-06-05
 */

#include "StringUtilSplit.h"

#include "PAF/util/PAFStringUtil.h"

int main()
{
	StringUtilSplit test;
	return PAFTest::Evaluate(&test);
}

void StringUtilSplit::Test()
{
	TString* string1 = new TString("");
	std::vector<TString*>* string1splited = PAFStringUtil::Split(string1, ":");
	AssertEquals(0, string1splited->size());

	TString* string2 = new TString("test");
	std::vector<TString*>* string2splited = PAFStringUtil::Split(string2, ":");
	AssertEquals(1, string2splited->size());
	AssertEquals("test", string2splited->at(0)->Data());

	TString* string3 = new TString("test0:test1");
	std::vector<TString*>* string3splited = PAFStringUtil::Split(string3, ":");
	AssertEquals(2, string3splited->size());
	AssertEquals("test0", string3splited->at(0));
	AssertEquals("test1", string3splited->at(1));

	TString* string4 = new TString("test:");
	std::vector<TString*>* string4splited = PAFStringUtil::Split(string4, ":");
	AssertEquals(1, string4splited->size());
	AssertEquals("test", string4splited->at(0));

	TString* string5 = new TString(":test");
	std::vector<TString*>* string5splited = PAFStringUtil::Split(string5, ":");
	AssertEquals(1, string5splited->size());
	AssertEquals("test", string5splited->at(0));
}

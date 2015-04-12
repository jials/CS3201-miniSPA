#include <cppunit/config/SourcePrefix.h>
#include "PQLEvaluator.h"
#include "TestQueryEvaluator.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void
QueryEvaluatorTest::setUp()
{
}

void
QueryEvaluatorTest::tearDown()
{}


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( QueryEvaluatorTest );
// method to test the constructor
void QueryEvaluatorTest::testConstructor() { 
}

void QueryEvaluatorTest::testIndInSymbols(){
	PQLEvaluator eva; 
	vector<vector<string>> symbols;
	vector<string> line1;
	line1.push_back("assign");
	line1.push_back("aaa");
	symbols.push_back(line1);
	vector<string> line2;
	line2.push_back("stmt");
	line2.push_back("s2");
	symbols.push_back(line2);
	vector<string> line3;
	line3.push_back("variable");
	line3.push_back("v");
	symbols.push_back(line3);

	CPPUNIT_ASSERT_EQUAL(2, eva.indInSymbols("v", symbols));
	CPPUNIT_ASSERT_EQUAL(-1, eva.indInSymbols("while", symbols));

}

void QueryEvaluatorTest::testMerge() {
	PQLEvaluator eva; 
	std::vector<std::string> vec1;
	vec1.push_back("blah");
	vec1.push_back("cs2222");
	vec1.push_back("rt5");
	std::vector<std::string> vec2;
	vec2.push_back("fff");
	vec2.push_back("cs2222");
	vec2.push_back("rrr");
	vec2.push_back("blah");
	std::vector<string> res = eva.merge(vec1, vec2);
	CPPUNIT_ASSERT_EQUAL(0, res.at(0).compare("blah"));
	CPPUNIT_ASSERT_EQUAL(0,res.at(1).compare("cs2222"));
}

void QueryEvaluatorTest::testIsNumber(){
	PQLEvaluator eva;
	string str1 = "345235";
	string str2 = "s3489aaa";
	CPPUNIT_ASSERT(eva.isNumber(str1));
	CPPUNIT_ASSERT(!eva.isNumber(str2));
}

void QueryEvaluatorTest::testIsIn(){
	PQLEvaluator eva; 
	vector<string> vec;
	vec.push_back("first");
	vec.push_back("second");
	vec.push_back("last");
	CPPUNIT_ASSERT(eva.isIn("second",vec));
	CPPUNIT_ASSERT(!eva.isIn("banana",vec));
}

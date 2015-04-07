#include <cppunit/config/SourcePrefix.h>
#include "PQLEvaluator.h"
#include "TestQueryEvaluator.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


PQLEvaluator eva; 
const char* args1[] = {"", "abc", "blah", "xyz"};
std::vector<std::string> vec1(args1, args1 + 4);
const char* args2[] = {"apple", "orange", "pear", "cs3201"};
std::vector<std::string> vec2(args2, args2 + 4);
std::vector<string> res = eva.merge(vec1, vec2);

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

// method to test the assigning and retrieval of grades
void QueryEvaluatorTest::testEvaluate() {

}

void QueryEvaluatorTest::testMerge() {
	CPPUNIT_ASSERT_EQUAL(0,res[6].compare("pear"));
	CPPUNIT_ASSERT_EQUAL(0,res[0].compare(""));
	CPPUNIT_ASSERT_EQUAL(0,res[2].compare("apple"));
}

void QueryEvaluatorTest::testIsIn() {
	CPPUNIT_ASSERT(eva.isIn(res,"cs3201"));
	CPPUNIT_ASSERT(!eva.isIn(res,"banana"));
}
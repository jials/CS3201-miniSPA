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

// method to test the assigning and retrieval of grades
void QueryEvaluatorTest::testEvaluate() {

}

void QueryEvaluatorTest::testMerge() {

	PQLEvaluator eva; 
	const char* args1[] = {"", "abc", "blah", "xyz"};
	std::vector<std::string> vec1(args1, args1 + 4);
	const char* args2[] = {"apple", "orange", "pear", "cs3201"};
	std::vector<std::string> vec2(args2, args2 + 4);
	std::vector<string> res = eva.merge(vec1, vec2);

	for (int i=0;i<vec1.size();i++){
		cout << vec1[i] << endl;
	}

	for (int i=0;i<res.size();i++){
		cout << res[i] << endl;
	}

	CPPUNIT_ASSERT_EQUAL(0,res[6].compare("pear"));
	CPPUNIT_ASSERT_EQUAL(0,res[0].compare(""));
	CPPUNIT_ASSERT_EQUAL(0,res[2].compare("apple"));
}

void QueryEvaluatorTest::testIsIn() {
	PQLEvaluator eva; 
	const char* args2[] = {"apple", "orange", "pear", "cs3201"};
	std::vector<std::string> res(args2, args2 + 4);
	CPPUNIT_ASSERT(eva.isIn("cs3201",res));
	CPPUNIT_ASSERT(!eva.isIn("banana",res));
}
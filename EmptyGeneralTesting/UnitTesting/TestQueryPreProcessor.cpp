#include <cppunit/config/SourcePrefix.h>
#include "PQLPreProcessor.h"
#include "TestQueryPreProcessor.h"
#include <iostream>
#include <string>
#include <vector>

void
QueryPreProcessorTest::setUp()
{}
void
QueryPreProcessorTest::tearDown()
{}


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( QueryPreProcessorTest );
// method to test the constructor
void QueryPreProcessorTest::testConstructor() { 
}

// method to test the assigning and retrieval of grades
void QueryPreProcessorTest::testParse() {
	vector<string> strs;
	PQLPreProcessor processor;
	QueryTreeRoot res = processor.parse(strs,"");
	string str;


	CPPUNIT_ASSERT_EQUAL(str.compare("1"),0);
}
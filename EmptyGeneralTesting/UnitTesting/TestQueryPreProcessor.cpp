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
	strs.push_back("stmt s;");
	strs.push_back("Select a pattern a(_,_\"i\"_)");

	PQLPreProcessor processor;
	QueryTreeRoot res = processor.parse(strs,"");
<<<<<<< HEAD

	string expectedAns = "stmt";
	CPPUNIT_ASSERT_EQUAL(0,expectedAns.compare(res.getSymbol("s")));
=======
	string str;


	CPPUNIT_ASSERT_EQUAL(str.compare("1"),0);
>>>>>>> Kexin-QueryPreprocessor
}
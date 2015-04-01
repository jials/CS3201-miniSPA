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
	cout<<"printing"<<endl;
	cout<<(res.getSymbol("s")) << endl;
	string expectedSymbol = "stmt";
	string expectedPattern = "_\"i\"_"; 
	cout << "TC1" << endl;
	CPPUNIT_ASSERT_EQUAL(0,expectedSymbol.compare(res.getSymbol("s")));
	cout << "TC2" << endl;
	if (res.getPattern()->getChild()->getNextRel() == NULL)
		cout << "NULL found"  << endl;
	else cout << "Correct"  << endl;
	CPPUNIT_ASSERT_EQUAL(0,expectedPattern.compare(res.getPattern()->getChild()->getNextRel()->getName()));
}
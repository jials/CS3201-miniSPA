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
	strs.push_back("Select a such that Follows* (1,a) pattern a(_,_\"i\"_)");

	PQLPreProcessor processor;
	QueryTreeRoot res = processor.parse(strs,"");
	cout<<"printing"<<endl;
	cout<<(res.getSymbol("s")) << endl;
	string expectedSymbol = "stmt";
	string expectedPattern = "_\"i\"_"; 
	string str0="1",str1="a",relation = "follows*";
	cout << "TC1" << endl;
	CPPUNIT_ASSERT_EQUAL(0,expectedSymbol.compare(res.getSymbol("s")));
	cout << "TC2" << endl;
	if (res.getPattern()->getChild()->getNextRel() == NULL)
		cout << "NULL found"  << endl;
	else cout << "Correct"  << endl;
	vector<PQLAttributeNode*> patternChildren = (res.getPattern()->getChild()->getChildren());
	vector<PQLAttributeNode*> suchThatChildren = (res.getSuchThat()->getChild()->getChildren());
	CPPUNIT_ASSERT(res.isValidQuery);
	CPPUNIT_ASSERT_EQUAL(0,expectedPattern.compare(patternChildren[1]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,str1.compare(suchThatChildren[1]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,str0.compare(suchThatChildren[0]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,relation.compare(res.getSuchThat()->getChild()->getName())); cout <<res.getSuchThat()->getChild()->getName()<<endl;
}

void QueryPreProcessorTest::testIsValidName(){
	CPPUNIT_ASSERT(PQLPreProcessor::isValidName("banana"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("12345"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("_apple"));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidName("a12345"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("a123.45"));
}
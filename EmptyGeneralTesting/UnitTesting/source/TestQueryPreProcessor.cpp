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
	strs.push_back("stmt s; assign a");
	strs.push_back("Select a such that Follows* (1,a) pattern a(_,_\"i\"_)");

	PQLPreProcessor processor;
	QueryTreeRoot res = processor.parse(strs,"");
	string expectedSymbol = "stmt";
	string expectedPattern = "_\"i\"_"; 
	string str0="1",str1="a",relation = "follows*";
	CPPUNIT_ASSERT_EQUAL(0,expectedSymbol.compare(res.getSymbol("s")));
	vector<PQLAttributeNode*> patternChildren = (res.getPattern()->getChild()->getChildren());
	vector<PQLAttributeNode*> suchThatChildren = (res.getSuchThat()->getChild()->getChildren());
	CPPUNIT_ASSERT(res.isValidQuery);
	CPPUNIT_ASSERT_EQUAL(0,expectedPattern.compare(patternChildren[1]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,str1.compare(suchThatChildren[1]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,str0.compare(suchThatChildren[0]->getName()));
	CPPUNIT_ASSERT_EQUAL(0,relation.compare(res.getSuchThat()->getChild()->getName())); cout <<res.getSuchThat()->getChild()->getName()<<endl;

	vector<string> strs2;
	strs2.push_back("assign          a;");
	strs2.push_back("Select        a such that   follows (2,           a);");
	string assignment = "assign";

	QueryTreeRoot res2 = processor.parse(strs2,"");
	CPPUNIT_ASSERT(res2.isValidQuery);
	CPPUNIT_ASSERT_EQUAL(0,assignment.compare(res2.getSymbol("a")));

	vector<string> strs3;
	strs3.push_back("assign a;");
	strs3.push_back("Select a such that Uses(_, \"x\")");
	QueryTreeRoot res3 = processor.parse(strs3,"");
	CPPUNIT_ASSERT(res3.isValidQuery); cout<< "assert res3 isValidQuery" <<endl;

	vector<string> strs4;
	strs4.push_back("assign a;");
	strs4.push_back("Select a pattern a(_,_\"x + z\"_);");
	QueryTreeRoot res4 = processor.parse(strs4,"");
	CPPUNIT_ASSERT(res4.isValidQuery); cout<< "assert res4 isValidQuery" <<endl;
}

void QueryPreProcessorTest::testIsValidName(){
	CPPUNIT_ASSERT(PQLPreProcessor::isValidName("banana"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("12345"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("_apple"));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidName("a12345"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidName("a123.45"));
}

void QueryPreProcessorTest::testValidityChecking(){
	vector<string> strs;
	strs.push_back("stmt s; assign a");
	strs.push_back("Select a such that Follows* (1,a) pattern a(_,_\"i\"_)");
	PQLPreProcessor processor;
	QueryTreeRoot res = processor.parse(strs,"");

	CPPUNIT_ASSERT(PQLPreProcessor::isValidSynonym("s",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidSynonym("a",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidSynonym("_\"i\"_",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidSynonym("_",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidSynonym("stmt",&res));

	CPPUNIT_ASSERT(PQLPreProcessor::isValidStmtRef("s",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidStmtRef("_",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidStmtRef("123",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidStmtRef("banana",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidStmtRef("_\"i\"_",&res));

	CPPUNIT_ASSERT(PQLPreProcessor::isValidEntRef("a",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidEntRef("_",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidEntRef("\"apple123\"",&res));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidEntRef("\"apple123#\"",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidEntRef("\"apple123",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidEntRef("apple123\"",&res));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidEntRef("54321",&res));
}

void QueryPreProcessorTest::testIsValidExpressionSpec(){
	CPPUNIT_ASSERT(PQLPreProcessor::isValidExpressionSpec("_"));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidExpressionSpec("_\"x\"_"));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidExpressionSpec("_\"k+j1k\"_"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidExpressionSpec("_\"+\"_"));
	CPPUNIT_ASSERT(PQLPreProcessor::isValidExpressionSpec("_\"Rome\"_"));
	CPPUNIT_ASSERT(!PQLPreProcessor::isValidExpressionSpec("a+b+c")); cout << "preprocessor test finish" << endl;
}
#include "TestSimpleParser.h"
#include "SimpleParser.h"

void
TestSimpleParser::testParse(void)
{
   // CPPUNIT_ASSERT(0 == mTestObj->parse("test;"));

	const char *test1 =
		"PROCEDURE Example{ "
		  "x = z;"
		  "z = 3;"
		 "}";
	CPPUNIT_ASSERT(1 == mTestObj->parse(test1));

	const char *test2 =
		"procedureExample{ "
		  "x = z;"
		 "}";
	//CPPUNIT_ASSERT(0 == mTestObj->parse(test2));

	const char *test3 =
		"procedure Example { "
		  "x = z"
		 "}";
	//CPPUNIT_ASSERT(0 == mTestObj->parse(test3));

	const char *test4 =
		"procedure Example { "
		  "x = z;;"
		  "z = 2;"
		 "}";
	//CPPUNIT_ASSERT(0 == mTestObj->parse(test4));
}

void
TestSimpleParser::testAppendWhiteSpace(void)
{
    string test1 = "test;";
	CPPUNIT_ASSERT("test ; " == mTestObj->appendWhiteSpace(test1));

	const char *test2 =
		"PROCEDURE Example{ "
		  "x =   z;"
		 "}";

	const char *result2 =
		"PROCEDURE Example { "
		  "x = z ; "
		 "} ";

	CPPUNIT_ASSERT(result2 == mTestObj->appendWhiteSpace(test2));

}

void TestSimpleParser::setUp(void)
{
    mTestObj = new SimpleParser();
}

void TestSimpleParser::tearDown(void)
{
    delete mTestObj;
}
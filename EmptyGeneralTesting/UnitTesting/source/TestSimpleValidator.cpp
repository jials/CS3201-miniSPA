#include "TestSimpleValidator.h"
#include "SimpleValidator.h"

void
TestSimpleValidator::testValidate(void)
{

	const char *test0 =
		 "this is a sample that not in simple syntax";
	CPPUNIT_ASSERT(false == mTestObj->validate(test0));

	const char *test1 =
		 "procedure Example {"
		  "x = 2;"
		  "z = 3;"
		  "i = 5;"
		"}";
	CPPUNIT_ASSERT(true == mTestObj->validate(test1));

	const char *test2 =
		 "procedure Example "
		  "x = z;"
		 "}";
	CPPUNIT_ASSERT(false == mTestObj->validate(test2));		//because lack of open bracket in line1

	const char *test3 =
		"PROCEDURE Example{ "
		  "x = z;"
		 "}";
	CPPUNIT_ASSERT(true == mTestObj->validate(test3));

	const char *test4 =
		"procedure Example{x = z;}";
	CPPUNIT_ASSERT(true == mTestObj->validate(test4));

	const char *test5 =
		"procedure Example{ "
		  "x = 2;"
		  "x = z"
		 "}";
	CPPUNIT_ASSERT(false == mTestObj->validate(test5));		//because lack of semi colon in line3

	const char *test6 =
		"procedureExample{ "
		  "x = z"
		 "}";
	CPPUNIT_ASSERT(false == mTestObj->validate(test6));		//because no space after procedure

	const char *test7 =
		"procedure Example{ "
		 "}";	
	CPPUNIT_ASSERT(false == mTestObj->validate(test7));		//because no stmt inside procedure

	const char *test8 =
		"procedure Example{ "
			"x = z"
		 "};";
	CPPUNIT_ASSERT(false == mTestObj->validate(test8));		//because of extra semicolon in line3

	
	const char *test9 =
		"procedure Example{ "
			"x = z"
		 "}"
		 "procedure Example2{ "
			"x = 4"
		 "}";
	CPPUNIT_ASSERT(true == mTestObj->validate(test9));

}

void TestSimpleValidator::setUp(void)
{
    mTestObj = new SimpleValidator();
}

void TestSimpleValidator::tearDown(void)
{
    delete mTestObj;
}
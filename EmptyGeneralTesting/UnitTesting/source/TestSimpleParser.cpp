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
	//CPPUNIT_ASSERT(1 == mTestObj->parse(test1));

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

	const char *test5 =
		"procedure Example { "
		  "x = z + y;"
		 "}";
	//CPPUNIT_ASSERT(1 == mTestObj->parse(test5));

	const char *test6 =
		"procedure Example { "
		  "x = z + y + 33 + k;"
		 "}";
	//CPPUNIT_ASSERT(1 == mTestObj->parse(test6));

	const char *test7 =
		"procedure Example { "
			"while x{"
				"y = 1;"
			"}"
		 "}";
	//CPPUNIT_ASSERT(1 == mTestObj->parse(test7));


	const char *test8 =
		"procedure Example { "
			"while x{"
				"y = 1;"
				"while y {"
					"z = k + y + 2 + 3;"
					"z = k + 1;"
				"}"
			"}"
		 "}";
	//CPPUNIT_ASSERT(1 == mTestObj->parse(test8));

	
	const char *test9 =
		"procedure ABC {"
			  "i=1;"					
			 "b=200 ;"						
				"c= a   ;"					
			"while a"							
			"{"
			   "while beta {"						
					"oSCar  = 1 + beta + tmp;"			
					"while tmp{"					
					  "oSCar = I + k + j1k + chArlie; }"		
				"while x {"					
					"x = x + 1;"					
					"while left {"					
					  "while right {"					
						"Romeo = Romeo + 1;"				
						"b = 0;"					
						"c = delta    + l  + width + Romeo ; }"	
						"while c {"					
						  "c = c +1   	; }" 			
						"x = x+ 1	; }}"				
					  "a=   2; }"					
			   "w = w+1  ;"						
			"}"
			"}";
	CPPUNIT_ASSERT(1 == mTestObj->parse(test9));
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
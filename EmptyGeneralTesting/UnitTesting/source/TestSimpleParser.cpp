#include "TestSimpleParser.h"
#include "SimpleParser.h"

void
TestSimpleParser::testParse(void)
{
    //CPPUNIT_ASSERT(0 == mTestObj->parse());
}

void TestSimpleParser::setUp(void)
{
    mTestObj = new SimpleParser();
}

void TestSimpleParser::tearDown(void)
{
    delete mTestObj;
}
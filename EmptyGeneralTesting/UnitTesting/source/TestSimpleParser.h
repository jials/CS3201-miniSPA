#include <iostream>
#include <string>
#include <list>
#include <cppunit/extensions/HelperMacros.h>
#include <SimpleParser.h>


class TestSimpleParser : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSimpleParser);
    CPPUNIT_TEST(testParse);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testParse(void);

private:

    SimpleParser *mTestObj;
};

 CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestSimpleParser, "TestSimpleParser" );
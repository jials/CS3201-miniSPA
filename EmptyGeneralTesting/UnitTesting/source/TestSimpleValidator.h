#include <iostream>
#include <string>
#include <list>
#include <cppunit/extensions/HelperMacros.h>
#include <SimpleValidator.h>


class TestSimpleValidator : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSimpleValidator);
    CPPUNIT_TEST(testValidate);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testValidate(void);

private:

    SimpleValidator *mTestObj;
};

 CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TestSimpleValidator, "TestSimpleValidator" );
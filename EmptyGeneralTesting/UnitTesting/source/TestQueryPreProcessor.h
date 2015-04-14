#ifndef TestQueryPreProcessor_h
#define TestQueryPreProcessor_h

#include <cppunit/extensions/HelperMacros.h>
class QueryPreProcessorTest : public CPPUNIT_NS::TestFixture 
{
CPPUNIT_TEST_SUITE( QueryPreProcessorTest);
CPPUNIT_TEST( testConstructor );
CPPUNIT_TEST( testParse );
CPPUNIT_TEST( testIsValidName );
CPPUNIT_TEST( testValidityChecking );
CPPUNIT_TEST( testIsValidExpressionSpec );
CPPUNIT_TEST_SUITE_END();
public:
void QueryPreProcessorTest::setUp();
void QueryPreProcessorTest::tearDown();
void testConstructor();
void testParse();
void testIsValidName();
void testValidityChecking();
void testIsValidExpressionSpec();
};

#endif
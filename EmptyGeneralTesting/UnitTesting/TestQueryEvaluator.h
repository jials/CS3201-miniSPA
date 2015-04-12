#ifndef TestEvaluator_h
#define TestEvaluator_h

#include <cppunit/extensions/HelperMacros.h>
class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture 
{
CPPUNIT_TEST_SUITE( QueryEvaluatorTest);
CPPUNIT_TEST( testConstructor );
CPPUNIT_TEST( testIndInSymbols );
CPPUNIT_TEST( testMerge );
CPPUNIT_TEST( testIsNumber );
CPPUNIT_TEST( testIsIn );
//CPPUNIT_TEST( testEvaluateResult );
//CPPUNIT_TEST( testEvaluateSuchThat );
//CPPUNIT_TEST( testEvaluatePattern );
CPPUNIT_TEST_SUITE_END();
public:
void QueryEvaluatorTest::setUp();
void QueryEvaluatorTest::tearDown();
void testConstructor();
void testIndInSymbols();
void testMerge();
void testIsNumber();
void testIsIn();
};
#endif
#ifndef TestEvaluator_h
#define TestEvaluator_h

#include <cppunit/extensions/HelperMacros.h>
class QueryEvaluatorTest : public CPPUNIT_NS::TestFixture 
{
CPPUNIT_TEST_SUITE( QueryEvaluatorTest);
CPPUNIT_TEST( testConstructor );
CPPUNIT_TEST( testParse );
CPPUNIT_TEST_SUITE_END();
public:
void QueryEvaluatorTest::setUp();
void QueryEvaluatorTest::tearDown();
void testConstructor();
void testEvaluate();
void testMerge();
void testIsIn()
};
#endif
#ifndef TestStmtTable_h
#define TestStmtTable_h

#include <cppunit/extensions/HelperMacros.h>

class TestStmtTable : public CPPUNIT_NS::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( TestStmtTable ); 
	CPPUNIT_TEST( testPatternMatching );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testPatternMatching();
private:
	StmtTable *mTestObj;
};
#endif


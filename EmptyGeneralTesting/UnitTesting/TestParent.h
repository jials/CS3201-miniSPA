#ifndef TestParent_h
#define TestParent_h

#include <cppunit/extensions/HelperMacros.h>

class ParentTest : public CPPUNIT_NS::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( ParentTest ); 
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testAssignAndRetrieveGrades );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetParent();
	void testIsParent();
	void testGetChildren();

};
#endif


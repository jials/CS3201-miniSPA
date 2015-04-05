#ifndef TestParent_h
#define TestParent_h

#include <cppunit/extensions/HelperMacros.h>

class TestParent : public CPPUNIT_NS::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( TestParent ); 
	CPPUNIT_TEST( testSetParent );
	CPPUNIT_TEST( testIsParent );
	CPPUNIT_TEST( testGetChildren );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetParent();
	void testIsParent();
	void testGetChildren();

};
#endif


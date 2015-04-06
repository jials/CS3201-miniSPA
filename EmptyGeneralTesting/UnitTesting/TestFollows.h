#ifndef TestFollows_h
#define TestFollows_h

#include <cppunit/extensions/HelperMacros.h>

class FollowsTest : public CPPUNIT_NS::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( FollowsTest ); 
	CPPUNIT_TEST( testSetFollows );
	CPPUNIT_TEST( testIsFollows );
	CPPUNIT_TEST( testGetFollows );
	CPPUNIT_TEST( testGetFollowedBy );
	CPPUNIT_TEST( testGetAllFollows );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testSetFollows();
	void testIsFollows();
	void testGetFollows();
	void testGetFollowedBy();
	void testGetAllFollows();

//private:
	//Follows *mTestObj;

};
#endif
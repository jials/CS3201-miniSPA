#include <cppunit/config/SourcePrefix.h>
#include "Follows.h"
#include "TestFollows.h"

#include <iostream>
#include <string>
#include <vector>

void 
FollowsTest::setUp()
{
}

void 
FollowsTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); 

void FollowsTest::testSetFollows() {
	//Follows fol("");
	//fol.setFollows(3,5); 
	//CPPUNIT_ASSERT(fol.getFollows(5) == 3);

	return;
}

// method to test the assigning and retrieval of grades
void FollowsTest::testIsFollows() {
	Follows fol("");
	//fol.setFollows(2,7);
	//CPPUNIT_ASSERT(fol.isFollows(2, 7) == true);
	//CPPUNIT_ASSERT(fol.isFollows(5, 9) == false);
	
	return;
}

void FollowsTest::testGetFollows() {
	Follows fol("");
	//fol.setFollows(3,4); 
	//CPPUNIT_ASSERT(fol.getFollows(4) == 3);
}

void FollowsTest::testGetFollowedBy() {
	Follows fol("");
	//fol.setFollows(8,9); 
	//CPPUNIT_ASSERT(fol.getFollowedBy(8) == 9);
}

void FollowsTest::testGetAllFollows() {
	Follows fol("");
	//fol.setFollows(10,11); 
	//CPPUNIT_ASSERT(fol.getAllFollows().size() == 5);
}



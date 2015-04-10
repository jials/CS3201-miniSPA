#include <cppunit/config/SourcePrefix.h>
#include "Follows.h"
#include "TestFollows.h"

#include <iostream>
#include <string>
#include <vector>

void 
FollowsTest::setUp()
{
	mTestObj = new Follows();
}

void 
FollowsTest::tearDown()
{
	delete mTestObj;
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FollowsTest ); 

void FollowsTest::testSetFollows() {
	mTestObj->reset();
	mTestObj->setFollows(3,5); 
	CPPUNIT_ASSERT(mTestObj->getFollows(5) == 3);
	mTestObj->reset();
	return;
}

// method to test the assigning and retrieval of grades
void FollowsTest::testIsFollows() {
	mTestObj->reset();
	mTestObj->setFollows(2,7);
	CPPUNIT_ASSERT(mTestObj->isFollows(2, 7) == true);
	CPPUNIT_ASSERT(mTestObj->isFollows(5, 9) == false);
	return;
}

void FollowsTest::testGetFollows() {
	mTestObj->reset();
	mTestObj->setFollows(3,4); 
	CPPUNIT_ASSERT(mTestObj->getFollows(4) == 3);
}

void FollowsTest::testGetFollowedBy() {
	mTestObj->reset();
	mTestObj->setFollows(8,9); 
	CPPUNIT_ASSERT(mTestObj->getFollowedBy(8) == 9);
	mTestObj->reset();
}

void FollowsTest::testGetAllFollows() {
	mTestObj->reset();
	mTestObj->setFollows(10,11);
	CPPUNIT_ASSERT(mTestObj->getAllFollows().size() == 1);
	mTestObj->reset();
}



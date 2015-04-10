#include <cppunit/config/SourcePrefix.h>
#include "Parent.h"
#include "TestParent.h"

#include <iostream>
#include <string>
#include <vector>

void 
ParentTest::setUp()
{
	mTestObj = new Parent();
}

void 
ParentTest::tearDown()
{
	delete mTestObj;
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest ); 

void ParentTest::testSetParent() {
	mTestObj->reset();
	mTestObj->setParent(3,5); 
	CPPUNIT_ASSERT(mTestObj->getParent(5) == 3);
	mTestObj->reset();
	return;
}

// method to test the assigning and retrieval of grades
void ParentTest::testIsParent() {
	mTestObj->reset();
	mTestObj->setParent(2,7);
	CPPUNIT_ASSERT(mTestObj->isParent(2, 7) == true);
	CPPUNIT_ASSERT(mTestObj->isParent(5, 9) == false);
	mTestObj->reset();
	return;
}

void ParentTest::testGetChildren() {
	mTestObj->reset();
	mTestObj->setParent(4,6);
	mTestObj->setParent(4,8);
	mTestObj->setParent(4,10);

	vector<int> children = mTestObj->getChildren(4);
	CPPUNIT_ASSERT(children.size() == 3);
	mTestObj->reset();
	return;
}
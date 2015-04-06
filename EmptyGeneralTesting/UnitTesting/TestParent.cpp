#include <cppunit/config/SourcePrefix.h>
#include "Parent.h"
#include "TestParent.h"

#include <iostream>
#include <string>
#include <vector>

void 
ParentTest::setUp()
{
}

void 
ParentTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ParentTest ); 

void ParentTest::testSetParent() {

	Parent par("");
	par.setParent(3,5); 
	CPPUNIT_ASSERT(par.getParent(5) == 3);

	return;
}

// method to test the assigning and retrieval of grades
void ParentTest::testIsParent() {
	Parent par("");
	par.setParent(2,7);
	CPPUNIT_ASSERT(par.isParent(2, 7) == true);
	CPPUNIT_ASSERT(par.isParent(5, 9) == false);
	
	return;
}

void ParentTest::testGetChildren() {
	Parent par("");
	par.setParent(4,6);
	par.setParent(4,8);
	par.setParent(4,10);

	vector<int> children = par.getChildren(4);
	CPPUNIT_ASSERT(children.size() == 3);

	return;
}
#include <cppunit/config/SourcePrefix.h>
#include "Parent.h"
#include "TestParent.h"

#include <iostream>
#include <string>
#include <vector>

void 
TestParent::setUp()
{
}

void 
TestParent::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TestParent ); 

void TestParent::testSetParent() {

	Parent par;
	par.setParent(3,5);
	CPPUNIT_ASSERT(par.getParent(5) == 3);

	return;
}

// method to test the assigning and retrieval of grades
void TestParent::testIsParent() {
	Parent par;
	par.setParent(2,7);
	CPPUNIT_ASSERT(par.isParent(2, 7) == true);
	CPPUNIT_ASSERT(par.isParent(5, 9) == false);
	
	return;
}

void TestParent::testGetChildren() {
	Parent par;
	par.setParent(2,7);
	par.setParent(2,4);
	par.setParent(2,9);

	vector<int> children = par.getChildren(2);
	CPPUNIT_ASSERT(children.size() == 3);

	return;
}
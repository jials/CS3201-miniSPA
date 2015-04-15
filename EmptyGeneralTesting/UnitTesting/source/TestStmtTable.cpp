#include <cppunit/config/SourcePrefix.h>
#include "StmtTable.h"
#include "TestStmtTable.h"

#include <iostream>
#include <string>
#include <vector>

void 
TestStmtTable::setUp()
{
	mTestObj = new StmtTable();
}

void 
TestStmtTable::tearDown()
{
	delete mTestObj;
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TestStmtTable ); 

void TestStmtTable::testPatternMatching() {
	mTestObj->reset();
	
	mTestObj->insertStmtByCode(ASSIGN, 1, "x = y + 1;", "x");
	mTestObj->insertStmtByCode(WHILE, 2, "while x", "x");
	mTestObj->insertStmtByCode(ASSIGN, 3, "y = 23 + x;", "y");
	mTestObj->insertStmtByCode(ASSIGN, 4, "x = z + y + 2;", "x");
	mTestObj->insertStmtByCode(ASSIGN, 5, "y = x + 21;", "y");
	mTestObj->insertStmtByCode(WHILE, 6, "while y", "y");
	mTestObj->insertStmtByCode(ASSIGN, 7, "q = k + 22", "q");
	mTestObj->insertStmtByCode(ASSIGN, 8, "b = kai + koko + 33", "b");

	map<int, string> result = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "x", "_y+2_", false);
	CPPUNIT_ASSERT(result.size() == 0);

	map<int, string> result2 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "y", "_x_", false);
	CPPUNIT_ASSERT(result2[3] == "y");
	CPPUNIT_ASSERT(result2[5] == "y");
	CPPUNIT_ASSERT(result2.size() == 2);

	map<int, string> result3 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "v", "_x_", true);
	CPPUNIT_ASSERT(result3[3] == "y");
	CPPUNIT_ASSERT(result3[5] == "y");
	CPPUNIT_ASSERT(result3.size() == 2);

	map<int, string> result4 = mTestObj->getAllStatementModifyTuplesWithPattern(WHILE, "v", "_", true);
	CPPUNIT_ASSERT(result4[2] == "x");
	CPPUNIT_ASSERT(result4[6] == "y");
	CPPUNIT_ASSERT(result4.size() == 2);

	map<int, string> result5 = mTestObj->getAllStatementModifyTuplesWithPattern(WHILE, "y", "_", false);
	CPPUNIT_ASSERT(result4[6] == "y");
	CPPUNIT_ASSERT(result5.size() == 1);

	map<int, string> result6 = mTestObj->getAllStatementModifyTuplesWithPattern(WHILE, "x", "_", false);
	CPPUNIT_ASSERT(result6[2] == "x");
	CPPUNIT_ASSERT(result6.size() == 1);

	map<int, string> result7 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "y", "_x+2_", false);
	CPPUNIT_ASSERT(result7.size() == 0);

	map<int, string> result8 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "y", "_x+21_", false);
	CPPUNIT_ASSERT(result8[5] == "y");
	CPPUNIT_ASSERT(result8.size() == 1);

	map<int, string> result9 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "y", "_x+2_", true);
	CPPUNIT_ASSERT(result9.size() == 0);

	map<int, string> result10 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "_", "k", false);
	CPPUNIT_ASSERT(result10.size() == 0);

	map<int, string> result11 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "_", "k+22", false);
	CPPUNIT_ASSERT(result11[7] == "q");
	CPPUNIT_ASSERT(result11.size() == 1);

	map<int, string> result12 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "_", "_ka_", false);
	CPPUNIT_ASSERT(result12.size() == 0);

	map<int, string> result13 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "_", "_koko_", false);
	CPPUNIT_ASSERT(result13[8] == "b");
	CPPUNIT_ASSERT(result13.size() == 1);

	map<int, string> result14 = mTestObj->getAllStatementModifyTuplesWithPattern(ASSIGN, "b", "_", false);
	CPPUNIT_ASSERT(result14[8] == "b");
	CPPUNIT_ASSERT(result14.size() == 1);
}


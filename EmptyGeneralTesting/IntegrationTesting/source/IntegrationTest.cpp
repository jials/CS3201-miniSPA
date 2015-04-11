#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "SimpleParser.h"
#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeRoot.h"
#include "PQLResultNode.h"


using namespace std;

int main(int argc, char* argv[])
{
// Get the top level suite from the registry
CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
CppUnit::TextUi::TestRunner runner;

//parse the SIMPLE soource code into the parser
//Parse();

const char *test2 =
		"procedure Example{ "
		  "x = 2;"
		  "z = 3;"
		  "i = 5;"
		  "y = x;"
		  "z = i;"
		  "x = 10;"
		 "}";

SimpleParser parser;
parser.parse(test2);
vector<string> results;
string query = "assign a; Select a such that Follows(2, a)";
PQLPreProcessor proc;
PQLEvaluator eva;
QueryTreeRoot root;
PQLResultNode* node;
vector<string> a ;
vector<string> finalResults;
string first_token = query.substr(0, query.find("Select"));
string second_token = query.substr(query.find("Select"));
a.push_back(first_token);
a.push_back(second_token);
root = proc.parse(a,"");
eva.evaluateResult(&root);
node = root.getResult();
finalResults = node->getResult();
for(int q = 0 ; q< finalResults.size(); q++){
	results.push_back(finalResults[q]);
}

runner.addTest(suite);
bool wasSucessful = runner.run();


getchar();

return wasSucessful ? 0 : 1;
}
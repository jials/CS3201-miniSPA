#include "TestWrapper.h"
#include "SimpleParser.h"
#include "PQLPreProcessor.h"
#include "PQLEvaluator.h"
#include "QueryTreeRoot.h"
#include "PQLResultNode.h"
#include <fstream>
#include <string>
#include "VarTable.h"
#include "Helpers.h"

using namespace std;

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
	
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
    // ...rest of your code...

	Helpers helper;
	string path = helper.GetExePath();
	path += "\\source.txt";

	std::ifstream file(path);
    std::string str; 
	string line;
    while (std::getline(file, str))
    {
        line += str + "\n";
    }

	SimpleParser parser;
	if(!parser.parse(line)){
		cout << "\nParsing of SIMPLE code fail" << endl;
	}
	

	
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
	try{
	PQLPreProcessor proc;
	Helpers helper;
	PQLEvaluator eva;
	QueryTreeRoot root;
	PQLResultNode* node;
	vector<string> a ;
	vector<string> finalResults;
	string first_token = query.substr(0, helper.toLower(query).find("select"));
	string second_token = query.substr(helper.toLower(query).find("select"));
	a.push_back(first_token);
	a.push_back(second_token);
	root = proc.parse(a,"");
	eva.evaluateResult(&root);
	node = root.getResult();
	finalResults = node->getResult();
	
	for(int q = 0 ; q< finalResults.size(); q++){
		if(finalResults[q] == "none") return;
		results.push_back(finalResults[q]);
		
	}
	}
	catch(const exception& error){
		cout << "error";
	}


	



	

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}


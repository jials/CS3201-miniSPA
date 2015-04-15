#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "TNode.h"
#include "AST.h"

TNode* AST::root;

void AST::setRoot(TNode* _root){
	root = _root;
}



void draw(TNode* node, int level){
	string type;
	switch (node -> type)
    {
        case PROGRAM:   type = "PROGRAM"; break;
		case VARIABLE:   type = "VARIABLE"; break;
		case PROCEDURE:   type = "PROCEDURE"; break;
		case ASSIGN:   type = "ASSIGN"; break;
		case CONSTANT:   type = "CONSTANT"; break;
		case STMTLST:   type = "STMTLST"; break;
		case PLUS:   type = "PLUS"; break;
		case WHILE:   type = "WHILE"; break;
    }

	string tabs;
	int currentLevel = level;
	while(currentLevel>0){
		tabs += "  ";
		currentLevel--;
	}

	cout <<  tabs + type;
	if(node->info != ""){
		cout << "("+ node -> info + ")";
	}
	if(node->lineNumber > 0){
		cout << ":" << node -> lineNumber;
	}
	cout << "\n";
	vector<TNode*> children = node -> getChildren();
	if(children.size()>0){
		for(int i =0; i<= children.size()-1; i++){
			draw(children[i], level+1);
			//return;
		}
	}
}

void AST::drawAst(){
	cout << "\n---------------------------------------------------------\n";
	cout << "AST";
	cout << "\n-------------------\n";
	draw(root, 0);
	cout << "\n---------------------------------------------------------\n";
}




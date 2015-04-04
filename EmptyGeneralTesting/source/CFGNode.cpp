#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "CFGNode.h"
int CFGNode::getStatementNum(){
	return CFGNode::statNum;
}
void CFGNode::addChild(CFGNode nextNode){
	//std::cout<<""
	std::vector<CFGNode> childrenList = CFGNode::children;
	children.push_back(nextNode);
}
std::vector<CFGNode> CFGNode::getChildren(){
	return CFGNode::children;
}
void CFGNode::printInfo(){
	std::cout<<"this Node is "<<this->getStatementNum()<<std::endl;
	std::vector<CFGNode> childrenList=this->getChildren();
	std::cout<<"it has "<<childrenList.size()<<" children."<<std::endl;
	for(unsigned i=0; i<childrenList.size(); i++) {
    /* std::cout << *it; ... */
		std::cout<<"child "<<i+1<<" : "<<childrenList.at(i).getStatementNum()<<std::endl;
	}
}
int test(){
	CFGNode node1 = CFGNode(1);
	CFGNode node2 = CFGNode(2);
	CFGNode node3 = CFGNode(3);
	std::cout<<"node1 is "<<node1.getStatementNum()<<std::endl;
	//std::cout<<"node1 is "<<node1<<std::endl;
	std::cout<<"node2 is "<<node2.getStatementNum()<<std::endl;
	//std::cout<<"node2 is "<<node2<<std::endl;
	std::cout<<"node3 is "<<node3.getStatementNum()<<std::endl;
	node1.addChild(node2);
	node1.addChild(node3);
	node1.printInfo();
	return 0;
}
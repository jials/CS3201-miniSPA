
class CFGNode{
public:
	 
	CFGNode(int num){
		statNum = num; 
	}
	void addChild(CFGNode nextNode);
	int getStatementNum();
	std::vector<CFGNode> getChildren();
	//std::ostream& operator<<(std::ostream &strm,const CFGNode &thisNode){
	//	return strm<<"statNum: "<<statNum<<std::endl;
	//}
	void printInfo();
private:
	std::vector<CFGNode> children;
	int statNum;
};
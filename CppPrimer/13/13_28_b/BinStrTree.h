#pragma once
#include"TreeNode.h"
class BinStrTree
{
public:
	BinStrTree(TreeNode *pNode = new TreeNode);
	BinStrTree(const BinStrTree &t);
	~BinStrTree();
	BinStrTree& operator=(BinStrTree& t);
	TreeNode& getRoot()const{ return *root; }
private:
	TreeNode* root;
};
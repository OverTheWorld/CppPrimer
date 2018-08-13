#include "BinStrTree.h"


BinStrTree::BinStrTree(TreeNode* pNode):
root(pNode)
{
}

BinStrTree::BinStrTree(const BinStrTree &t):
root(new TreeNode(*t.root))
{
}

BinStrTree::~BinStrTree()
{
	if (this->root)
		delete root;
}

BinStrTree& BinStrTree::operator=(BinStrTree &t)
{
	TreeNode *pTempRoot = new TreeNode;
	*pTempRoot = *t.root;
	if (this->root)
		delete this->root;
	this->root = pTempRoot;
	return *this;
}
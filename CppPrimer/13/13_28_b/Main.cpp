#include"BinStrTree.h"

int main()
{

	TreeNode *ptn1 = new TreeNode("root");
	ptn1->setLeft("root-Left");
	ptn1->setRight("root-Right");
	if (ptn1->hasLeft())
	{
		ptn1->getLeft().setLeft("root-Left-Left");
		ptn1->getLeft().setRight("root-Left-Right");
	}
	if (ptn1->hasRight())
	{
		ptn1->getRight().setRight("root-Right-Right");
		ptn1->getRight().setLeft("root-Right-Left");
	}
	BinStrTree t(ptn1);
	t.getRoot().PreOrder([](string &value){cout << value << " "; });
	cout << endl;
	BinStrTree t1 = t;
	t1.getRoot().setValue("thisIsT1Root");
	BinStrTree t2;
	t2 = t;
	t2.getRoot().setValue("thisIsT2Root");
	t1.getRoot().PreOrder([](string &value){cout << value << " "; });
	cout << endl;
	t.getRoot().PreOrder([](string &value){cout << value << " "; });
	cout << endl;
	t2.getRoot().PreOrder([](string &value){cout << value << " "; });
	cout << endl;
	t.getRoot().PreOrder([](string &value){cout << value << " "; });
	cout << endl;

	system("pause");
}
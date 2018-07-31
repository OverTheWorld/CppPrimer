#include<iostream>
#include<string>
#include<stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::runtime_error;

class TreeNode
{
public:
	using traFunc = void (*)(string & value);
	TreeNode(const string &s = string()):
		value(s),count(0),
		left(nullptr),right(nullptr){}
	TreeNode(const TreeNode& tn):
		value(tn.value),count(tn.count),
		left((tn.left == nullptr?nullptr:(new TreeNode(*tn.left)))),
		right((tn.right == nullptr?nullptr:(new TreeNode(*tn.right))))
		{}
	~TreeNode()
	{
		if(left)delete left;
		if(right)delete right;
	}
	TreeNode& operator=(TreeNode& tn)
	{
		TreeNode *tempLeft = new TreeNode(*tn.left);
		TreeNode *tempRight = new TreeNode(*tn.right);
		if(left)delete left;
		if(right)delete right;
		value = tn.value;
		count = tn.count;
		left = tempLeft;
		right = tempRight;
		return *this;
	}
	bool hasLeft()const {return left != nullptr;}
	bool hasRight()const {return right != nullptr;}
	TreeNode& getLeft()const 
	{
		if(left == nullptr)
		{
			throw runtime_error("空引用！");
		}
		return *left;
	}
	TreeNode& getRight()const
	{
		if(right == nullptr)
		{
			throw runtime_error("空引用！");
		}
		return *right;
	}
	bool setLeft(const string &value)
	{
		try
		{
		if(left == nullptr)
			left = new TreeNode(value);
		else
			this->value = value;
		}catch(const std::bad_alloc &e)
		{
			return false;
		}
		return true;
	}
	bool setRight(const string &value)
	{
		try
		{
		if(right == nullptr)
			right = new TreeNode(value);
		else
			this->value = value;
		}catch(const std::bad_alloc &e)
		{
			return false;
		}
		return true;
	}
	void PreOrder(traFunc pFunc)
	{
		pFunc(value);
		if(left)left->PreOrder(pFunc);
		if(right)right->PreOrder(pFunc);
	}
	void setValue(const string &s)
	{
		value = s;
	}
	string getValue()const {return value;}
private:
	string 		value;
	int 		count;
	TreeNode	*left;
	TreeNode	*right;
};

int main()
{
	TreeNode tn1("root");
	tn1.setLeft("root-Left");
	tn1.setRight("root-Right");
	if(tn1.hasLeft())
	{
		tn1.getLeft().setLeft("root-Left-Left");
		tn1.getLeft().setRight("root-Left-Right");
	}
	if(tn1.hasRight())
	{
		tn1.getRight().setRight("root-Right-Right");
		tn1.getRight().setLeft("root-Right-Left");
	}
	TreeNode tn2 = tn1;
	tn2.setValue(string("Cretaeing copy func"));
	TreeNode tn3;
	tn3 = tn1;
	tn3.setValue(string("copy operator"));
	tn1.PreOrder([](string &value){cout<<value<<" ";});
	cout<<endl;
	tn2.PreOrder([](string &value){cout<<value<<" ";});
	cout<<endl;
	tn3.PreOrder([](string &value){cout<<value<<" ";});
	cout<<endl;
}
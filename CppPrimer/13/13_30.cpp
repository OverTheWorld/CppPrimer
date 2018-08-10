//这个有一点要注意的就是：在VS2013上，不能保证总是会使用swap来进行交换。CSDN上有一篇文章讲的是只有在元素超过30的情况下，VS2013编译器才会选择使用swap来进行交换

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<time.h>
#include<stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class HasPtr{
	friend void swap(HasPtr &,HasPtr &);
	friend bool operator<(HasPtr &lhs,HasPtr &rhs);
	public:
		HasPtr(const string &s = string()):
			ps(new string(s)),i(0){}
		HasPtr(const HasPtr &s):
			ps(new string(s.getStr())),i(s.getI()){}
		void Print()const
		{
			cout<<*ps<<endl<<i<<endl;
		}
		string getStr()const{return *ps;}
		void setStr(const string &str){*ps = str;}
		int getI()const {return i;}
		void setI(int i){this->i = i;}
	private:
		string *ps;
		int i;
};

inline void swap(HasPtr &lhs,HasPtr &rhs)
{
	using std::swap;
	swap(lhs.i,rhs.i);
	swap(lhs.ps,rhs.ps);
	cout<<"swap"<<endl;
}
bool operator<(HasPtr &lhs,HasPtr &rhs)
{
	return lhs.getStr()<rhs.getStr();
}

HasPtr getPtr(const string &s)
{
	HasPtr ptr(s);
	ptr.Print();
	return ptr;
}

int main()
{
	
	srand(time(nullptr));
	getPtr("string").Print();
	vector<HasPtr> vechptr;
	for(int i = 0;i != 50;++i)
	{
		string strtemp;
		for(int i = 0;i!=5;++i)
		{
			strtemp += 'a'+rand()%26;
		}
		vechptr.push_back(strtemp);
	}
	for_each(vechptr.cbegin(),vechptr.cend(),[](const HasPtr &lhs){cout<<lhs.getStr()<<" ";});
	cout<<endl;
	sort(vechptr.begin(),vechptr.end());
	for_each(vechptr.cbegin(),vechptr.cend(),[](const HasPtr &lhs){cout<<lhs.getStr()<<" ";});
	cout<<endl;
}
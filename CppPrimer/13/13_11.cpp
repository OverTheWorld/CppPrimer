#include<iostream>
#include<string>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class HasPtr{
	public:
		HasPtr(const string &s = string()):
			ps(new string(s)),i(0){}
		HasPtr(const HasPtr &s):
			ps(new string(s.getStr())),i(s.getI()){}
		~HasPtr()
		{
			delete ps;
		}
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

HasPtr getPtr(const string &s)
{
	HasPtr ptr(s);
	ptr.Print();
	return ptr;
}

int main()
{
	getPtr("string").Print();
}
#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::vector;
using std::istream;
using std::ostream;

struct Account
{
	
	Account(int aa,int bb):a(aa),b(bb){}
	
	friend ostream& print(ostream& os,const Account& acc);
	friend ostream& printOnlycd(ostream& os);
	private:
		int a;
		int b;
		static const int c = 2;
		static int d;
};
const int Account::c;
int Account::d = 5;
ostream& print(ostream& os,const Account& acc)
{
	os <<"a:"<<acc.a<<endl
	<<"b:"<<acc.b<<endl
	<<"c:"<<acc.c<<endl
	<<"d:"<<acc.d<<endl;
	
	return os;
}

ostream& printOnlycd(ostream& os)
{
	os << "c:" <<Account::c<<endl
	<<"d:"<<Account::d<<endl;
	
	return os;
}

int main()
{
	printOnlycd(cout);
	Account acc(12,13);
	print(cout,acc);
	
	return 0;
}
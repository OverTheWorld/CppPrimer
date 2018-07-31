#include<iostream>
using std::cout;
using std::cin;
using std::endl;

struct X{
	X(){cout<<"X()"<<endl;}
	X(const X&){cout<<"X(const X&)"<<endl;}
	~X(){cout<<"~X()"<<endl;}
};

int main()
{
	X t1;
	X t2 = t1;
}
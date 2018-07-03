#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void f()
{
	cout<<"parameter is void"<<endl;
}
void f(int i)
{
	cout<<"parameter is int , value is "<< i <<endl;
}
void f(int i,int j)
{
	cout<<"parameter is int and int,value is "<<i<<" and "<<j<<" respectively"<<endl;
}
void f(double i,double j = 3.14)
{
	cout<<"parameter is double and double ,value is "<<i<<" and "<<j<<" respectively"<<endl;
}

int main()
{
//	f(2.56,42);
	f(42);
	f(42,0);
	f(2.56,3.14);
	return 0;
}
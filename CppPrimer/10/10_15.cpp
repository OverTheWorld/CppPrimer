#include<iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int sz = 100;
	auto f = [sz](int a){return a+sz;};
	cout<<f(1)<<endl;
}
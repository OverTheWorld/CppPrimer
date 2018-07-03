#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	auto f = [](int a,int b){return a+b;};
	cout<<f(1,2);
	return 0;
}
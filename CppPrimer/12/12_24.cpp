#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	char *p = new char[20];
	cin>>p;
	cout<<p<<endl;
	delete [] p;
}
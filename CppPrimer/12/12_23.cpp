#include<iostream>
#include<string.h>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

char* catstr(const char* str1,const char* str2)
{
	int len = strlen(str1)+strlen(str2)+1;
	int len1 = strlen(str1);
	char *p = new char[len]();
	int i = 0;
	while(i != strlen(str1))
	{
		p[i] = str1[i];
		++i;
	}
	while(i!=len)
	{
		p[i] = str2[i-len1];
		++i;
	}
	return p;
}
int main()
{
	char str1[10],str2[10];
	cin>>str1>>str2;
	auto p = catstr(str1,str2);
	cout<<p<<endl;
	delete p;
	string sstr1(str1),sstr2(str2);
	cout<<sstr1+sstr2<<endl;
}
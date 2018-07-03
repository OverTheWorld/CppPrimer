#include<iostream>
#include<string>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;


int main()
{
	string str;
	list<string> listStr;
	while(cin>>str)
	{
		listStr.push_back(str);
	}
	for(auto iter = listStr.cbegin();iter != listStr.cend();++iter)
	{
		cout<<*iter<<endl;
	}
}
#include<iostream>
#include<string>
#include<deque>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::deque;


int main()
{
	string str;
	deque<string> deStr;
	while(cin>>str)
	{
		deStr.push_back(str);
	}
	for(auto iter = deStr.cbegin();iter != deStr.cend();++iter)
	{
		cout<<*iter<<endl;
	}
}
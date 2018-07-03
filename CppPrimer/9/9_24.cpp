#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main()
{
	vector<string> vecStr;
	string str;
	
	while(cin>>str)
	{
		vecStr.push_back(str);
	}
	if(!vecStr.empty())
	{
		cout<<vecStr.front()<<endl;
		cout<<vecStr.at(0)<<endl;
		cout<<*vecStr.begin()<<endl;
		cout<<vecStr[0]<<endl;
	}
	return 0;
}
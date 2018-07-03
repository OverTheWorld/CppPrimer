#include<iostream>
#include<string>
#include<vector>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::vector;
using std::string;

int main()
{
	list<const char*> listChars = {"123","456","789","000"};
	vector<string> vecStr(listChars.begin(),listChars.end());
	
	for(const auto &s : vecStr)
	{
		cout<<s<<endl;
	}
	return 0;
}

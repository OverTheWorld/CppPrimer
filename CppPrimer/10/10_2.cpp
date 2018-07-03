#include<iostream>
#include<list>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::string;

int main()
{
	list<string> listStr;
	string str[5] = {"123","123123","345","765","34435"};
	srand(time(nullptr));
	for(int i = 0;i!=30;++i)
	{
		listStr.push_back(str[rand()%5]);
	}
	for(const auto &s:listStr)
		cout<<s<<" ";
	cout<<endl;
	int iCount = count(listStr.cbegin(),listStr.cend(),"123");
	cout<<iCount<<endl;
}
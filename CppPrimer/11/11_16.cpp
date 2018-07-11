#include<iostream>
#include<string>
#include<map>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::string;

int main()
{
	map<string,int> mapPerson;
	string str;
	int num;
	while(cin>>str)
	{
		cin>>num;
		mapPerson[str] = num;
	}
	for(const auto &s : mapPerson)
	{
		cout<<s.first<<" : "<<s.second<<endl;
	}
	int i = mapPerson.cbegin()->second;
	cout<<i<<endl;
}
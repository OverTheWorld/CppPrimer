//Program:				family name and childs
//Program Process:		implement add a family and add child
//						map<string,vector<string>> families;
//						addFamily(families,string,vector<string>);
//						addChild(families,family,childname);

#include<iostream>
#include<string>
#include<vector>
#include<map>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::map;
using std::string;

void addFamily(map<string,vector<string>> &mapFamily,const string &family,const vector<string> &vecStr)
{
	mapFamily[family] = vecStr;
}

void addChild(map<string,vector<string>> &mapFamily,const string &family,const string &childname)
{
	mapFamily[family].push_back(childname);
}

int main()
{
	vector<string> vecStr;
	map<string,vector<string>> mapFamily;
	vecStr.push_back("Jerry");
	vecStr.push_back("John");
	addFamily(mapFamily,"Tom",vecStr);
	for(const auto &s : mapFamily)
	{
		cout<<s.first<<": ";
		for(const auto &u:s.second)
		{
			cout<<u<<" ";
		}
		cout<<endl;
	}
	addChild(mapFamily,"Tom","123");
		for(const auto &s : mapFamily)
	{
		cout<<s.first<<": ";
		for(const auto &u:s.second)
		{
			cout<<u<<" ";
		}
		cout<<endl;
	}
}
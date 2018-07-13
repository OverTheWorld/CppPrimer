//需要依赖11_33_infileRule.txt和11_33_infileText.txt两个文件，请放在同一文件夹下
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::ifstream;
using std::unordered_map;

unordered_map<string,string> getTransMap(ifstream &ifs)
{
	unordered_map<string,string> unorderTransMap;
	string strKey,strValue;
	while(ifs>>strKey&&getline(ifs,strValue))
	{
		unorderTransMap[strKey] = strValue.substr(1);
	}
	return unorderTransMap;
}

string transText(const string &str,const unordered_map<string,string> &unorderTransMap)
{
	istringstream iss(str);
	ostringstream oss;
	unordered_map<string,string>::const_iterator iter;
	string strTemp;
	bool bFirst = true;
	while(iss>>strTemp)
	{
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			oss<<" ";
		}
		if((iter = unorderTransMap.find(strTemp)) != unorderTransMap.end())
		{
			oss<<iter->second;
		}
		else
			oss<<strTemp;
	}
	return oss.str();
}

void transWords(ifstream &fileRule,ifstream &fileText)
{
	auto TransMap = getTransMap(fileRule);
	string line;
	while(getline(fileText,line))
	{
		cout<<transText(line,TransMap)<<endl;
	}
}

int main()
{
	transWords(ifstream("11_33_infileRule.txt"),ifstream("11_33_infileText.txt"));
}
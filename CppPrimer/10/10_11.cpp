#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::vector;

void Print(const vector<string> &vecStr)
{
	for(const auto &s : vecStr)
	{
		cout<<s<<" ";
	}
	cout<<endl;
}

bool isShorter(const string & str1,const string &str2)
{
	return str1.size()<str2.size();
}

int main()
{
	vector<string> vecStr;
	string line,str;
	ifstream ifs("infile.txt",std::ios::in);
	istringstream iss;
	getline(ifs,line);
	iss.str(line);
	while(iss>>str)
	{
		vecStr.push_back(str);
	}
	Print(vecStr);
	sort(vecStr.begin(),vecStr.end(),isShorter);
	Print(vecStr);
	auto end_unique = unique(vecStr.begin(),vecStr.end());
	Print(vecStr);
	vecStr.erase(end_unique,vecStr.end());
	Print(vecStr);
}
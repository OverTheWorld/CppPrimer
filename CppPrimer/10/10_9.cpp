#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>

using std::ifstream;
using std::vector;
using std::string;
using std::istringstream;
using std::cout;
using std::cin;
using std::endl;

void Print(const vector<string> &vecStr)
{
	for(const auto &s : vecStr)
	{
		cout<<s<<" ";
	}
	cout<<endl;
}

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	vector<string> vecStr;
	string str;
	getline(ifs,str);
	istringstream iss;
	iss.str(str);
	string strTemp;
	while(iss>>strTemp)
	{
		vecStr.push_back(strTemp);
	}
	Print(vecStr);
	sort(vecStr.begin(),vecStr.end());
	Print(vecStr);
	auto end_unique = unique(vecStr.begin(),vecStr.end());
	Print(vecStr);
	vecStr.erase(end_unique,vecStr.end());
	Print(vecStr);
}
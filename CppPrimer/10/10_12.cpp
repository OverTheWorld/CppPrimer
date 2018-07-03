#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::vector;
using std::string;

void Print(const vector<string> &vecStr)
{
	for(const auto &s : vecStr)
	{
		cout<<s<<" ";
	}
	cout<<endl;
}

bool isBigerThanFive(const string &str)
{
	return str.size()>=5;
}

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	istringstream iss;
	vector<string> vecStr;
	string line,str;
	getline(ifs,line);
	iss.str(line);
	while(iss>>str)
	{
		vecStr.push_back(str);
	}
	Print(vecStr);
	auto end_par = partition(vecStr.begin(),vecStr.end(),isBigerThanFive);
	Print(vecStr);
	vecStr.erase(end_par,vecStr.end());
	Print(vecStr);
}
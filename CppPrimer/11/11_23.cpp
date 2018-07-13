#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::multimap;
using std::string;
using std::vector;
using std::istringstream;

int main()
{
	ifstream ifs("11_23_infile.txt");
	istringstream iss;
	string line,str,strTemp;
	vector<string> vecStr;
	multimap<string,vector<string>> mapFamily;
	while(getline(ifs,line))
	{
		iss.str(line);
		iss>>str;
		while(iss>>strTemp)
		{
			vecStr.push_back(strTemp);
		}
		mapFamily.insert({str,vecStr});
		vecStr.clear();
		iss.clear();
	}
	for(const auto & s : mapFamily)
	{
		cout<<s.first<<" : ";
		for(const auto &u : s.second)
		{
			cout<<u<<" ";
		}
		cout<<endl;
	}
}
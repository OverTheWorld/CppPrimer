#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<fstream>
#include<sstream>
#include<algorithm>

using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;

int main()
{
	ifstream ifs("11_14_infile.txt");
	map<string,vector<pair<string,string>>> mapFamily;
	vector<pair<string,string>> vecPar;
	istringstream iss(ifs);
	string line,str;
	string str1,str2;
	while(getline(ifs,str))
	{
		while(getline(ifs,line))
		{
			if(line.empty())break;
			iss.str(line);
			iss>>str1;
			iss>>str2;
			vecPar.push_back(make_pair(str1,str2));
			iss.clear();
		}
		mapFamily[str] = vecPar;
		vecPar.clear();
	}
	for_each(mapFamily.cbegin(),mapFamily.cend(),
	[](const pair<string,vector<pair<string,string>>> &par)
	{
		cout<<par.first<<" : "<<endl;
		for_each(par.second.cbegin(),par.second.cend(),
		[](const pair<string,string> &pa)
		{
			cout<<pa.first<<" : "<<pa.second<<endl;
		}
		);
		cout<<endl;
	}
	);
}
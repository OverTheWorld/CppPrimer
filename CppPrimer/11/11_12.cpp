#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<utility>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::pair;

int main()
{
	ifstream ifs("11_12_infile.txt");
	string str;
	vector<pair<string,int>> vecPar;
	int i;
	while(ifs >> str)
	{
		ifs >> i;
		vecPar.push_back(make_pair(str,i));
	}
	for_each(vecPar.cbegin(),vecPar.cend(),
	[](const pair<string,int>& s)
		{
			cout<<s.first<<" : "<<s.second<<endl;
		}
	);
}
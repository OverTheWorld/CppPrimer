#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<functional>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::istringstream;
using namespace std::placeholders;

bool bCountString(const string &str,size_t sz)
{
	if(str.size()>=sz)return true;
	return false;
}

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	istringstream iss;
	vector<string> vecStr;
	string line,str;
	getline(ifs,line);
	iss.str(line);
	const size_t sz = 5;
	while(iss>>str)
	{
		vecStr.push_back(str);
	}
	auto end_countif = count_if(vecStr.cbegin(),vecStr.cend(),bind(bCountString,_1,sz));
	cout<<end_countif<<endl;
}
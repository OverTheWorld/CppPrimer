#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<functional>
#include<iterator>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::istringstream;
using namespace std::placeholders;

bool isBigger(const string &str,size_t sz)
{
	return str.size()>= sz?true:false;
}

int main()
{
	vector<string> vecStr;
	ifstream ifs("infile.txt",std::ios::in);
	istringstream iss;
	string line,str;
	getline(ifs,line);
	iss.str(line);
	auto bIter = back_inserter(vecStr);
	
	while(iss>>str)
	{
		bIter = str;
	}
	const size_t sz = 5;
	auto end_parIter = partition(vecStr.begin(),vecStr.end(),bind(isBigger,_1,sz));
	for_each(vecStr.begin(),end_parIter,[](const string &str){cout<<str<<" ";});
	cout<<endl;
}
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;


int main()
{
	vector<string> vecStr;
	string str;
	ifstream ifs("./infile.txt",ifstream::in);
	while(getline(ifs,str))
	{
		vecStr.push_back(str);
	}
	for(const auto &s:vecStr)
	{
		cout<<s<<endl;
	}
	return 0;
}
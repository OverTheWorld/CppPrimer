#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int main()
{
	vector<string> vecStr;
	string str;
	ifstream ifs("./infile.txt",ifstream::in);
	while(ifs>>str)
	{
		vecStr.push_back(str);
	}
	for(const auto &s:vecStr)
	{
		cout<<s<<endl;
	}
	return 0;
}
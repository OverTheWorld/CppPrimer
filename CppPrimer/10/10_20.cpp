#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::istringstream;
using std::string;
using std::vector;
using std::ifstream;

int main()
{
	vector<string> vecStr;
	istringstream iss;
	ifstream ifs("infile.txt",std::ios::in);
	string line,str;
	getline(ifs,line);
	iss.str(line);
	while(iss>>str)
	{
		vecStr.push_back(str);
	}
	int sz = 5;
	auto iCount = count_if(vecStr.cbegin(),vecStr.cend(),[sz](const string &str)->bool{if(str.size()>=5)return true;else return false;});
	cout<<iCount<<endl;
}
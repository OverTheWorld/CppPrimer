#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::istringstream;
using std::ifstream;

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
	auto sz = 5;
	auto end_par = partition(vecStr.begin(),vecStr.end(),[sz](const string &str){return str.size()>=sz;});
	for(auto iter = vecStr.cbegin();iter != end_par;++iter)
		cout<<*iter<<" ";
	cout<<endl;
}
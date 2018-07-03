#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

int main()
{
	vector<string> vecStr;
	ifstream ifs("infile.txt",std::ios::in);
	istringstream iss;
	string line,str;
	getline(ifs,line);
	iss.str(line);
	while(iss>>str)
	{
		vecStr.push_back(str);
	}
	vector<string>::size_type sz = 5;
	auto end_FindIf = vecStr.begin();
	while((end_FindIf = find_if(end_FindIf,vecStr.end(),[sz](const string& str){return str.size()>=sz;})) != vecStr.end())
	{
		cout<<*end_FindIf++<<" ";
	}
	cout<<endl;
	cout<<"for_each example as follows:"<<endl;
	for_each(vecStr.cbegin(),vecStr.cend(),[sz](const string &str){if(str.size()>=sz)cout<<str<<" ";});
	cout<<endl;
}
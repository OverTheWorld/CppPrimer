#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::vector;
using std::begin;
using std::end;

struct PersonInfo
{
	string strName;
	vector<string> vecStr;
};

int main()
{
	vector<PersonInfo> vecPer;
	PersonInfo per;
	fstream ifs("./infile.txt",fstream::in);
	fstream ofs("./outfile.txt",fstream::out);
	istringstream iss;
	ostringstream oss;
	string str;
	while(getline(ifs,str))
	{
		iss.str(str);
		iss>>str;
		per.strName = str;
		while(iss>>str)
		{
			per.vecStr.push_back(str);
		}
		vecPer.push_back(per);
		per.vecStr.clear();
		iss.clear();
	}
	for(const auto &perInfo:vecPer)
	{
		oss.str(str);
		oss << perInfo.strName<<" ";
		if(perInfo.vecStr.size())
		{
			for(const auto &strNum:perInfo.vecStr)
			{
				oss<<strNum<<" ";
			}
		}
		else 
		{
			oss <<"DataWrong";
		}
		ofs<<oss.str()<<endl;
	}
	
	return 0;
}
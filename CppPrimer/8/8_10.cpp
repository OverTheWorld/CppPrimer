#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::istream;
using std::ostream;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::vector;

int main()
{
	vector<string> vecStr;
	fstream ifs("infile.txt",fstream::in);
	fstream ofs("outfile.txt",fstream::out);
	istringstream iss;
	string str;
	while(getline(ifs,str))
	{
		vecStr.push_back(str);
	}
	cout<<vecStr.size()<<endl;
	for(const auto s:vecStr)
	{
		iss.str(s);
		while(iss>>str)
		{
			ofs<<str<<endl;
		}
		iss.clear();
	}
	return 0;
}
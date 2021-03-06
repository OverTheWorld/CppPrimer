#include<iostream>
#include<string>
#include<stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::out_of_range;

string FindAlpha(const string& s)
{
	string str;
	auto pos = s.find_first_of("1234567890");
	if(pos != string::npos)
	{
		str = str + s.at(pos);
		while((pos = s.find_first_of("1234567890",pos+1)) != string::npos)
		{
			str = str + s.at(pos);
		}
	}
	return str;
}
string FindNumber(const string &s)
{
	string str;
	auto pos = s.find_first_not_of("1234567890");
	if(pos != string::npos)
	{
		str.append(1,s.at(pos));
		while((pos = s.find_first_not_of("1234567890",pos+1)) != string::npos)
		{
			str.append(1,s.at(pos));
		}
	}
	return str;
}

int main()
{
	string str("ab2c3d7R4E6");
	try{
		cout<<FindAlpha(str)<<endl;
		cout<<FindNumber(str)<<endl;
	}
	catch(out_of_range err)
	{
		cerr<<err.what()<<endl;
		cerr<<"执行失败!"<<endl;
	}
	return 0;
}
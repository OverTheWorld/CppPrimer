#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

string& addStr(string &s,const string &preStr,const string &lastStr)
{
	s.insert(s.begin(),preStr.begin(),preStr.end());
	s.append(lastStr);
	return s;
}

int main()
{
	string str("Jack");
	cout<<addStr(str,"Mr "," Jr")<<endl;
	return 0;
}
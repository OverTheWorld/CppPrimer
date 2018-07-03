#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

string& addStr(string &s,const string &preStr,const string &lastStr)
{
	return s.insert(s.insert(0,preStr).size(),lastStr);
}

int main()
{
	string str("Jack");
	cout<<addStr(str,"Mr "," Jr")<<endl;
	return 0;
}
#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

inline bool isShorter(const string &str1,const string &str2)
{
	return str1.size()<str2.size();
}

int main()
{
	string str1,str2;
	cin>>str1>>str2;
	cout<<to_string(isShorter(str1,str2))<<endl;
	return 0;
}
#include"StrVec.h"
#include<iostream>
#include<fstream>
#include<algorithm>
using std::string;
using std::ifstream;
using std::cout;
using std::endl;

int main()
{
	ifstream ifs("input.txt");
	string str;
	StrVec strvec;
	for (int i = 0; i != 5; ++i)
	{
		ifs >> str;
		strvec.push_back(str);
	}
	for_each(strvec.begin(), strvec.end(), [](const string & str) {cout << str << endl; });
	cout << endl;
	StrVec strvec1(strvec);
	while (ifs >> str)
	{
		strvec1.push_back(str);
	}
	for (auto iter = strvec.begin(); iter != strvec.end(); ++iter)
	{
		cout << *iter<<" ";
	}
	cout << endl;
	for_each(strvec1.begin(), strvec1.end(), [](const string& str) {cout << str << " "; });
	cout << endl;

	cout << endl;
	cout << "initializer_list:" << endl;
	StrVec strvec2({ "string1","Initializer","_______","list" });
	for_each(strvec2.begin(), strvec2.end(), [](const string & str) {cout << str << " "; });
	cout << endl;
	system("pause");
}
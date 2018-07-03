#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	vector<int> v1,v2(10),v3(10,42),v4{10},v5{10,42};
	vector<string> v6{10},v7{10,"hi"};
	
	cout<<"a:"<<v1.size()<<endl;
	cout<<"b:"<<v2.size()<<endl;
	cout<<"c:"<<v3.size()<<endl;
	cout<<"d:"<<v4.size()<<endl;
	cout<<"e:"<<v5.size()<<endl;
	cout<<"f:"<<v6.size()<<endl;
	cout<<"g:"<<v7.size()<<endl;
	
	return 0;
}
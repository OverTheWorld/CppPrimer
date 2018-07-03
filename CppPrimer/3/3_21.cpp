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
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10,42);
	vector<int> v4{10};
	vector<int> v5{10,42};
	vector<string> v6{10};
	vector<string> v7{10,"hi"};
	
	
	cout<<"v1:"<<endl;
	for(auto s : v1)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v2:"<<endl;
	for(auto s : v2)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v3:"<<endl;
	for(auto s : v3)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v4:"<<endl;
	for(auto s : v4)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v5:"<<endl;
	for(auto s : v5)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v6:"<<endl;
	for(auto s : v6)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	cout<<"v7:"<<endl;
	for(auto s : v7)
		cout<<s<<" ";
	cout<<endl<<endl;
	
	return 0;
}
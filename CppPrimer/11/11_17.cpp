//Program			: test the 11_17

#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<vector>
#include<iterator>

using std::vector;
using std::multiset;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	multiset<string> c = {"123","456","789"};
	vector<string> v = {"qwe","rty","uio"};
	for_each(c.cbegin(),c.cend(),[](const string & str){cout<<str<<" ";});
	cout<<endl;
	copy(v.begin(),v.end(),inserter(c,c.end()));
	for_each(c.cbegin(),c.cend(),[](const string & str){cout<<str<<" ";});
	cout<<endl;
	copy(c.begin(),c.end(),inserter(v,v.end()));
	copy(c.begin(),c.end(),back_inserter(v));
	for_each(v.cbegin(),v.cend(),[](const string & str){cout<<str<<" ";});
	cout<<endl;
}
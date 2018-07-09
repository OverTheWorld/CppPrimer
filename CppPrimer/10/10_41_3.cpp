#include<iostream>
#include<string>
#include<algorithm>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istream_iterator;

int main()
{
	string str1 = "No Smoking";
	string str2;
	replace_copy(str1.cbegin(),str1.cend(),back_inserter(str2),'o','u');
	cout<<str2<<endl;
	cout<<str1<<endl;
}
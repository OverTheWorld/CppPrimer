#include<iostream>
#include<string>
#include<iterator>
#include<cstdlib>
#include<ctime>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::begin;
using std::end;

using Array = string[10];
typedef string typeArray[10];

auto func(Array a) -> string (&)[10]
{
	for(auto s = begin(a);s != end(a);++s)
	{
		for(int i = 0;i<5;++i)
		{
			*s += 'A'+rand()%26;
		}
	}
	return a;
}
int main()
{
	string str[10];
	string (&strfunc)[10] = func(str);
	for(const auto &s : str)
	{
		cout<<s<<endl;
	}
	
	return 0;
}
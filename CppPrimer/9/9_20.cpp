#include<iostream>
#include<list>
#include<deque>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::deque;


int main()
{
	int ival;
	list<int> listInt;
	deque<int> deOdd,deEven;
	while(cin>>ival)
	{
		listInt.push_back(ival);
	}
	for(auto s : listInt)
	{
		if(s%2 == 0)
		{
			deEven.push_back(s);
		}
		else
		{
			deOdd.push_back(s);
		}
	}
	for(auto s : deEven)
	{
		cout<<s<<endl;
	}
	cout<<endl;
	for(auto s : deOdd)
	{
		cout<<s<<endl;
	}
	
}
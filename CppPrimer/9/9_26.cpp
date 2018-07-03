#include<iostream>
#include<vector>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::iterator;
using std::begin;
using std::end;

int main()
{
	int ia[] = {0,1,1,2,3,5,8,13,21,55,89};
	int *start = begin(ia),*send = end(ia);
	vector<int> vecInt(start,send);
	list<int> listInt(start,send);
	
	{
		auto it = vecInt.begin();
		while(it != vecInt.end())
		{
			if(*it %2 == 0)
			{
				it = vecInt.erase(it);
			}
			else
				++it;
		}
	}
	auto it = listInt.begin();
	while(it != listInt.end())
	{
		if(*it %2 == 1)
		{
			it = listInt.erase(it);
		}
		else
			++it;
	}
	for(auto &s : vecInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	for(auto &s : listInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	
	return 0;
}

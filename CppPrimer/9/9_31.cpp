#include<iostream>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::list;

int main()
{
	list<int> li = {0,1,2,3,4,5,6,7,8,9};
	auto beg = li.begin();
	while(beg != li.end())
	{
		if(*beg%2)
		{
			beg = li.insert(beg,*beg);
			//beg += 2;
			++beg;
			++beg;
		}
		else
		{
			beg = li.erase(beg);
		}
	}
	for(auto &s:li)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	
	return 0;
}


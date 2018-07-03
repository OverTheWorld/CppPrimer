#include<iostream>
#include<vector>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::vector;

int main()
{
	list<int> listInt = {1,2,3,44,55};
	vector<int> vecInt = {1,2,3,55};
	
	if(vecInt.size() == listInt.size())
	{
		auto it = vecInt.begin();
		for(const auto &s: listInt)
		{
			if(*it != s)
			{
				if(*it>s)
				{
					cout<<"vecInt > listInt"<<endl;
				}
				else
				{
					cout<<"vecInt < listInt"<<endl;
				}
				return 0;
			}
			++it;
		}
		cout<<"vecInt == listInt"<<endl;
	}
	else
	{
		if(vecInt.size() > listInt.size())
		{
			cout<<"vec > list"<<endl;
		}
		else
		{
			cout<<"vec < list"<<endl;
		}
	}
	
	return 0;
}

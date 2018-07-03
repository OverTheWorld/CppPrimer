#include<iostream>
#include<forward_list>

using std::cout;
using std::cin;
using std::endl;
using std::forward_list;

int main()
{
	forward_list<int> flistInt = {0,1,2,3,4,5,6,7,8,9};
	
	auto prev = flistInt.before_begin();
	auto curr = flistInt.begin();
	while(curr != flistInt.end())
	{
		if(*curr%2)
		{
			curr = flistInt.erase_after(prev);
		}
		else
		{
			prev = curr;
			++curr;
		}
	}
	for(auto s : flistInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
}
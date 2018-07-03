#include<iostream>
#include<forward_list>

using std::cout;
using std::cin;
using std::endl;
using std::forward_list;

int main()
{
	forward_list<int> fli = {0,1,2,3,4,5,6,7,8,9};
	
	auto prev = fli.before_begin();
	auto iter = fli.begin();
	
	while(iter!=fli.end())
	{
		if(*iter%2)
		{
			iter = fli.insert_after(iter,*iter);
			prev = iter++;
		}
		else
		{
			iter = fli.erase_after(prev);
		}
	}
	for(auto s : fli)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	return 0;
}

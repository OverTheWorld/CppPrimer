#include<iostream>
#include<string>
#include<memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::allocator;

int main()
{
	allocator<string> alc;
	string * const p = alc.allocate(10);
	string *q = p;
	alc.construct(q);
	size_t size = q-p;
	while(cin>>*q++&&size != 10)
	{
		alc.construct(q);
		size = q-p;
	}
	cout<<size<<endl;
	while(q!=p)
	{
		cout<<*(--q)<<endl;
		alc.destroy(q);
	}
	alc.deallocate(p,10);
	return 0;
}
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::begin;
using std::end;
void print(const int (&arr)[2])
{
	for(auto elem : arr)
	{
		cout<<elem<<endl;
	}
}

void print(const int a)
{
	cout<<a<<endl;
}

void print(const int* beg,const int* end)
{
	for(auto i = beg;i != end;++i)
	{
		cout<<*i<<endl;
	}
}

int main()
{
	int i = 0,j[2] = {0,1};
	print(j);
	print(i);
	print(begin(j),end(j));
	return 0;
}
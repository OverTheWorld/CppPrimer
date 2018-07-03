#include<iostream>
#include<initializer_list>

using std::cout;
using std::cin;
using std::endl;
using std::initializer_list;

int CalcAllVal(initializer_list<int> il)
{
	int sum = 0;
	for(initializer_list<int>::iterator beg = il.begin();beg != il.end();++beg)
	{
		sum += *beg;
	}
	return sum;
}
int main()
{
	cout<<CalcAllVal({1,2,3,4,5,6,7,8})<<endl;
	
	return 0;
}
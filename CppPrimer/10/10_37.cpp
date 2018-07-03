#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<list>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::vector;

int main()
{
	vector<int> vecInt;
	list<int> lstInt;
	for(int i = 0;i != 10;++i)
	{
		vecInt.push_back(i+1);
	}
	auto bIter = back_inserter(lstInt);
	auto rbegin_copy = vecInt.crbegin() + 2;
	auto rend_copy = vecInt.crend() - 3;
	copy(rbegin_copy,rend_copy,bIter);
	for_each(lstInt.cbegin(),lstInt.cend(),[](int num){cout<<num<<" ";});
	
}
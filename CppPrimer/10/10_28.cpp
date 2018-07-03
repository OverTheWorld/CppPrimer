#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include<functional>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::vector;
using std::array;
using namespace std::placeholders;

int main()
{
	vector<int> vecInt;
	array<list<int>,3> arrList;
	for(int i = 0;i!= 9;++i)
	{
		vecInt.push_back(i);
	}
	auto bIter = back_inserter(arrList.at(0));
	for(auto s: vecInt)
	{
		bIter = s;
	}
	auto fIter = front_inserter(arrList.at(1));
	for(auto s: vecInt)
	{
		fIter = s;
	}
	auto iIter = inserter(arrList.at(2),arrList.at(2).begin());
	for(auto s : vecInt)
	{
		iIter = s;
	}
	for(const auto &s : arrList)
	{
		for(auto v : s)
		{
			cout<<v<<" ";
		}
		cout<<endl;
	}
	
}
#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vecInt;
	vecInt.reserve(10);
	fill_n(vecInt.begin(),vecInt.size(),12321);
	for(const auto &s:vecInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	for(int i = 0;i<10;++i)
	{
		cout<<vecInt[10]<<" ";
	}
	cout<<endl;
	for(int i = 0;i<10;++i)
	{
		cout<<vecInt.at(i)<<" ";
	}
	cout<<endl;
	
	
}
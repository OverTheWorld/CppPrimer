#include<iostream>
#include<vector>
#include<iterator>
#include<ctime>
#include<cstdlib>
using std::vector;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	vector<int> vecInt;
	srand(time(NULL));
	for(int i = 0;i<10;++i)
	{
		vecInt.push_back(rand()%100);
	}
	for(const auto &s : vecInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	fill_n(vecInt.begin(),vecInt.size(),0);
	for(const auto &s : vecInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
}
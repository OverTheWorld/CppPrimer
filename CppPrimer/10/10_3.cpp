#include<iostream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<numeric>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vecInt;
	srand(time(nullptr));
	for(int i = 0;i<10;++i)
	{
		vecInt.push_back(rand()%100);
	}
	for(const auto &s : vecInt)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	cout<<accumulate(vecInt.cbegin(),vecInt.cend(),0)<<endl;
}
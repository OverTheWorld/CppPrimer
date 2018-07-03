#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vecInt;
	srand(time(nullptr));
	for(int i = 0;i!=30;++i)
	{
		vecInt.push_back(rand()%5);
	}
	for(const auto &s:vecInt)
		cout<<s<<" ";
	cout<<endl;
	int iCount = count(vecInt.cbegin(),vecInt.cend(),3);
	cout<<iCount<<endl;
}
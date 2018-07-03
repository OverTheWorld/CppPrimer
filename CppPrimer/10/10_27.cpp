#include<iostream>
#include<ctime>
#include<cstdlib>
#include<list>
#include<vector>
#include<algorithm>
#include<iterator>

using std::vector;
using std::list;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	srand(time(NULL));
	vector<int> vecInt;
	list<int> listInt;
	auto bIter = back_inserter(vecInt);
	for(int i = 0;i!= 20;++i)
	{
		bIter = rand()%20;
	}
	sort(vecInt.begin(),vecInt.end(),[](int num1,int num2){return num1<num2;});
	for_each(vecInt.cbegin(),vecInt.cend(),[](int num){cout<<num<<" ";});
	cout<<endl;
	auto bIterList = back_inserter(listInt);
	unique_copy(vecInt.cbegin(),vecInt.cend(),bIterList);
	for_each(listInt.cbegin(),listInt.cend(),[](int num){cout<<num<<" ";});
}
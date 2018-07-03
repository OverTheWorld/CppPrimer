#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<functional>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using namespace std::placeholders;

bool stringSize(int num,const string &str)
{
	if(num>=str.size())return true;
	return false;
}

int main()
{
	vector<int> vecInt;
	auto bIter = back_inserter(vecInt);
	srand(time(NULL));
	for(int i = 0;i != 10;++i)
	{
		bIter = rand()%40;
	}
	for_each(vecInt.cbegin(),vecInt.cend(),[](int num){cout<<num<<" ";});
	cout<<endl;
	string str;
	cin>>str;
	auto end_findif = find_if(vecInt.cbegin(),vecInt.cend(),bind(stringSize,_1,ref(str)));
	cout<<*end_findif<<endl;
}
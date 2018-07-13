#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::map;

int main()
{
	map<string,vector<int>> mapStrToVec;
	string str;
	vector<int> vecInt;
	srand(time(NULL));
	int size = rand()%100;
	for(int i = 0;i!=size;++i)
	{
		vecInt.push_back(rand()%100);
	}
	cin>>str;
	mapStrToVec[str] = vecInt;
	map<string,vector<int>>::iterator iter ;
	iter = mapStrToVec.find(str);
	cout<<str<<endl;
	for_each(iter->second.cbegin(),iter->second.cend(),[](int num){cout<<num<<" ";});
	cout<<endl;
}
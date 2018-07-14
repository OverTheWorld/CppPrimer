#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<algorithm>
#include<memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

shared_ptr<vector<int>>& ReadVec(shared_ptr<vector<int>> &pVecInt)
{
	srand(time(NULL));
	for(int i = 0;i<10;++i)
	{
		pVecInt->push_back(rand()%5000);
	}
	return pVecInt;
}
void PrintVec(shared_ptr<vector<int>> &pVecInt)
{
	for_each(pVecInt->cbegin(),pVecInt->cend(),[](int num){cout<<num<<endl;});
}
int main()
{
	PrintVec(ReadVec(make_shared<vector<int>>()));
}
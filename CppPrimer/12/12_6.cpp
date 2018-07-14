#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::nothrow;

vector<int>* getVec(){return new(nothrow) vector<int>;}

vector<int>* ReadVec(vector<int> *pVecInt)
{
	srand(time(NULL));
	for(int i = 0;i<10;++i)
	{
		pVecInt->push_back(rand()%5000);
	}
	return pVecInt;
}

void PrintVec(vector<int> *pVecInt)
{
	for_each(pVecInt->cbegin(),pVecInt->cend(),[](int num){cout<<num<<endl;});
	delete pVecInt;
}

int main()
{
	PrintVec(ReadVec(getVec()));
}
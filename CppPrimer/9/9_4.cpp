#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

auto findVal(vector<int>::iterator beg,const vector<int>::iterator end,int ival) ->vector<int>::iterator 
{
	for(;beg != end && *beg != ival;++beg);
	return beg;
}

int main()
{
	vector<int> vecInt = {1,2,3,4,5,6,7,8,9};
	cout<<(findVal(vecInt.begin(),vecInt.end(),5) != vecInt.end() ? "true":"false")<<endl;
	
	return 0;
}
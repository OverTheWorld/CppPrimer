#include<iostream>
#include<list>
#include<vector>

using std::list;
using std::vector;
using std::cout;
using std::endl;

int main()
{
	list<int> listInt = {1,2,3,4,5,6,7};
	vector<int> vecInt = {7,8,9,0,1};
	vector<double> vecDou(listInt.begin(),listInt.end());
	vector<double> vecDou2(vecInt.rbegin(),vecInt.rend());
	
	for(const auto &s: vecDou)
	{
		cout<<s<<endl;
	}
	cout<<endl;
	
	for(const auto &s : vecDou2)
	{
		cout<<s<<endl;
	}
	return 0;
}
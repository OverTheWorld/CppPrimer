#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vecInt1 = {1,2,3,4};
	vector<int> vecInt2 = {1,2,5,7};
	
	if(vecInt1 == vecInt2)
	{
		cout<<" == "<<endl;
	}
	else
	{
		cout<<" != "<<endl;
	}
	
	return 0;
}
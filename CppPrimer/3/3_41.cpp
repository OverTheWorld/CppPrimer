#include<iostream>
#include<iterator>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::iterator;

int main()
{
	int a[10];
	int i = 0;
	for(auto &s : a)
	{
		s = i++;
	}
	vector<int> vi(a,a+10);
	
	for(auto s : vi)
		cout<<s<<endl;
	
	return 0;
}
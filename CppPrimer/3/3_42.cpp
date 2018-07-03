#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vi(10,42);
	
	int a[10];
	auto pStart = vi.begin();
	auto pEnd = vi.end();
	for(auto &s : a)
	{
		s = *pStart;
		pStart++;
	}
	
	for(auto s : a)
		cout<<s<<endl;
	
	return 0;
}
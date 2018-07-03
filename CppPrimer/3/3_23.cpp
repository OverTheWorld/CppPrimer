#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vi(10,21);
	for(auto it = vi.begin();it!=vi.end();it++)
	{
		(*it)*=2;
		cout<<*it<<endl;
	}
	
	return 0;
}
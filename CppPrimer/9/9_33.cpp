#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
	
	auto iter = vi.begin();
	while(iter != vi.end())
	{
		cout<<*iter<<" ";
		++iter;
		iter = vi.insert(iter,10);
		cout<<*iter<<" ";
		++iter;
	}
	return 0;
}
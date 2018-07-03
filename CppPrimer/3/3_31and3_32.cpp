#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	int a[10];
	for(int i = 0;i<10;i++)
	{
		a[i] = i;
		cout<<a[i]<<" ";
	}
	cout<<endl;
	int b[10];
	for(int i = 0;i<10;i++)
	{
		b[i] = a[i];
		cout<<b[i]<<" ";
	}
	cout<<endl;
	vector<int> v1(10);
	int i = 0;
	for(auto &s : v1)
	{
		s = i++;
		cout<<s<<" ";
	}
	
	return 0;
}
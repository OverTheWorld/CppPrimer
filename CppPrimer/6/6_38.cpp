#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};

decltype(odd) &arrPtr(int i)
{
	return (i%2)?odd:even;
}

int main()
{
	int ival;
	cin>>ival;
	int (&arr)[5] = arrPtr(ival);
	for(auto s : arr)
		cout<<s<<" ";
	cout<<endl;
	return 0;
}
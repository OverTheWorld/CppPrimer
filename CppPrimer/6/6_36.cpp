#include<iostream>
#include<cmath>

using std::cout;
using std::cin;
using std::endl;

int (&func(int ival,int &length,int (&a)[100]))[100]
{
	int sqrtiVal = static_cast<int>(sqrt(static_cast<double>(ival)));
	length = 0;
	for(int i = 1;i<=sqrtiVal;++i)
	{
		if(ival%i == 0)
		{
			a[length++] = i;
			a[length++] = ival/i;
		}
	}
	return a;
}
int main()
{
	int ival;
	scanf("%d",&ival);
	int a[100];
	int length = 0;
	int (&ra)[100] = func(ival,length,a);
	for(int i = 0;i<length;++i)
		cout<<ra[i]<<" ";
	cout<<endl;
	
	return 0;
}
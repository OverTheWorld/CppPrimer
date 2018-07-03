#include<iostream>
using std::cout;
using std::cin;
using std::endl;

void ExchangePointer(int *&pa,int *&pb)
{
	int *pTemp = pa;
	pa = pb;
	pb = pTemp;
}
int main()
{
	int *pa,*pb;
	pa = new int;
	pb = new int;
	
	cin>>*pa>>*pb;
	ExchangePointer(pa,pb);
	cout<<"pa:"<<*pa<<endl;
	cout<<"pb:"<<*pb<<endl;
	return 0;
}
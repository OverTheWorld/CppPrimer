#include<iostream>
using std::cout;
using std::cin;
using std::endl;
int ExchangeVal(int a,int *pb);
int main()
{
	int a,b;
	cin>>a>>b;
	cout<<ExchangeVal(a,&b)<<endl;
	return 0;
}
int ExchangeVal(int a,int *pb)
{
	return (a>*pb?a:*pb);
}
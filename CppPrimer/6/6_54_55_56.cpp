#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int numOperator(int,int);

int add(int a,int b)
{
	return a+b;
}
int minus(int a,int b)
{
	return a-b;
}
int multiple(int a,int b)
{
	return a*b;
}
int divide(int a,int b)
{
	if(b != 0)
		return a/b;
	else 
		return -1;
}

int main()
{
	vector<int(*)(int,int)> vec;
	vec.push_back(add);
	vec.push_back(minus);
	vec.push_back(multiple);
	vec.push_back(divide);
	int a,b;
	cin>>a>>b;
	for(auto &s : vec)
	{
		cout<<s(a,b)<<endl;
	}
	return 0;
}
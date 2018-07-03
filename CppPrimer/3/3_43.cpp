#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int ia[3][4];
	int i = 0;
	for(int (&row)[4] : ia)
		for(int &s : row)
			s = i++;
	for(int i = 0;i != 3;i++)
		for(int j = 0;j!=4;j++)
		{
			cout<<ia[i][j]<<" ";
		}
	cout<<endl;
	for(int (*p)[4] = ia;p != ia+3;p++)
		for(int *ps = *p;ps != *p+4;ps++)
		{
			cout<<*ps<<" ";
		}
	cout<<endl;
	
	return 0;
}
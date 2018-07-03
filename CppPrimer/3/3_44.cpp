#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	using int_array = int[4];
	int ia[3][4],i = 0;
	for(int_array &array : ia)
		for(int &s : array)
		{
			s = i++;
		}
	for(i = 0;i != 3;i++)
		for(int j = 0;j != 4;j++)
			cout<<ia[i][j]<<" ";
		cout<<endl;
	for(int_array *array = ia;array != ia+3;array++)
		for(int *p = *array;p != *array+4;p++)
			cout<<*p<<" ";
		cout<<endl;
		
		return 0;
}
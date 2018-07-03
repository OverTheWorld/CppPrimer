#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int ia[3][4],i = 0;
	
	for(auto &array:ia)
		for(auto &s : array)
			s = i++;
		
	for(i = 0;i != 3;i++)
		for(auto j = 0;j != 4;j++)
			cout<<ia[i][j]<<" ";
	cout<<endl;
	for(auto array = ia;array != ia +3;array++)
		for(auto p = *array;p != *array + 4;p++)
			cout<<*p<<" ";
	cout<<endl;
	
	return 0;
}
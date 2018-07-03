#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

void Print(vector<int> &vec,vector<int>::iterator i )
{
	if(i == vec.end())return ;
	else
	{
		cout<<*i++<<endl;
		Print(vec,i);
	}
}

int main()
{
	vector<int> vec = {1,2,3,4,5,6,7,8,9,0};
	Print(vec,vec.begin());
	
	return 0;
}
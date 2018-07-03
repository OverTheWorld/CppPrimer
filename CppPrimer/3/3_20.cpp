#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// int main()
// {
	// vector<int> v1;
	// int iInput;
	// while(cin>>iInput)
	// {
		// v1.push_back(iInput);
	// }
	// auto count = v1.size();
	// for(decltype(count) i = 1;i<count;i++)
	// {
		// cout<<v1[i-1]+v1[i]<<endl;
	// }
	
	// return 0;
// }
int main()
{
	vector<int> v1;
	int iInput;
	while(cin>>iInput)
	{
		v1.push_back(iInput);
	}
	auto count = v1.size();
	for(decltype(count) i = 0;i<=count - i - 1;i++)
	{
		if(i == count - i - 1)
		{
			cout<<v1[i]<<endl;
		}
		else
		{
			cout<<v1[i]+v1[count - i - 1]<<endl;
		}
	}
	
	return 0;
}
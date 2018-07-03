#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// int main()
// {
	// vector<int> v1;
	// int iInput;
	
	// while(cin>>iInput)
	// {
		// v1.push_back(iInput);
	// }
	// for(auto it = v1.begin()+1;it!=v1.end();it++)
	// {
		// cout<<*it+*(it-1)<<endl;
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
	
	for(auto its = v1.begin(),ite = v1.end()-1;ite >= its;its++,ite--)
	{
		if(ite == its)
			cout<<*its<<endl;
		else
			cout<<*its + *ite <<endl;
	}
	
	return 0;
}
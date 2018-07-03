#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	vector<int> v1;
	int iInput;
	while(cin>>iInput)
		v1.push_back(iInput);
	cout<<endl;
	for(auto s : v1)
		cout<<s<<endl;
	
	return 0;
}
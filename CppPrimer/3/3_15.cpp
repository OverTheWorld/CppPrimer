#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

int main()
{
	string iInput;
	vector<string> v1;
	while(getline(cin,iInput))
	{
		v1.push_back(iInput);
	}
	for(auto s : v1)
		cout<<s;
	return 0;
}
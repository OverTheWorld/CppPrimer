#include<iostream>
#include<vector>
#include<string>


using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main()
{
	vector<char> vc;
	char cc;
	while(cin>>cc)
	{
		vc.push_back(cc);
	}
	string str(vc.begin(),vc.end());
	cout<<str<<endl;
	return 0;
}
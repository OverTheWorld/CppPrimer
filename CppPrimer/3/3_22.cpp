#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	vector<string> vstr;
	string InputString;
	while(getline(cin,InputString))
		vstr.push_back(InputString);
	for(auto it = vstr.begin();!it->empty()&&it != vstr.end();it++)
	{
		for(auto &s : *it)
			if(isalpha(s))
				s = toupper(s);
		
	}
	for(auto s : vstr)
		cout<<s<<endl;
		
	return 0;
}
#include<iostream>
#include<string>
#include<vector>
#include<cctype>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
	vector<string> vstrInput;
	string strInput;
	while(cin>>strInput)
	{
		for(auto &s : strInput)
			s = toupper(s);
		vstrInput.push_back(strInput);
	}
	for(decltype(vstrInput.size()) i = 0;i<vstrInput.size();i++)
		cout<<vstrInput[i]<<endl;
	
	return 0;
}
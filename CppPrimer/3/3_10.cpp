#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string strInput;
	string strOut;
	cout<<"Please Input some Words:"<<endl;
	cin>>strInput;
	for(auto s : strInput)
		if(!ispunct(s))
			strOut += s;
	cout<<strOut<<endl;
	
	return 0;
}
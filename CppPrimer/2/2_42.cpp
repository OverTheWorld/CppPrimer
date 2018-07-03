#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string strLine;
	while(getline(cin,strLine))
		cout<<strLine<<endl;
	
	cout<<" End "<<endl;
	
	return 0;
}
#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string strInput;
	cout<<"Please input some words"<<endl;
	cin>>strInput;
	for(char &s : strInput)
		s = 'X';
	cout<<strInput<<endl;
	
	return 0;
}
#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
int main(int argc,char *argv[])
{
	string str = "";
	str =str + argv[1] +" "+ argv[2];
	cout<<str<<endl;
	return 0;
}
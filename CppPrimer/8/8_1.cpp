#include<iostream>
#include<string>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::istream;
using std::istringstream;

istream& read(istream& is,string& str)
{
	do
	{
		is >> str;
		cout<<str<<endl;
	}while(!is.eof());
	
	is.clear();
	return is;
}

int main()
{
	string strLine;
	getline(cin,strLine);
	istringstream iss(strLine);
	string str;
	read(iss,str);
	cout<<str<<endl;
	
	return 0;
}
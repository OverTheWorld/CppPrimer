#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::wstring;
using std::wcout;

int main()
{
	string strInput;
	const wstring cstrOutString = (L" Please Input some words");
	wcout<<cstrOutString<<endl;
	cin>>strInput;
	auto input_count = strInput.size();
	for(auto &s : strInput)
	{
		s = L'X';
	}
	cout<<"the sum of these is";
	cout<<input_count<<endl;
	cout<<"the string is "<<endl;
	cout<<strInput<<endl;
	
	return 0;
}
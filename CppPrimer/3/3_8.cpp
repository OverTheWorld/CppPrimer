#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string strInput;
	cout<<"Please Input Some Words:"<<endl;
	cin>>strInput;
	auto sumOfStr = strInput.size();
	decltype(sumOfStr) i = 0;
	while(i< sumOfStr)
	{
		strInput[i] = 'X';
		i++;
	}
	cout<<strInput<<endl;
	return 0;
}
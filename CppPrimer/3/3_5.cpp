#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* int main()
{
	string str[10],str1;
	int i = 0;
	while(cin >> str[i])
		str1 += str[i++];
	
	cout<< str1 <<endl;
	
	return 0;
} */

int main()
{
	string str[10],str1;
	int i = 0;
	while(cin>>str[i])
		str1 += (str[i++] + " ");
	
	cout<<str1<<endl;
	
	return 0;
}
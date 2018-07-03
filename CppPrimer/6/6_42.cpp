#include<iostream>
#include<string>
#include<cstddef>

using std::cout;
using std::cin;
using std::endl;
using std::string;

string make_plural(size_t crt,const string &word,const string &ending = "s")
{
	return crt>1?word+ending:word;
}

int main()
{
	string strWord;
	while(cin>>strWord)
	{
		cout<<make_plural(2,strWord);
	}
	return 0;
}

#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc,char *argv[])
{
	for(int i = 1;i<argc;++i)
	{
		cout<<argv[i]<<" ";
	}
	cout<<endl;
	return 0;
}
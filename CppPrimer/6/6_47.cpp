#define NDEBUG
#include<cassert>
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void Print(vector<string> &vec)
{
	#ifndef NDEBUG
	
	cout<<endl;
	cout<<"Error:"<<__FILE__<<":in file "<<__FILE__<<" at line "<<__LINE__<<endl;
	cout<<"Compiled on "<<__DATE__<<" at "<<__TIME__<<":"<<endl;
	cout<<"this vector size is :" <<vec.size()<<endl;
	cout<<endl;
	
	#endif
	if(vec.empty())return ;
	else
	{
		assert(vec.back() != "[");
		cout<<vec.back()<<endl;
		vec.pop_back();
	}
	Print(vec);
}
void GetValue(vector<string> &vec,int n)
{
	string str;
	srand(static_cast<unsigned>(time(NULL)));
	for(int i = 0;i != n;++i)
	{
		str = 'A' + rand()%27;
		vec.push_back(str);
	}
}
int main()
{
	int n;
	vector<string> vec;
	while(cin>>n)
	{
		GetValue(vec,n);
		Print(vec);
	}
	return 0;
}
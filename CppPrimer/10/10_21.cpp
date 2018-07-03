#include<iostream>
#include<algorithm>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int input;
	cout<<"Please input a number:"<<endl;
	cin>>input;
	auto f = [&input]()->bool{--input;return input?false:true;};
	bool b;
	while(!(b = f()))
	{
		cout<<(b?"true":"false")<<" ";
	}
	cout<<endl;
}
#include<iostream>
#include<memory>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unique_ptr;

int main()
{
	unique_ptr<int> pu1(new int());
	unique_ptr<int> pu2 = pu1;
	
}
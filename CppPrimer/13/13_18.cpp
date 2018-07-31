//首先实际上我认为雇员类是不需要拷贝控制成员的，因为实际上把一个雇员对象赋予另一个这样是没有意义的，但是我们抽象开来，不考虑现实情况，那么可以写一写。

#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Employee
{
	static size_t count;
	string name;
	size_t number;
	
public:
	void Print()const
	{
		cout<<name<<endl<<number<<endl;
	}
	Employee():
	name(""),number(count++)
	{
		
	}
};
size_t Employee::count = 0;

int main()
{
	Employee t1,t2,t3;
	t1.Print();
	t2.Print();
	t3.Print();
}
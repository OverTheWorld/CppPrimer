#include<iostream>

using std::cout;
using std::cin;
using std::endl;

struct NoDefault
{
	NoDefault(int s):data(s){}
	int getData()const{return data;}
	private:
		int data;
};
struct C
{
	C() = default;
	const NoDefault& getNoDefault()const{return nd;}
	private:
		NoDefault nd = 10;
};

int main()
{
	C varC;
	cout<<varC.getNoDefault().getData()<<endl;
	
	return 0;
}

//const this指针只能指向const成员
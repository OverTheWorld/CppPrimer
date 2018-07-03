#include<iostream>
int main()
{
	int i = 1,&r1 = i;
	double d = 0,&r2 = d;
	std::cout<<"r1: "<<i<<"r2: "<<r2<<std::endl;
	r1 = i;
	std::cout<<"r1: "<<r1<<std::endl;
	return 0;
}
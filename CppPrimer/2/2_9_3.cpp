#include<iostream>
int main()
{
	int wage(1);
	std::cout<<wage<<std::endl;
	int salary = wage = 9999;
	std::cout<<salary<<"  "<<wage<<std::endl;
	return 0;
}
#include<iostream>
#include<string>
struct Sales_data{
	std::string ISBN;
	int iCount;
	double dRevenue;
};

Sales_data data1,data2;

int main()
{
	double dPrice;
	std::cin>>data1.ISBN>>data1.iCount>>dPrice;
	data1.dRevenue = data1.iCount*dPrice;
	std::cin>>data2.ISBN>>data2.iCount>>dPrice;
	data2.dRevenue = data2.iCount*dPrice;
	
	if(data1.ISBN == data2.ISBN)
	{
		int iCount = data1.iCount + data2.iCount;
		if(iCount != 0)
		{
			std::cout<<data1.ISBN<<" "<<iCount<<" "<<(data1.dRevenue+data2.dRevenue)/iCount<<std::endl;
		}
		else
		{
			std::cout<<data1.ISBN<<" "<<iCount<<" "<<0<<std::endl;
		}
		return 0;
	}
	else
	{
		std::cout<<" these ISBN is not equal!"<<std::endl;
		return -1;
	}
}
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

struct Sales_data
{
	friend istream& read(istream& is,Sales_data& sa);
	friend ostream& print(ostream& os,const Sales_data& sa);
	friend Sales_data& add(Sales_data& lsa,const Sales_data& rsa);
	
	Sales_data(string str = ""):isbn(str){}
	Sales_data(string str,unsigned num,double allCost):isbn(str),cCount(num),revenue(allCost){}
	Sales_data(istream& is)
	{
		read(is,*this);
	}
	const string& getIsbn()const{return isbn;}
	private:
		string isbn;
		unsigned cCount = 0;
		double revenue = 0;
};

Sales_data& add(Sales_data& lsa,const Sales_data& rsa)
{
	lsa.cCount += rsa.cCount;
	lsa.revenue += rsa.cCount;
	return lsa;
}

istream& read(istream& is,Sales_data& sa)
{
	return is>>sa.isbn>>sa.cCount>>sa.revenue;
}

ostream& print(ostream& os,const Sales_data& sa)
{
	os <<"ISBN: " <<sa.getIsbn()<<endl
	<<"总数:"<<sa.cCount<<endl
	<<"单价:"<<sa.revenue/sa.cCount<<endl
	<<"总价:"<<sa.revenue<<endl;
	return os;
}

int main()
{
	
	Sales_data lsa,rsa;
	fstream ifs("./infile.txt",fstream::in);
	fstream ofs("./outfile.txt",fstream::out);
	read(ifs,lsa);
	while(read(ifs,rsa))
	{
		if(lsa.getIsbn() == rsa.getIsbn())
		{
			add(lsa,rsa);
		}
	}
	print(ofs,lsa);
	return 0;
}
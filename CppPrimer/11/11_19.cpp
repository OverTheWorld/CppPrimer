#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<fstream>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::multiset;
using std::istringstream;

struct SalesData
{
	string strBook;
	int price;
};

bool compareSale(const SalesData &s1,const SalesData &s2)
{
	return s1.price<s2.price;
}

int main()
{
	SalesData ss;
	multiset<SalesData,bool(*)(const SalesData& s1,const SalesData& s2)> setSales(compareSale);
	ifstream ifs("11_19_infile.txt");
	istringstream iss;
	string line,str;
	
	while(getline(ifs,line))
	{
		iss.str(line);
		iss>>ss.strBook;
		iss>>str;
		ss.price = stoi(str);
		setSales.insert(ss);
		iss.clear();
	}
	multiset<SalesData,bool(*)(const SalesData& s1,const SalesData& s2)>::iterator iter = setSales.begin();
	while(iter != setSales.end())
	{
		cout<<iter->strBook<<" : "<<iter->price<<endl;
		++iter;
	}
}
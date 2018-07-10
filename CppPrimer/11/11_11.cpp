//程序名：11_11
//程序需求：不使用decltype重新定义bookstore
//程序过程思路：定义书籍类型，以其价格进行排序，以此作为假性案例进行实现

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
using std::multiset;
using std::ifstream;
using std::istringstream;

struct book 
{
	string strBookName;
	string strISBN;
	size_t price;
};
bool compareBook(const book &b1,const book &b2)
{
	return b1.price<b2.price;
}

int main()
{
	multiset<book,bool(*)(const book &b1,const book &b2)> mset(compareBook);
	ifstream ifs("11_11_infile.txt");
	string line,str;
	istringstream iss;
	book bTemp;
	while(getline(ifs,line))
	{
		iss.str(line);
		iss>>bTemp.strBookName;
		iss>>bTemp.strISBN;
		iss>>bTemp.price;
		iss.clear();
		mset.insert(bTemp);
	}
	for_each(mset.cbegin(),mset.cend(),[](const book b){cout<<b.strBookName<<" "<<b.strISBN<<" "<<b.price<<endl;});
	
}
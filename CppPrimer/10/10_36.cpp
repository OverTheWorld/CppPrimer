#include<iostream>
#include<list>
#include<ctime>
#include<cstdlib>
#include<iterator>
#include<fstream>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::list;
using std::istream_iterator;

int main()
{
	ifstream ifs("infile.txt");
	istream_iterator<int> in(ifs),eof;
	list<int> lstInt(in,eof);
	srand(time(NULL));
	auto site = rand()%20;
	auto iter = lstInt.begin();
	for(int i = 0;i != site;++i,++iter);
	lstInt.insert(iter,0);
	for_each(lstInt.cbegin(),lstInt.cend(),[](int num){cout<<num<<" ";});
	cout<<endl;
	auto rIter = find(lstInt.crbegin(),lstInt.crend(),0);
	for_each(lstInt.crbegin(),rIter,[](int num){cout<<num<<" ";});
	cout<<endl;
	for_each(rIter,lstInt.crend(),[](int num){cout<<num<<" ";});
	cout<<endl;
}
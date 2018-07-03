#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::istream_iterator;

int main()
{
	ifstream ifs("infile.txt");
	istream_iterator<int> in(ifs),eof;
	vector<int> vecInt(in,eof);
	auto iter = vecInt.cend();
	do
	{
		cout<<*--iter<<" ";
	}while(iter != vecInt.cbegin());
	cout<<endl;
}
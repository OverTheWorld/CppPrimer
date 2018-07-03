#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::istream_iterator;

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	istream_iterator<int> in(ifs),eof;
	vector<int> vecInt(in,eof);
	for_each(vecInt.crbegin(),vecInt.crend(),[](int num){cout<<num<<" ";});
	cout<<endl;
}
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	ofstream ofsOdd("outfileOdd.txt",std::ios::out),ofsEven("outfileEven.txt",std::ios::out);
	istream_iterator<int> in(ifs),eof;
	ostream_iterator<int> outOdd(ofsOdd," "),outEven(ofsEven,"\n");
	vector<int> vecInt;
	auto bIter = back_inserter(vecInt);
	copy(in,eof,bIter);
	for_each(vecInt.cbegin(),vecInt.cend(),[&](int num)
		{
			if(num % 2 == 0)
				*outEven = num;
			else
				*outOdd = num;
		}
	);
}
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
	ifstream ifs("infile.txt",std::ios::in);
	ofstream ofs("outfile.txt",std::ios::out);
	istream_iterator<string> in(ifs),eof;
	ostream_iterator<string> out(ofs,"\n");
	vector<string> vecStr(in,eof);
	for_each(vecStr.cbegin(),vecStr.cend(),[&out](const string &str){cout<<str<<" ";*out = str;});
	*out = "\n";
	cout<<endl;
}
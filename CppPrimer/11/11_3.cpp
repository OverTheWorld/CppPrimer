//Program:count words
//		use map save and count the words

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<algorithm>
#include<iterator>

using std::cout;
using std::ostream;
using std::endl;
using std::string;
using std::map;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
	ifstream ifs("TextInfile.txt");
	ofstream ofs("TextOutfile.txt");
	istream_iterator<string> in(ifs),eof;
	map<string,size_t> mapStrToSize_t;
	for_each(in,eof,[&](const string &str){++mapStrToSize_t[str];});
	for_each(mapStrToSize_t.cbegin(),mapStrToSize_t.cend(),[&](const pair<string,size_t> &conPair){ofs<<conPair.first<<" "<<conPair.second<<endl;});
	cout<<endl;
}
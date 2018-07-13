#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<iterator>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;
using std::map;
using std::istream_iterator;

int main()
{
	ifstream ifs("11_20.cpp");
	istream_iterator<string> in(ifs),eof;
	map<string,size_t> mapWordCount;
	while(in != eof)
	{
		auto par = mapWordCount.insert({*in,1});
		if(!par.second)
			++par.first->second;
		++in;
	}
	for(const auto &s : mapWordCount)
	{
		cout<<s.first<<" : "<<s.second<<endl;
	}
	
}
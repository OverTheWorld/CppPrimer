#include<iostream>
#include<fstream>
#include<unordered_map>
#include<iterator>
#include<string>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::unordered_map;
using std::istream_iterator;

int main()
{
	ifstream ifs("11_38.cpp");
	istream_iterator<string> in(ifs),eof;
	unordered_map<string,size_t> unorderMapWordCount;
	string str;
	while(ifs>>str)
	{
		++unorderMapWordCount[str];
	}
	for(const auto & s : unorderMapWordCount)
	{
		cout<<s.first<<" : "<<s.second<<endl;
	}
}
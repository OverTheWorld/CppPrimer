#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::string;
using std::ifstream;
using std::istream_iterator;

int main()
{
	map<string,int> mapWordCount;
	ifstream ifs("11_18.cpp");
	istream_iterator<string> in(ifs),eof;
	while(in != eof)
	{
		++mapWordCount[*in++];
	}
	map<string,int>::iterator map_it = mapWordCount.begin();
	while(map_it != mapWordCount.end())
	{
		cout<<map_it->first<<" : "<<map_it->second<<endl;
		++map_it;
	}
	
}
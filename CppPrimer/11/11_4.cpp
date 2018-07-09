//Program:			words count
//goal:				save words in map (key as word and value as count) ,and ignore case and punctuation

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<ctype.h>
#include<iterator>
#include<sstream>
#include<list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::list;
using std::ifstream;
using std::istream_iterator;
using std::insert_iterator;
using std::istringstream;

const char* charInclude = "abcdefghijklmnopqrstuvwxyz'ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void processString(string &str)
{
	size_t pos = 0;
	while((pos = str.find_first_not_of(charInclude,pos))!=string::npos)
	{
		str.at(pos) = ' ';
		++pos;
	}
}

int main()
{
	ifstream ifs("TextInfile.txt");
	string line;
	getline(ifs,line);
	processString(line);
	istringstream iss(line);
	map<string,size_t> mapStr;
	string str;
	while(iss>>str)
	{
		++mapStr[str];
	}
	for(const auto &s : mapStr)
	{
		cout<<s.first<<" : "<<s.second<<endl;
	}
}
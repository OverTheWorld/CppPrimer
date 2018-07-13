#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<iterator>
#include<algorithm>

using std::cout;
using std::endl;
using std::pair;
using std::map;
using std::cin;
using std::string;
using std::multimap;
using std::ifstream;
using std::istream_iterator;

int main()
{
	ifstream ifs("11_31_infile.txt");
	istream_iterator<string> in(ifs),eof;
	multimap<string,string> mmapBook;
	while(in != eof)
	{
		cout<<*in<<endl;
		mmapBook.insert({*in++,*in});
		++in;
	}
	for_each(mmapBook.cbegin(),mmapBook.cend(),[](const pair<string,string> &par){cout<<par.first<<" : "<<par.second<<endl;});
	string str;
	cin>>str;
	cout<<endl;
	auto count = mmapBook.count(str);
	multimap<string,string>::iterator iter = mmapBook.find(str);
	while(count--)
	{
		cout<<iter->first<<" : "<<iter->second<<endl;
		iter = mmapBook.erase(iter);
	}
	cout<<endl;
	for(const auto & s : mmapBook)
	{
		cout<<s.first<<" : "<<s.second<<endl;
	}
	cout<<endl;
}
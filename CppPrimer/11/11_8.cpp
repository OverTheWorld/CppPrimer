//Program:						save unrepeated words by vector
//Program Process:				void save(vector<string> &vecStr,const string &str);
//Program Process function:		check if str has exist ,if not ,insert the str into vecStr,else ,do nothing

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iterator>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::istream_iterator;

void save(vector<string> &vecStr,const string &str)
{
	int pos;
	auto iter = lower_bound(vecStr.cbegin(),vecStr.cend(),str);
	if(iter == vecStr.cend() || *iter != str)
	{
		vecStr.insert(iter,str);
	}
}

int main()
{
	ifstream ifs("TextInfile.txt");
	istream_iterator<string> in(ifs),eof;
	vector<string> vecStr;
	while(in != eof)
	{
		save(vecStr,*in++);
	}
	for_each(vecStr.begin(),vecStr.end(),[](const string &str){cout<<str<<" ";});
}
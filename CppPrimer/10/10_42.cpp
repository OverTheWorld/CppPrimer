//reading text from file
//save in list
//sort list and unique it,then output it

#include<iostream>
#include<list>
#include<string>
#include<fstream>
#include<algorithm>
#include<iterator>

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::ifstream;
using std::string;
using std::istream_iterator;

//sort and unique words function
void DeleteRepeatedWord(list<string> &lstStr)
{
	lstStr.sort();
	lstStr.unique();
}

int main()
{
	ifstream ifs("TextInfile.txt");
	istream_iterator<string> in(ifs),eof;
	list<string> lstStr(in,eof);
	for_each(lstStr.begin(),lstStr.end(),[](const string &str){cout<<str<<" ";});
	cout<<endl;
	DeleteRepeatedWord(lstStr);
	for_each(lstStr.begin(),lstStr.end(),[](const string &str){cout<<str<<" ";});
}
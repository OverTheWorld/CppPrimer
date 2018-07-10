//Program:								save the map of word and line number in a text files
//Program version:						1.0
//Program Requirement Analysis:			for every word divided by space in a file, show all line number of every word(a line per word)
//Program Process:						scan the file , then save the word and line number in map ,show it in the end.

#include<iostream>
#include<string>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
#include<iterator>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::list;
using std::ifstream;
using std::istringstream;
using std::pair;

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		cout<<"parameters are wrong!"<<endl;
	}
	map<string,list<size_t>> mapWordToLineNum;
	ifstream ifs(argv[1]);
	istringstream iss;
	string line,str;
	size_t lineNum = 0;
	while(getline(ifs,line))
	{
		iss.str(line);
		while(iss>>str)
		{
			mapWordToLineNum[str].push_back(lineNum);
		}
		iss.clear();
		++lineNum;
	}
	for_each(mapWordToLineNum.cbegin(),mapWordToLineNum.cend(),
		[](const pair<string,list<size_t>> &par)->void
		{
			cout<<par.first<<" : ";
			for_each(par.second.cbegin(),par.second.cend(),
				[](size_t num)
				{
					cout<<num<<" ";
				}
			);
			cout<<endl;
		}
	);
}
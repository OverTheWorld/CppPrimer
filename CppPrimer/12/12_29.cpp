#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::ifstream;
using std::istringstream;

int main(int argc,char* argv[])
{
	if(argc != 2)
	{
		cout<<"parameters are wrong!"<<endl;
		return 0;
	}
	string strCurFile;
	long len = GetCurrentDirectory(0,nullptr);
	strCurFile.resize(len);
	GetCurrentDirectory(len,&strCurFile[0]);
	strCurFile.resize(len-1);
	strCurFile = strCurFile + "\\" + argv[1];
	cout<<strCurFile<<endl;
	ifstream ifs(strCurFile);
	istringstream iss;
	string line,strTemp;
	vector<string> vecText;
	map<string,set<size_t>> mapWordToSet;
	size_t lineNum = 0;
	while(getline(ifs,line))
	{
		vecText.push_back(line);
		iss.str(line);
		while(iss>>strTemp)
		{
			mapWordToSet[strTemp].insert(lineNum);
		}
		++lineNum;
		iss.clear();
	}
	cout<<vecText.size()<<endl;
	string strIn;
	do
	{
		cout<<"enter a word to observe :"<<endl;
		if(!(cin>>strIn) || strIn == "q")
			break;
		auto iter = mapWordToSet.find(strIn);
		if(iter == mapWordToSet.end())
		{
			cout<<"the file hasn't the word!"<<endl;
			continue;
		}
		cout<<"element occurs "<<iter->second.size()<<" times"<<endl;
		for_each(iter->second.cbegin(),iter->second.cend(),
		[&vecText](size_t num)
		{
			cout<<"\t"<<"(line "<<num<<") "<<vecText.at(num)<<endl;
		}
		);
		cout<<endl;
	}while(true);
}
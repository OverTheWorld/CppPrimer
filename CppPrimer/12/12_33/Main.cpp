#include"QueryResult.h"
#include<iostream>
#include<Windows.h>

using std::ifstream;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void runQueries(ifstream &ifs)
{
	TextQuery tq(ifs);
	string strWord;
	while (true)
	{
		cout << "enter a word to observe:" << endl;
		if (!(cin >> strWord) || strWord == "q")
			break;
		auto qr = tq.query(strWord);
		print(cout, qr);
		//test begin
		cout << endl << endl;
		for_each(qr.begin(),qr.end(),
			[&qr](size_t num)
			{
			cout << num << " : " << qr.get_File()->at(num-1) << endl;
			}
		);
		//test end
	}
}
int main(int argc,char* argv[])
{
	if (argc != 2)
	{
		cout << "the parameters are wrong!" << endl;
		return 0;
	}
	string strFile;
	long len = GetCurrentDirectory(0, nullptr);
	strFile.resize(len);
	GetCurrentDirectory(len, &strFile[0]);
	strFile.resize(len - 1);
	strFile = strFile + "\\" + argv[1];
	ifstream ifs(strFile);
	if (!ifs.good())
	{
		cout << "Fail to Open File!" << endl;
		return 0;
	}
	runQueries(ifs);
}
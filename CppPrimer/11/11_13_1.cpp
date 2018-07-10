//程序需读取11_12_infile.txt文件，请将两个文件放在同一文件夹下
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::pair;
using std::string;
using std::vector;

int main()
{
	ifstream ifs("11_12_infile.txt");
	vector<pair<string,int>> vecPar;
	string str;
	int i;
	while(ifs>>str)
	{
		ifs>>i;
		vecPar.push_back({str,i});
	}
	for_each(vecPar.cbegin(),vecPar.cend(),
		[](const pair<string,int> & s)
		{
			cout<<s.first<<" : "<<s.second<<endl;
		}
	);
}
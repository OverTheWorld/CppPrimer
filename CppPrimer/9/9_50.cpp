#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::out_of_range;


int CalcInt(vector<string> vecStr)
{
	int i,sum;
	for(i = 0,sum = 0;i!=vecStr.size();++i)
	{
		sum += stoi(vecStr.at(i));
	}
	return sum;
}
double CalcDou(vector<string> vecStr)
{
	int i;
	double sum = 0.0;
	for(i = 0;i != vecStr.size();++i)
	{
		sum += stod(vecStr.at(i));
	}
	return sum;
}
int main()
{
	vector<string> vecStr;
	string str;
	while(cin>>str)
	{
		vecStr.push_back(str);
	}
	try{
		cout<<CalcInt(vecStr)<<endl;
	}
	catch(out_of_range err)
	{
		cout<<err.what()<<endl;
		cout<<"转换整型失败！"<<endl;
	}
	
	vecStr.clear();
	cin.clear();
	while(cin>>str)
	{
		vecStr.push_back(str);
	}
	try{
		cout<<CalcDou(vecStr)<<endl;
	}
	catch(out_of_range err)
	{
		cout<<err.what()<<endl;
		cout<<"转换整型失败！"<<endl;
	}
	
	return 0;
}
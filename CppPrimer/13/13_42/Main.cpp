#include"TextQuery.h"
using std::cin;
using std::cout;
using std::string;

int main()
{
	TextQuery textquery("input.txt");
	string str;
	while (cin >> str)
	{
		auto res = textquery.query(str);
		Print(cout, res);
	}

}
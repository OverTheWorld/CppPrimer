#include"String.h"

using std::cout;
using std::endl;

int main()
{
	String str("123123123");
	cout << str << endl;
	String str1 = str;
	cout << str1 << endl;
	String str2;
	cout << str2.size() << endl;
	str2 = str1;
	cout << str1 << endl;
	String str4("qweradsfzxcv");
	str1 = str4;
	cout << str4 << endl;
	cout << str1 << endl;
	system("pause");
}
#include<iostream>
#include<string>
#include"Folders.h"
#include"Message.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	Folders f1, f2, f3;
	Message m1("str1"), m2("str2");
	m1.addFolders(f1);
	m1.addFolders(f2);
	m2.addFolders(f2);
	m2.addFolders(f3);
	f1.Print();
	f2.Print();
	f3.Print();
	Message m3 = m1;
	f1.Print();
	f2.Print();
	f3.Print();
	m1 = m2;
	f1.Print();
	f2.Print();
	f3.Print();
	system("pause");

}
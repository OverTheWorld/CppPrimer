#include<iostream>
#include<string>
#include<forward_list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::forward_list;

void fInsert(forward_list<string> &flistStr,const string &str1,const string &str2)
{
	bool bflag = false;
	auto prev = flistStr.cbefore_begin();
	auto curr = flistStr.cbegin();
	while(curr != flistStr.end())
	{
		if(*curr == str1)
		{
			curr = flistStr.insert_after(curr,str2);
			bflag = true;
		}
		prev = curr;
		++curr;
	}
	if(!bflag)
	{
		flistStr.insert_after(prev,str2);
	}
}

int main()
{
	forward_list<string> flistStr = {"1","2","3","4","6","7"};
	
	fInsert(flistStr,"8","9");
	
	for(const auto &s : flistStr)
	{
		cout<<s<<" ";
	}
	cout<<endl;
	return 0;
}


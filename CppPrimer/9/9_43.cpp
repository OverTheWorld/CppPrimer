#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void strReplace(string &s,const string &oldVal,const string &newVal)
{
	auto iter = s.begin();
	
	while(iter != s.end())
	{
		if(*iter == oldVal.at(0))
		{
			unsigned i = 1;
			while(i != oldVal.size())
			{
				if(*(iter+i) == oldVal.at(i))
				{
					++i;
				}
				else
				{
					break;
				}
			}
			if(i == oldVal.size())
			{
				iter = s.erase(iter,iter+i);
				iter = s.insert(iter,newVal.begin(),newVal.end());
				iter += newVal.size();
			}
			else
			{
				++iter;
			}
		}
		else
		{
			++iter;
		}
	}
}

int main()
{
	string s("My tho and thruall in this");
	strReplace(s,"tho","though");
	cout<<s<<endl;
	strReplace(s,"thru","through");
	cout<<s<<endl;
	
	return 0;
}

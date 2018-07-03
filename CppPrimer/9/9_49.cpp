#define NDEBUG

#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<cctype>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::out_of_range;
using std::fstream;
using std::ifstream;
using std::ofstream;

int main()
{
	ifstream ifs("input.txt");
	const string strMode("aceimnorstuvwxz");
	const string strAlpha("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	string str;
	string strResult;
	unsigned len = 0;
	while(getline(ifs,str))
	{
		unsigned pos = 0;
		while((pos = str.find_first_of(strMode,pos))!=string::npos)
		{
			unsigned i = pos +1;
			if(pos == 0 || !isalpha(str.at(pos-1)))
			{
				while(i != str.size() && i == str.find_first_of(strMode,i))
					++i;
				if(i == str.size() || !isalpha(str.at(i)))
				{
					if(i-pos > len)
					{
						strResult = str.substr(pos,i-pos);
						len = i - pos;
						#ifdef NDEBUG
						cout<<strResult<<endl;
						cout<<len<<endl;
						#endif
					}
				}
			}
			pos = str.find_first_not_of(strAlpha,pos);
			#ifdef NDEBUG
			cout<<pos<<endl;
			cout<<str.at(pos)<<endl;
			#endif
			if(pos == string::npos)
			{
				break;
			}
		}
	}
	cout<<strResult<<endl;
	#ifdef NDEBUG
	cout<<len<<endl;
	#endif
	return 0;
}
#include<iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ends;
using std::unitbuf;
using std::nounitbuf;
using std::flush;

int main()
{
	cout<<"hi"<<flush;
	cout<<"hi"<<endl;
	cout<<"hi"<<ends;
	cout<<unitbuf;
	cout<<"1234567897654321";
	cout<<nounitbuf;
	
	cout<<endl;
	
	cout<<"12343";
	cerr<<"cerr";
	cout<<endl;
	
	return 0;
	
}

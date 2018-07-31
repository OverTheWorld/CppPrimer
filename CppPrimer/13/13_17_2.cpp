#include<iostream>

using std::cout;
using std::cin;
using std::endl;

class numbered{
	static int count;
	public:
	int mysn;
	numbered(){mysn = count++;}
	numbered(const numbered&) {mysn = count++;}
};

int numbered::count = 1;

void f(numbered s){cout<<s.mysn<<endl;}

int main()
{
	numbered a,b=a,c=b;
	f(a);
	f(b);
	f(c);
}
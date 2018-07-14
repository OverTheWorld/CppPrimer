#include<iostream>
#include<memory>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

void connection()
{
	cout<<"connecting"<<endl;
}
void disconnection()
{
	cout<<"disconnection"<<endl;
}
struct ConStr
{
	string str;
};

void endConnection(ConStr *constr)
{
	disconnection();
}

int main()
{
	auto c = ConStr();
	shared_ptr<ConStr> pCon(&c,endConnection);
	connection();
}
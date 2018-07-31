#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class HasPtr
{
public:
	HasPtr(const string &s = string()):
		ps(new string(s)),i(0),use(new size_t(1)){}
	HasPtr(const HasPtr &h):
		ps(h.ps),i(h.i),use(h.use){++*use;}
	~HasPtr();
	HasPtr& operator=(HasPtr &h);
	
	void Print()const;
	
private:
	string *ps;
	int i;
	size_t *use;
};
HasPtr::~HasPtr()
{
	if(--*use == 0)
	{
		cout<<"delete "<<*ps<<endl;
		delete ps;
		delete use;
	}
}
void HasPtr::Print()const
{
	cout<<"string:"<<*ps<<endl;
	cout<<"i:"<<i<<endl;
}
HasPtr& HasPtr::operator=(HasPtr &h)
{
	++*h.use;
	if(--*use == 0)
	{
		delete ps;
		delete use;
	}
	ps = h.ps;
	use = h.use;
	i = h.i;
	return *this;
}

int main()
{
	HasPtr h1("string");
	{
		h1.Print();
		HasPtr h3 = h1;
		h3.Print();
		HasPtr h2("hhhhhhhh");
		h1 = h2;
		h2.Print();
	}
	h1.Print();
}
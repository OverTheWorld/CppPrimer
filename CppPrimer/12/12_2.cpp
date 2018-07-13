#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<stdexcept>
#include<initializer_list>
#include<algorithm>

using std::runtime_error;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::initializer_list;

class StrBlob
{
	public:
	StrBlob();
	StrBlob(initializer_list<string> il);
	using size_type = vector<string>::size_type;
	size_type size()const{return data->size();}
	bool empty()const{return data->empty();}
	void push_back(const string &str){data->push_back(str);}
	void pop_back();
	string front()const;
	string back()const;
	private:
	shared_ptr<vector<string>> data;
	void check(size_type num,const string &strError)const;
};
StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
void StrBlob::check(size_type num,const string &strError)const
{
	if(num>=data->size())
		throw runtime_error(strError);
}
void StrBlob::pop_back()
{
	check(0,"can't pop item cause size is zero");
	data->pop_back();
}
string StrBlob::front()const
{
	check(0,"size si zero");
	return data->front();
}
string StrBlob::back()const
{
	check(0,"size is zero");
	return data->back();
}

int main()
{
	initializer_list<string> il = {"123","456","7890"};
	StrBlob strblob(il);
	cout<<"size : "<<strblob.size()<<endl;
	cout<<strblob.front()<<"   "<<strblob.back()<<endl;
	strblob.push_back("qwe");
	while(!strblob.empty())
	{
		cout<<strblob.back()<<endl;
		strblob.pop_back();
	}
	
}

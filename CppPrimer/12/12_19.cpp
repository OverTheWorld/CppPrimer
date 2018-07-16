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
using std::weak_ptr;
using std::make_shared;
using std::initializer_list;

class StrBlobPtr;

class StrBlob
{
	friend class StrBlobPtr;
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

class StrBlobPtr
{
	public:
	StrBlobPtr(StrBlob *pstrblob,size_t cur = 0):wpdata(pstrblob->data),curr(cur){}
	StrBlobPtr():curr(0),wpdata(){}
	~StrBlobPtr(){curr = 0;}
	string& deref(){return check(curr);}
	string& addself(){return check(++curr);}
	private:
	string& check(size_t site)
	{
		auto pdata = wpdata.lock();
		if(!pdata)
			throw runtime_error("Fail to lock shared_ptr");
		if(site >= pdata->size())
			throw runtime_error("site is illegal");
		return pdata->at(site);
	}
	size_t curr;
	weak_ptr<vector<string>> wpdata;
};

int main()
{
	initializer_list<string> il = {"123","456","7890"};
	StrBlob strblob(il);
	StrBlobPtr pstrblob(&strblob);
	cout<<pstrblob.deref()<<endl;
	cout<<pstrblob.addself()<<endl;
	cout<<pstrblob.addself()<<endl;
}

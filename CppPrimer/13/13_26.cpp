#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include<initializer_list>
#include<stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::out_of_range;
using std::initializer_list;

class StrBlob
{
public:
	using size_type = vector<string>::size_type;
	
	StrBlob():sptrVecStr(make_shared<vector<string>>()){};
	StrBlob(initializer_list<string> il):
	sptrVecStr(make_shared<vector<string>>(il)){}
	
	//拷贝控制成员
	StrBlob(const StrBlob& blob):
	sptrVecStr(make_shared<vector<string>>(*blob.sptrVecStr)){}
	StrBlob& operator=(const StrBlob& blob)
	{
		auto tempSharedPtr = blob.sptrVecStr;
		sptrVecStr = make_shared<vector<string>>(*tempSharedPtr);
		return *this;
	}
	
	size_type size()const{return sptrVecStr->size();}
	bool empty()const{return sptrVecStr->empty();}
	void push_back(const string &s){sptrVecStr->push_back(s);}
	void pop_back(){check(size()-1);sptrVecStr->pop_back();};
	string &front(){check(0);return sptrVecStr->front();};
	string &back(){check(size()-1);return sptrVecStr->back();};
	vector<string>::iterator begin(){return sptrVecStr->begin();}
	vector<string>::iterator end(){return sptrVecStr->end();}
private:
	shared_ptr<vector<string>> sptrVecStr;
	void check(size_type i)const
	{
		if(i >= size())
			throw out_of_range("数组越界");
	}
};

StrBlob& getBlob(StrBlob& blob){return blob;}

int main()
{
	StrBlob blob = {"123","456","789","0"};
	blob = getBlob(blob);
	StrBlob blob1 = blob;
	blob1.front() = "ads";
	for_each(blob.begin(),blob.end(),
	[](const string &s)
	{
		cout<<s<<endl;
	}
	);
	for_each(blob1.begin(),blob1.end(),
	[](const string &s)
	{
		cout<<s<<endl;
	}
	);
}
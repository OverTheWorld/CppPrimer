#include "StrVec.h"
#include<utility>
#include<algorithm>

using std::string;
using std::pair;
using std::uninitialized_copy;
using std::for_each;

StrVec::StrVec(const StrVec& s)
{
	auto pa = alloc_n_copy(s.begin(), s.end());
	element = pa.first;
	cap = first_free = pa.second;
}

StrVec::StrVec(std::initializer_list<string> il)
{
	auto pa = alloc_n_copy(il.begin(), il.end());
	element = pa.first;
	cap = first_free = pa.second;
}

StrVec& StrVec::operator=(const StrVec& s)
{
	auto pa = alloc_n_copy(s.begin(), s.end());
	free();
	element = pa.first;
	cap = first_free = pa.second;
	return *this;
}

StrVec::~StrVec()
{
	free();
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
	auto newdata = alloc.allocate(e - b);
	return pair<string*, string*>(newdata, uninitialized_copy(b, e, newdata));
}
void StrVec::reallocate()
{
	auto newsize = size() ? size() * 2 : 1;
	auto newdata = alloc.allocate(newsize);
	auto dest = newdata;
	auto elem = element;
	for (size_t i = 0; i != size(); ++i)
	{
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	element = newdata;
	first_free = dest;
	cap = newdata + newsize;
}
void StrVec::free()
{
	if (element)
	{
		for_each(element, first_free, [](string &str) {alloc.destroy(&str); });
		alloc.deallocate(element, capacity());
	}
}
void StrVec::push_back(const string &str)
{
	chk_n_alloc();
	alloc.construct(first_free++, str);
}
std::allocator<std::string> StrVec::alloc;
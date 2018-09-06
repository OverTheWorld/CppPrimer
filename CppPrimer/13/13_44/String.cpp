#include "String.h"
#include<string.h>
#include<algorithm>
using std::for_each;
using std::allocator;
using std::cout;
using std::ostream;
using std::istream;

allocator<char> String::alloc;

String::String(const char *pString) :
	length(strlen(pString)), data(nullptr)
{
	if (!pString)return;
	data = alloc.allocate(length + 1);
	auto pdata = data;
	while (*pString != '\0')
	{
		alloc.construct(pdata, *pString);
		++pdata;
		++pString;
	}
	alloc.construct(data+length, '\0');
}

String::String(const String &rhs) :
	length(rhs.length)
{
	if (length == 0)
	{
		data = nullptr;
		return;
	}
	data = alloc.allocate(length + 1);
	for (auto i = 0; i != length+1; ++i)
	{
		alloc.construct(data + i, *(rhs.data + i));
	}
}

String::~String()
{
	if (data == nullptr)return;
	for (auto iter = data; *iter != '\0'; ++iter)
	{
		alloc.destroy(iter);
	}
	alloc.destroy(data + length);
	alloc.deallocate(data, length + 1);
}
String& String::operator=(String &t)
{
	char* pdata = nullptr;
	if (t.data != nullptr)
	{
		pdata = alloc.allocate(t.length + 1);
		for (size_t i = 0; i != t.length + 1; ++i)
		{
			alloc.construct(pdata + i, *(t.data + i));
		}
	}
	for (size_t i = 0; i != length; ++i)
	{
		alloc.destroy(data + i);
	}
	alloc.deallocate(data, length);
	data = pdata;
	length = t.length;
	return *this;
}

ostream& operator<<(ostream &os, const String &rhs)
{
	return os << rhs.data ;
}
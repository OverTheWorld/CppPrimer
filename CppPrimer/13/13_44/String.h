#pragma once
#include<memory>
#include<iostream>


class String
{
	friend std::ostream& operator<<(std::ostream &os, const String &rhs);
private:
	static std::allocator<char> alloc;
	char *data;
	size_t length;
public:
	String& operator=(String &rhs);
	String() :data(nullptr),length(0) {}
	String(const String &rhs);
	String(const char *pString);
	~String();
	size_t size()const noexcept { return length; }
};

std::ostream& operator<<(std::ostream &os, const String &rhs);
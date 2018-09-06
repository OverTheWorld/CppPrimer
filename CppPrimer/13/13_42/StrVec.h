#pragma once
#include<memory>
#include<string>
#include<initializer_list>
class StrVec
{
public:
	StrVec() :element(nullptr), first_free(nullptr), cap(nullptr) {};
	StrVec(const StrVec& s);
	StrVec(std::initializer_list<std::string> il);
	~StrVec();
	StrVec& operator=(const StrVec& s);
	size_t size()const { return first_free - element; }
	size_t capacity()const { return cap - element; }
	std::string* begin()const { return element; }
	std::string* end()const { return first_free; }
	void push_back(const std::string &str);
	std::string& at(size_t i) { if (i < size()) { return element[i]; } }
private:
	static std::allocator<std::string> alloc;
	std::string *element, *first_free, *cap;
	void free();
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string *b, const std::string *e);
	void chk_n_alloc() { if (cap == first_free)reallocate(); };
	void reallocate();
};



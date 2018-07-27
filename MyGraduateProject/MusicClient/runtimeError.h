#pragma once
#include"CharConvert.h"
#include<stdexcept>

using std::runtime_error;

class runtimeError :
	public runtime_error
{
public:
	runtimeError(const wstring& str);
	~runtimeError();
	wstring getWhat();
};


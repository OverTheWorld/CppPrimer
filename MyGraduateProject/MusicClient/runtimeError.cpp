#include "runtimeError.h"


runtimeError::runtimeError(const wstring& str) :runtime_error(wcTomt(str))
{
}


runtimeError::~runtimeError() 
throw ()
{
}

wstring runtimeError::getWhat()
{
	return mtTowc(what());
}
#include"CharConvert.h"

const string wcTomt(const wstring& str)
{
	BOOL bFail = FALSE;
	unsigned len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	LPSTR pStr = NULL;
	//分配内存
	pStr = (LPSTR)malloc(len+1);
	//此处先不考虑内存分配失败
	len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), pStr, len, NULL, &bFail);
	pStr[len] = '\0';
	//先不考虑执行失败情况
	string nstr(pStr);
	free(pStr);
	return nstr;
}

const wstring mtTowc(const string& str)
{
	BOOL bFail = FALSE;
	unsigned len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	LPWSTR pwStr = NULL;
	pwStr = (LPWSTR)malloc(sizeof(WCHAR)*(len+1));
	//先不考虑执行失败的情况
	len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pwStr, len);
	pwStr[len] = L'\0';
	//同样先不考虑执行失败的情况
	wstring wstr(pwStr);
	free(pwStr);
	return wstr;
}
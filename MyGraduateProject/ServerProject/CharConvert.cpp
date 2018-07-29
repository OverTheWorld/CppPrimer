#include"CharConvert.h"

const string wcTomt(const wstring& str)
{
	BOOL bFail = FALSE;
	unsigned len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	LPSTR pStr = NULL;
	//�����ڴ�
	pStr = (LPSTR)malloc(len+1);
	//�˴��Ȳ������ڴ����ʧ��
	len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), pStr, len, NULL, &bFail);
	pStr[len] = '\0';
	//�Ȳ�����ִ��ʧ�����
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
	//�Ȳ�����ִ��ʧ�ܵ����
	len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), pwStr, len);
	pwStr[len] = L'\0';
	//ͬ���Ȳ�����ִ��ʧ�ܵ����
	wstring wstr(pwStr);
	free(pwStr);
	return wstr;
}
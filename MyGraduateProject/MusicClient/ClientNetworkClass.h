#pragma once
#include<winsock2.h>
#include<mysql.h>
#include"CharConvert.h"
#include<fstream>
#include<vector>
#include<list>
using std::list;
using std::vector;
using std::ofstream;

class ClientNetworkClass
{
private:
	const string strSaveSite = "G:/TestFile/";
	SOCKET m_client;
	netProtocol m_netPro;
	void SaveFile(const string &strFileName,const string &strLast);
	void Connection();
public:
	ClientNetworkClass();
	~ClientNetworkClass();
	void GetFile(const wstring &str);
	void vagueQuery(const wstring &str,vector<wstring> &vecStr);
	void SendComment(const wstring &strComment, int time,int SID);
	bool userRegister(const wstring &strName, const wstring &strPassword);
	int userLogin(const wstring &wstrName, const wstring &wstrPassword,int &userId);
	void GetComments(list<CommentClass> &listStrCom,int SID);
	wstring getStrSaveSite()const{ return mtTowc(strSaveSite); }
	int queryID(const wstring& strFileName);
};


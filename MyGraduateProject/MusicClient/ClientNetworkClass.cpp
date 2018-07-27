#include "ClientNetworkClass.h"


ClientNetworkClass::ClientNetworkClass()
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 0);
	WSAStartup(wVersion, &wsaData);
}
ClientNetworkClass::~ClientNetworkClass()
{
	closesocket(m_client);
	WSACleanup();
}
void ClientNetworkClass::SaveFile(const string &strFileName,const string &strLast)
{
	string str = strSaveSite + strFileName + strLast;
	ofstream ofs(str, std::ios::out | std::ios::binary);
	ofs.seekp(std::ios::beg);
	while (recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0) > 0)
	{
		ofs.write(m_netPro.szText, m_netPro.len);
		if (m_netPro.len != 512)
			break;
	}
	printf("Music is Ok!\n");
}
void ClientNetworkClass::GetFile(const wstring &strFile)
{
	Connection();
	m_netPro.message = NM_downloadFile;
	string str = wcTomt(strFile);
	memcpy(m_netPro.szText, str.c_str(), str.size());
	m_netPro.szText[str.size()] = '\0';
	m_netPro.len = str.size() + 1;
	send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0);
	SaveFile(str, ".mp3");
	SaveFile(str, ".lyric");
}
void ClientNetworkClass::vagueQuery(const wstring &str,vector<wstring> &vecStr)
{
	Connection();
	string strSql = wcTomt(str);
	m_netPro.message = NM_query;
	memcpy(m_netPro.szText, strSql.c_str(), strSql.size());
	m_netPro.szText[strSql.size()] = '\0';
	m_netPro.len = strSql.size() + 1;
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
	}
	if (SOCKET_ERROR == recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
	}
	int len = m_netPro.len;
	for (int i = 0; i != len; ++i)
	{
		if (SOCKET_ERROR == recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0))
		{
			MessageBox(0, 0, 0, 0);
		}
		vecStr.emplace_back(mtTowc(m_netPro.szText));
		memset(&m_netPro, 0, sizeof(m_netPro));
	}
}
void ClientNetworkClass::SendComment(const wstring &strComment, int time,int SID)
{
	Connection();
	string str = wcTomt(strComment);
	m_netPro.message = NM_comment;
	memcpy(m_netPro.szText, str.c_str(), str.size());
	m_netPro.szText[str.size()] = '\0';
	m_netPro.len = str.size() + 1;
	int *plen = (int *)&m_netPro.szText[m_netPro.len];
	*plen = time;
	int *p = (int *)&m_netPro.szText[m_netPro.len + 4];
	*p = SID;
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
}
void ClientNetworkClass::GetComments(list<CommentClass> &listStrCom,int SID)
{
	listStrCom.clear();
	Connection();
	CommentClass cc;
	CommentStruct *pcs = NULL;
	m_netPro.message = NM_downloadComment;
	m_netPro.len = SID;
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0))
	{
		//post an error
	}
	while (recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0) > 0)
	{
		if (m_netPro.message == NM_END)
			break;
		else if (m_netPro.message == NM_downloadComment)
		{
			pcs = (CommentStruct*)m_netPro.szText;
			cc.time = pcs->time;
			cc.strComment = mtTowc(pcs->szText);
			listStrCom.push_back(cc);
		}
	}
}
bool ClientNetworkClass::userRegister(const wstring &userName, const wstring &userPassword)
{
	Connection();
	string strName = wcTomt(userName);
	string strPassword = wcTomt(userPassword);
	userStruct user;
	memcpy(user.userName, strName.c_str(), strName.size());
	user.userName[strName.size()] = '\0';
	memcpy(user.userPassword, strPassword.c_str(), strPassword.size());
	user.userPassword[strPassword.size()] = '\0';
	memcpy(m_netPro.szText, &user, sizeof(user));
	m_netPro.message = NM_register;
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	if (recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0) <= 0)
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	if (m_netPro.len == 1)
		return true;
	else
		return false;
}
int ClientNetworkClass::userLogin(const wstring &wstrName, const wstring &wstrPassword,int &userId)
{
	Connection();
	string strName = wcTomt(wstrName), strPassword = wcTomt(wstrPassword);
	m_netPro.message = NM_login;
	userStruct *pus = (userStruct*)m_netPro.szText;
	memcpy(pus->userName, strName.c_str(), strName.size());
	pus->userName[strName.size()] = '\0';
	memcpy(pus->userPassword, strPassword.c_str(), strPassword.size());
	pus->userPassword[strPassword.size()] = '\0';
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	int res;
	if ((res = recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0)) <= 0)
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	int *p = (int *)(m_netPro.szText + sizeof(userStruct));
	if (m_netPro.len == 1)
	{
		userId = *p;
		return 1;
	}
	else if (m_netPro.len == 0)
	{
		return 0;//password wrong
	}
	else if (m_netPro.len == -1)
	{
		return -1;//user does not exist
	}
	return -2;
}
int ClientNetworkClass::queryID(const wstring& strFileName)
{
	Connection();
	string str = wcTomt(strFileName);
	memcpy(m_netPro.szText, str.c_str(), str.size());
	m_netPro.szText[str.size()] = '\0';
	m_netPro.message = NM_queryID;
	if (SOCKET_ERROR == send(m_client, (const char*)&m_netPro, sizeof(m_netPro),0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	if (recv(m_client, (char*)&m_netPro, sizeof(m_netPro), 0) <= 0)
	{
		MessageBox(0, 0, 0, 0);;
		//post an error
	}
	return m_netPro.len;
}
void ClientNetworkClass::Connection()
{
	m_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (!m_client)
	{
		//throw an error
	}
	sockaddr_in sock;
	sock.sin_family = AF_INET;
	sock.sin_port = htons(4444);
	sock.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(m_client, (sockaddr*)&sock, sizeof(sock)) == SOCKET_ERROR)
	{
		//throw an error
	}
	sockaddr_in sockServer;
	sockServer.sin_family = AF_INET;
	sockServer.sin_port = htons(8888);
	sockServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(m_client, (sockaddr*)&sockServer, sizeof(sockServer)) == SOCKET_ERROR)
	{
		//post an error
	}
}
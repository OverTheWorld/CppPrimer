#pragma once
#include<winsock2.h>
#include<mysql.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<winsock2.h>
#include<mysql.h>
#include"CharConvert.h"
#include<fstream>
#include<cstdlib>

using std::ifstream;
using std::to_string;

class ServerNetworkClass
{
private:
	const string cstrUserTable = "userTable";
	const string cstrMusicTable = "MusicTable";
	const string cprestrComment = "Comment";
	MYSQL *m_con;
	MYSQL_RES *m_result;
	const short m_port = 8888;
	SOCKET m_socket;
	netProtocol m_netprotocol;

	void SendFile(string strFileSite, SOCKET client);
	void SendComments(int SID,SOCKET client);
public:
	ServerNetworkClass();
	~ServerNetworkClass();
	void ProcessingMessage();
	void DownloadFile(SOCKET client);
	void vagueQuery(SOCKET client);
	void getComment(SOCKET client);
	void userRegister(SOCKET client);
	void userLogin(SOCKET client);
	void queryID(SOCKET client);
};


#include "ServerNetworkClass.h"


ServerNetworkClass::ServerNetworkClass()
{
	// initialize win sock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 0);
	WSAStartup(wVersion, &wsaData);
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		WSACleanup();
		//post an error
	}
	sockaddr_in sockadd;
	sockadd.sin_family = AF_INET;
	sockadd.sin_port = htons(m_port);
	sockadd.sin_addr.S_un.S_addr = INADDR_ANY;
	if (SOCKET_ERROR == bind(m_socket, (sockaddr*)&sockadd, sizeof(sockadd)))
	{
		WSACleanup();
		//post an error
	}
	if (SOCKET_ERROR == listen(m_socket, 2))
	{
		WSACleanup();
		//post an error
	}
	//initialize mysql
	m_con = mysql_init(NULL);
	if (!m_con)
	{
		// post an error
	}
	if (mysql_real_connect(m_con, "localhost", "root", "123456", NULL, 0, NULL, 0) == NULL)
	{
		//post an error
	}
	if (mysql_set_character_set(m_con, "gbk"))
	{
		//post an error
	}
	if (mysql_query(m_con, "use serverdatabase"))
	{
		//post an error
	}
}
ServerNetworkClass::~ServerNetworkClass()
{
	if (m_result)
	{
		mysql_free_result(m_result);
	}
	if (m_con)
	{
		mysql_close(m_con);
	}
	closesocket(m_socket);
	WSACleanup();
}
void ServerNetworkClass::ProcessingMessage()
{
	SOCKET client;
	sockaddr_in clientadd;
	int nlen = sizeof(clientadd);
	while (true)
	{
		client = accept(m_socket, (sockaddr*)&clientadd, &nlen);
		if (client == INVALID_SOCKET)
		{
			//post an error
			continue;
		}
		int ilength = recv(client, (char*)&m_netprotocol, sizeof(m_netprotocol), 0);
		switch (m_netprotocol.message)
		{
		case NM_queryID:
			queryID(client);
			break;
		case NM_downloadFile:
			DownloadFile(client);
			break;
		case NM_query:
			vagueQuery(client);
			break;
		case NM_comment:
			getComment(client);
			break;
		case NM_login:
			userLogin(client);
			break;
		case NM_register:
			userRegister(client);
			break;
		case NM_downloadComment:
			SendComments(m_netprotocol.len, client);
			break;
		}
		closesocket(client);
	}
}
void ServerNetworkClass::DownloadFile(SOCKET client)
{
	int SID;
	string strSql = "select * from MusicTable where MusicName = ";
	string strFileSite,strLyricSite;
	strSql = strSql +"'"+m_netprotocol.szText+"'";
	if (mysql_query(m_con, strSql.c_str()))
	{
		// post an error
		MessageBox(0, 0, 0, 0);
	}
	if (NULL == (m_result = mysql_store_result(m_con)))
	{
		// post an error
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(m_result))
	{
		SID = atoi(row[0]);
		strFileSite = row[2];
		strLyricSite = row[4];
	}
	SendFile(strFileSite, client);
	SendFile(strLyricSite, client);
	mysql_free_result(m_result);
	m_result = NULL;
	//SendComments(SID, client);
}
void ServerNetworkClass::SendFile(string strFileSite, SOCKET client)
{
	ifstream ifs(strFileSite.c_str(), std::ios::binary | std::ios::in);
	if (!ifs.good())
	{
		MessageBox(0, 0, 0, 0);
	}
	ifs.seekg(std::ios::beg);
	netProtocol netPro;
	netPro.message = NM_downloadFile;
	while (ifs.read(netPro.szText, 512))
	{
		netPro.len = ifs.gcount();
		if (send(client, (const char*)&netPro, sizeof(netPro), 0) == SOCKET_ERROR)
		{
			MessageBox(0, L"Fail to send!", 0, 0);
			//post an error
		}
		memset(netPro.szText, 0, sizeof(netPro.szText));
	}
	if (ifs.eof())
	{
		netPro.len = ifs.gcount();
		if (send(client, (const char*)&netPro, sizeof(netPro), 0) == SOCKET_ERROR)
		{
			MessageBox(0, L"Fail to Send!", 0, 0);
			//post an error
		}
	}
	ifs.close();
}
void ServerNetworkClass::vagueQuery(SOCKET client)
{
	string str(m_netprotocol.szText);
	string strSql = "select * from ";
	strSql = strSql + cstrMusicTable + " where MusicName like '" + str + "%'";
 	if (mysql_query(m_con, strSql.c_str()))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	m_result = mysql_store_result(m_con);
	if (!m_result)
	{
		//post an error
		MessageBox(0, 0, 0, 0);
	}
	netProtocol netPro;
	MYSQL_ROW row;
	netPro.message = NM_query;
	netPro.len = mysql_num_rows(m_result);
	if (SOCKET_ERROR == send(client, (const char*)&netPro, sizeof(netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
		// post an error;
	}
	while (row = mysql_fetch_row(m_result))
	{
		netPro.len = strlen(row[1])+1;
		memcpy(netPro.szText, row[1], netPro.len);
		send(client, (const char*)&netPro, sizeof(netPro), 0);
	}
	mysql_free_result(m_result);
	m_result = NULL;
}
void ServerNetworkClass::getComment(SOCKET client)
{
	int *p = (int *)&m_netprotocol.szText[m_netprotocol.len];
	int time = *p;
	int SID = *(p+1);
	string strTable = cprestrComment + to_string(SID);
	string strSql = "create table if not exists " + strTable + "(time int,comment varchar(50))";
	if (mysql_query(m_con, strSql.c_str()))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	strSql = "insert into ";
	strSql = strSql + strTable + " values(" + to_string(time) + ",'" + m_netprotocol.szText + "')";
	if (mysql_query(m_con, strSql.c_str()))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
}
void ServerNetworkClass::SendComments(int SID,SOCKET client)
{
	netProtocol netPro;
	if (SID != 0)
	{
		string strTable = cprestrComment + to_string(SID);
		string strSql = "select * from " + strTable + " order by time asc";
		if (mysql_query(m_con, strSql.c_str()))
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}
		m_result = mysql_store_result(m_con);
		if (!m_result)
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}
		CommentStruct cs;
		MYSQL_ROW row;
		int i = 0;
		netPro.message = NM_downloadComment;
		while (row = mysql_fetch_row(m_result))
		{
			cs.time = atoi(row[0]);
			memcpy(cs.szText, row[1], strlen(row[1]));
			cs.szText[strlen(row[1])] = '\0';
			memcpy(netPro.szText, &cs, sizeof(cs));
			if (SOCKET_ERROR == send(client, (const char*)&netPro, sizeof(netPro), 0))
			{
				MessageBox(0, 0, 0, 0);
				//post an error
			}
		}
	}
	netPro.message = NM_END;
	if (SOCKET_ERROR == send(client, (const char*)&netPro, sizeof(netPro), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	mysql_free_result(m_result);
	m_result = NULL;
}
void ServerNetworkClass::userRegister(SOCKET client)
{
	userStruct *pus = (userStruct*)m_netprotocol.szText;
	string strSql = "insert into ";
	strSql = strSql + cstrUserTable + "(userName,password) values('" + pus->userName + "','" + pus->userPassword + "')";
	m_netprotocol.message = NM_register;
	if (mysql_query(m_con, strSql.c_str()))
	{
		m_netprotocol.len = 0;
	}
	else
		m_netprotocol.len = 1;
	if (SOCKET_ERROR == send(client, (const char*)&m_netprotocol, sizeof(m_netprotocol),0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}

}
void ServerNetworkClass::userLogin(SOCKET client)
{
	userStruct *pus = (userStruct*)m_netprotocol.szText;
	string strSql = "select * from ";
	strSql = strSql + cstrUserTable + " where userName = '" + pus->userName + "'";
	if (mysql_query(m_con, strSql.c_str()))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	m_result = mysql_store_result(m_con);
	if (!m_result)
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	int resNum = mysql_num_rows(m_result);
	if (resNum == 0)
	{
		m_netprotocol.len = -1;//user does not exist
	}
	int *p = (int *)(m_netprotocol.szText + sizeof(userStruct));
	MYSQL_ROW row;
	string strPassword;
	while (row = mysql_fetch_row(m_result))
	{
		*p = atoi(row[0]);
		strPassword = row[2];
	}
	if (strPassword == pus->userPassword)
	{
		m_netprotocol.len = 1;
	}
	else if (resNum != 0)
	{
		m_netprotocol.len = 0;
	}
	if (SOCKET_ERROR == send(client, (const char*)&m_netprotocol, sizeof(m_netprotocol), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	mysql_free_result(m_result);
	m_result = NULL;
	
}
void ServerNetworkClass::queryID(SOCKET client)
{
	string strSql = "select * from ";
	strSql = strSql + cstrMusicTable + " where MusicName = '" + m_netprotocol.szText+"'";
	if (mysql_query(m_con, strSql.c_str()))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
	m_result = mysql_store_result(m_con);
	if (!m_result)
	{
		MessageBox(0, 0, 0, 0);
	}

	MYSQL_ROW row;
	while (row = mysql_fetch_row(m_result))
	{
		m_netprotocol.len = std::stoi(row[0]);
	}

	if (SOCKET_ERROR == send(client, (const char*)&m_netprotocol, sizeof(m_netprotocol), 0))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}

	mysql_free_result(m_result);
	m_result = NULL;
}

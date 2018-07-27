#pragma once
#include<winsock2.h>
#include<mysql.h>
#include<my_global.h>
#include"runtimeError.h"
#include"MusicFile.h"
#include<vector>
#include<list>
using std::to_string;
using std::vector;
using std::list;
class DataBaseClass
{
private:
	const string m_strDataBase = "ClientDataBase";
	MYSQL* m_con;
	MYSQL_RES *m_result;
	string m_strTable;
public:
	DataBaseClass(int userId);
	~DataBaseClass();
	void Query(const string &str);
	void getData(list<MusicFile> & listMusicFile);
	bool insertData(const MusicFile &mf);
	void deleteData(const MusicFile &mf);
};

extern DataBaseClass *g_pDataBaseClass;


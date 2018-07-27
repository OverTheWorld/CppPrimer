#include "DataBaseClass.h"


DataBaseClass::DataBaseClass(int userId) 
{
	m_result = NULL;
	string strSql;
	m_strTable = string("Table") + to_string(userId);
	m_con = mysql_init(NULL);
	if (!m_con)
	{
		throw runtimeError(L"Fail to Init Database Class!");
	}
	if (!mysql_real_connect(m_con, "localhost", "root", "123456", NULL, 0, NULL, 0))
	{
		throw runtimeError(L"Fail to Connect!");
	}
	if (mysql_set_character_set(m_con, "gbk"))
	{
		throw runtimeError(L"Fail to set character!");
	}
	strSql = strSql + "create database if not exists " + m_strDataBase;
	if (mysql_query(m_con, strSql.c_str()))
	{
		throw runtimeError(L"Fail to Create DataBase!");
	}
	strSql = "use ";
	strSql = strSql + m_strDataBase;
	if (mysql_query(m_con, strSql.c_str()))
	{
		throw runtimeError(L"Fail to use database");
	}
	strSql = "create table if not exists ";
	m_strTable = "table" + to_string(userId);
	strSql = strSql + m_strTable+"(SID INT,MusicName varchar(30),MusicSite varchar(50) unique,LyricSite varchar(50),LyricName varchar(30))";
	if (mysql_query(m_con, strSql.c_str()))
	{
		throw runtimeError(L"Fail to Create Table!");
	}
}
DataBaseClass::~DataBaseClass()
{
	if (m_result)
	{
		mysql_free_result(m_result);
	}
	if (m_con)
	{
		mysql_close(m_con);
	}
}
void DataBaseClass::getData(list<MusicFile> & listMusicFile)
{
	string strSql = "select * from "+m_strTable;
	if (mysql_query(m_con, strSql.c_str()))
	{
		throw runtimeError(L"Fail to Query !");
	}
	m_result = mysql_store_result(m_con);
	if (m_result == NULL)
	{
		throw runtimeError(L"Fail to Store result!");
	}
	int numField = mysql_num_fields(m_result);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(m_result))
	{
		MusicFile mf(mtTowc(row[2]), mtTowc(row[1]));
		mf.SetSiteLyricName(mtTowc(row[4]));
		mf.SetStrLyricSite(mtTowc(row[3]));
		mf.SetSID(atoi(row[0]));
		listMusicFile.push_back(mf);
	}
	mysql_free_result(m_result);
	m_result = NULL;
}
bool DataBaseClass::insertData(const MusicFile &mf)
{
	string strSql;
	strSql = strSql + "insert " + m_strTable + " values(" + to_string(mf.getSID()) + ",'" + wcTomt(mf.getStrFileName()) + "','" + wcTomt(mf.getStrFileSite()) + "','" + (mf.getStrLyricSite().empty() ? "NULL" : wcTomt(mf.getStrLyricSite())) + "','" + (mf.getStrLyricName().empty() ? "NULL" : wcTomt(mf.getStrLyricName()))+"')";
	if (mysql_query(m_con, strSql.c_str()))
	{
		return false;
	}
	return true;
}
void DataBaseClass::deleteData(const MusicFile &mf)
{
	string strSql = "delete from ";
	strSql = strSql + m_strTable + " where MusicName = '" + wcTomt(mf.getStrFileName())+"'";
	if (mysql_query(m_con, strSql.c_str()))
	{
		throw runtimeError(L"Fail to delete!");
	}
}

DataBaseClass *g_pDataBaseClass;
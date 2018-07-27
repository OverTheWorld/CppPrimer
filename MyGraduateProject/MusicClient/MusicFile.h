#pragma once
#include"CharConvert.h"
#include<iostream>
using std::wstring;
using std::wistream;
using std::wostream;
using std::string;
class MusicFile
{
	friend wistream& operator>>(wistream& is, MusicFile& mf);
private:
	int SID;
	wstring strFileName;
	wstring strFileSite;
	wstring strLyricSite;
	wstring strLyricName;
	//wstring strTableName;
public:
	MusicFile(const wstring& strFileSite, const wstring& strFileName);
	MusicFile() = default;
	const wstring& getStrFileSite()const { return strFileSite; }
	const wstring& getStrFileName()const { return strFileName; }
	const wstring& getStrLyricSite()const { return strLyricSite; }
	//const wstring& getStrTableName()const{ return strTableName; }
	const wstring& getStrLyricName()const{ return strLyricName; }
	void SetStrLyricSite(const wstring &str){ strLyricSite = str; }
	void SetSiteLyricName(const wstring &str){ strLyricName = str; }
	//void SetTableName(const wstring &str){ strTableName = str; }
	int getSID()const{ return SID; }
	void SetSID(int id){ SID = id; }
};



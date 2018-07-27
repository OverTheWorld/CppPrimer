#include "mciPlayer.h"
#include<sstream>
#include<fstream>
#include<iostream>
#include<direct.h>
#include"runtimeError.h"

using std::wistringstream;
using std::wostringstream;
using std::wstringstream;
using std::ifstream; 
using std::ofstream;
using std::getline;
using std::endl;

mciPlayer::mciPlayer(HWND hwnd) :hwnd(hwnd), ulength(0), volumn(100)
{
	srand(timeGetTime());
	readinList();
	iterNowFile = listMusicFile.begin();
	//打开播放文件
	//openFile();
	state = playSingle;
	playState = Stoped;
}
mciPlayer::~mciPlayer()
{
	if (playState != Stoped)
		closeFile();
	//printoutList();
}
void mciPlayer::readinList()
{
	//初始化list
	//逐行读入文件（空格之前为文件名，之后为文件地址）
	//输入list表中
	//关闭文件
	//setCurDir();
	//ifstream ifs(strInitFileName,std::ios::in);
	//wistringstream iss;
	//string str;
	//wstring wstr;
	//MusicFile mf;
	//while (getline(ifs, str))
	//{
	//	wstr = mtTowc(str);
	//	iss.str(wstr);
	//	iss >> mf;
	//	listMusicFile.push_back(mf);
	//	iss.clear();
	//}
	g_pDataBaseClass->getData(listMusicFile);
}
void mciPlayer::openFile(wstring strDeviceType )
{
	vecLyric.clear();
	if ((*iterNowFile).getStrLyricSite().size() != 0)
	{
		ReadLyric();
	}
	iterLyricNow = vecLyric.begin();
	// load Comment

	openParms.dwCallback = (DWORD)hwnd;
	openParms.lpstrDeviceType = strDeviceType.c_str();
	openParms.lpstrElementName = (*iterNowFile).getStrFileSite().c_str();
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openParms);
	
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	wDeviceId = openParms.wDeviceID;
	setlength();
	setVolumn(volumn);
	playState = pause;

}
void mciPlayer::printoutList()
{
	setCurDir();
	ofstream ofs(strInitFileName, std::ios::out);
	for (const auto& s : listMusicFile)
	{
		if (ofs)
		{
			ofs << wcTomt(s.getStrFileName()) << " " << wcTomt(s.getStrFileSite()) << endl;
		}
		else
		{
			throw runtimeError(L"打开失败!");
		}
	}
}
void mciPlayer::closeFile()
{
	if (playState == Stoped)
		return;
	genericParms.dwCallback = (DWORD)hwnd;
	mciError = mciSendCommand(wDeviceId, MCI_CLOSE, 0, (DWORD_PTR)&genericParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	playState = Stoped;
}
void mciPlayer::Play()
{
	if (playState == Stoped)
	{
		if (listMusicFile.empty())
		{
			return;
		}
		else
		{
			if (iterNowFile == listMusicFile.cend())
			{
				iterNowFile = listMusicFile.cbegin();
			}
			openFile();
		}
	}
	playParms.dwCallback = (DWORD)hwnd;
	mciError = mciSendCommand(wDeviceId, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	playState = playing;
	setlength();
}
enPlayState mciPlayer::getState() const
{
	return playState;
}
void mciPlayer::Pause()
{
	genericParms.dwCallback = (DWORD)hwnd;
	mciError = mciSendCommand(wDeviceId, MCI_PAUSE, 0, (DWORD_PTR)&genericParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	playState = pause;
}
void mciPlayer::Resume()
{
	Play();
}
void mciPlayer::MoveTo(unsigned toSite)
{
	if (playState == Stoped)
	{
		return;
	}
	//事先获取长度
	//获取状态
	//mci移动
	seekParms.dwCallback = (DWORD)hwnd;
	seekParms.dwTo = toSite*1000;
	mciError = mciSendCommand(wDeviceId, MCI_SEEK, MCI_TO, (DWORD_PTR)&seekParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}

	//验证状态,状态为MCI_MODE_PLAY则播放
	if (playState == playing)
	{
		Play();
	}
}
void mciPlayer::setlength()
{
	if (playState == Stoped)
	{
		ulength = 0;
		return;
	}
	statusParms.dwCallback = (DWORD)hwnd;
	statusParms.dwItem = MCI_STATUS_LENGTH;
	mciError = mciSendCommand(wDeviceId, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	ulength = statusParms.dwReturn;
}
unsigned mciPlayer::getCurrentPos()
{
	statusParms.dwCallback = (DWORD)hwnd;
	statusParms.dwItem = MCI_STATUS_POSITION;
	mciError = mciSendCommand(wDeviceId, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParms);
	if (mciError)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	return statusParms.dwReturn;
}
void mciPlayer::setPlayState(enState state)
{
	this->state = state;
}
enState mciPlayer::getPlayState()const
{
	return state;
}
void mciPlayer::ProcessingNotify(WPARAM wParam, LPARAM lParam)
{
	if (lParam == wDeviceId)
	{
		switch (wParam)
		{
			//播放流产
		case MCI_NOTIFY_ABORTED:
			break;
			//播放失败
		case MCI_NOTIFY_FAILURE:
			break;
			//播放成功
		case MCI_NOTIFY_SUCCESSFUL:
			switch (state)
			{
			case playSingle:
				Pause();
				MoveTo(0);
				Play();
				break;
			case playRound:
			case playRand:
				nextSong();
				break;
			}
			break;
		case MCI_NOTIFY_SUPERSEDED:
			break;
		}
	}
}
void mciPlayer::lastSong()
{
	if (listMusicFile.empty())return;
	if (iterNowFile == listMusicFile.cend())
	{
		return;
	}
	if (iterNowFile == listMusicFile.begin())
	{
		iterNowFile = listMusicFile.end();
	}
	--iterNowFile;
	closeFile();
	openFile();
	Play();
}
void mciPlayer::nextSong()
{
	if (listMusicFile.empty())return;
	if (iterNowFile == listMusicFile.cend())
	{
		return;
	}
	if (state != playRand)
	{
		++iterNowFile;
		if (iterNowFile == listMusicFile.cend())
		{
			iterNowFile = listMusicFile.cbegin();
		}
	}
	else
	{
		int iNow = rand() % listMusicFile.size();
		int i = 0;
		for (auto iter = listMusicFile.begin(); iter != listMusicFile.end(); ++iter,++i)
		{
			if (i == iNow)iterNowFile = iter;
		}
	}
	closeFile();
	openFile();
	Play();
}
void mciPlayer::setVolumn(unsigned volumn)
{
	audioParms.dwCallback = (DWORD)hwnd;
	audioParms.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	audioParms.dwValue = volumn*10;//音量默认范围为0--1000
	mciError = mciSendCommand(wDeviceId, MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE|MCI_DGV_SETAUDIO_ITEM, (DWORD_PTR)&audioParms);
	if (mciError == 257)
	{
		this->volumn = volumn;
	}
	else if (mciError != 0)
	{
		TCHAR szText[100];
		mciGetErrorString(mciError, szText, 100);
		throw runtimeError(szText);
	}
	this->volumn = volumn;
}
bool mciPlayer::addMusic()
{
	bool bResult = true;
	TCHAR szFile[1000];
	szFile[0] = '\0';
	TCHAR szFileTitle[100];
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = lpctstrFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = 1000;
	ofn.lpstrFileTitle = szFileTitle;
	ofn.nMaxFileTitle = 100;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = TEXT("mp3");
	ofn.lCustData = 0;
	ofn.lpTemplateName = NULL;
	ofn.lpfnHook = NULL;
	ofn.dwReserved = 0;
	ofn.pvReserved = 0;
	ofn.FlagsEx = 0;

	if (GetOpenFileName(&ofn))
	{
		wstring strPath(szFile);
		wstring str(szFileTitle);
		int pos = strPath.find_first_of(L"\\");
		while (pos != wstring::npos)
		{
			strPath.replace(pos, 1, L"/");
			pos = strPath.find(L"\\", pos);
		}
		str = str.substr(0, str.size() - 4);
		listMusicFile.emplace_back(strPath, str);
		g_pDataBaseClass->insertData(listMusicFile.back());
		if (listMusicFile.size() == 1)
		{
			iterNowFile = listMusicFile.begin();
		}
	}
	else
	{
		//DWORD Error = CommDlgExtendedError();
		bResult = false;
	}
	return bResult;
}
void mciPlayer::deleteMusic(const wstring str)
{
	if ((*iterNowFile).getStrFileName() == str)
	{
		nextSong();
	}
	list<MusicFile>::const_iterator iter;
	for ( iter = listMusicFile.cbegin(); iter != listMusicFile.cend(); )
	{
		if ((*iter).getStrFileName() == str)
		{
			g_pDataBaseClass->deleteData(*iter);
			iter = listMusicFile.erase(iter);
			break;
		}
		else
			++iter;
	}
	if (listMusicFile.empty())
	{
		closeFile();
		setlength();
	}
}
void mciPlayer::setCurDir()
{
	char strCurDir[MAX_PATH + 1];
	GetModuleFileNameA(NULL, strCurDir, MAX_PATH);
	string::size_type pos = string(strCurDir).find_last_of("\\/");
	string strCurDirectory = string(strCurDir).substr(0, pos);
	if (0 != _chdir(strCurDirectory.c_str()))
	{
		throw runtimeError(L"改变当前文件夹失败!");
	}
}
const MusicFile& mciPlayer::getCurMusicFile() const
{
	return *iterNowFile;
}
list<MusicFile>& mciPlayer::getList()
{
	return listMusicFile;
}
void mciPlayer::SetCurMusicFile(int index)
{
	list<MusicFile>::const_iterator iter = listMusicFile.cbegin();
	for (int i = 0; i < index&&iter != listMusicFile.cend(); ++i)
	{
		++iter;
	}
	iterNowFile = iter;
	closeFile();
	openFile();
	Play();
}
void mciPlayer::ReadLyric()
{

	ifstream ifs(iterNowFile->getStrLyricSite(),std::ios::in);
	wistringstream iss;
	string str;
	wstring wstr;
	wstring wstrtime;
	CommentClass cc;

	while (getline(ifs, str))
	{
		wstr = mtTowc(str);
		iss.str(wstr);
		iss >> wstrtime;
		cc.time = std::stoi(wstrtime);
		iss >> cc.strComment;
		vecLyric.push_back(cc);
		iss.clear();
	}
}
const wstring mciPlayer::getNowLyric()
{

	if (listMusicFile.empty())return L"";
	if (vecLyric.empty())return getCurMusicFile().getStrFileName();
	int CurPos = (getCurrentPos() / 1000);
	if (iterLyricNow->time > CurPos)
	{
		while (iterLyricNow!= vecLyric.begin()&&iterLyricNow->time > CurPos)
		{
				--iterLyricNow;
		}
	}
	else
	{
		while (iterLyricNow != vecLyric.end() && iterLyricNow->time <= CurPos)
		{
			++iterLyricNow;
		}
		if (iterLyricNow != vecLyric.begin())
		{
			--iterLyricNow;
		}
	}
	return iterLyricNow->strComment;
}
void mciPlayer::SetCurMusicFile(list<MusicFile>::iterator iter)
{
	iterNowFile = iter;
	closeFile();
	openFile();
	Play();
}
void mciPlayer::GetComment(wstring comment)
{
	CommentClass cc;
	cc.strComment = comment;
	cc.time = getCurrentPos() / 1000 + 2;
	listComment.push_front(cc);
}
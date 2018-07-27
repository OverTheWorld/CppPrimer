#pragma once
#include"DataBaseClass.h"
#include<windows.h>
#include<Digitalv.h>
#include<commdlg.h>
#include<list>

using std::list;

enum enState { playRound, playSingle ,playRand};
enum enPlayState{pause,playing,Stoped};

class mciPlayer
{
private:
	const string strInitFileName = "Init.ini";

	LPCTSTR lpctstrFilter = TEXT("mp3 File\0*.mp3\0")
		TEXT("All Files\0*.*\0\0");

	OPENFILENAME ofn;

	MCI_OPEN_PARMS openParms;
	MCI_GENERIC_PARMS genericParms;
	MCI_PLAY_PARMS playParms;
	MCI_STATUS_PARMS statusParms;
	MCI_SEEK_PARMS seekParms;
	MCI_DGV_SETAUDIO_PARMS audioParms;
	MCIERROR mciError;

	HWND hwnd;
	MCIDEVICEID wDeviceId;
	list<MusicFile> listMusicFile;
	list<MusicFile>::const_iterator iterNowFile;
	vector<CommentClass> vecLyric;
	vector<CommentClass>::iterator iterLyricNow;
	unsigned ulength;
	unsigned volumn;
	enPlayState playState;
	enState state;

	void readinList();
	void openFile(wstring strDeviceType = L"mpegvideo");
	void closeFile();
	void printoutList();
	void setlength();
	void setCurDir();
	void ReadLyric();

public:
	list<CommentClass> listComment;
	mciPlayer(HWND hwnd);
	~mciPlayer();
	
	void Play();
	void Pause();
	void Resume();
	void lastSong();
	void nextSong();
	void setPlayState(enState state);
	enState getPlayState()const ;
	enPlayState getState() const;
	void MoveTo(unsigned toSite);
	void ProcessingNotify(WPARAM wParam, LPARAM lParam);
	bool addMusic();
	void deleteMusic(const wstring str);
	void setVolumn(unsigned volumn);
	unsigned getVolumn()const { return volumn; }
	unsigned getlength()const{ return ulength; }
	unsigned getCurrentPos();
	const MusicFile& getCurMusicFile() const;
	void SetCurMusicFile(int index);
	list<MusicFile>& getList();
	const vector<CommentClass>& getLyric()const{ return vecLyric; }
	const wstring getNowLyric();
	void SetCurMusicFile(list<MusicFile>::iterator iter);
	void GetComment(wstring comment);
};


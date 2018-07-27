#pragma once
#include<Windows.h>
#include<vector>
#include<string>
#include"UIBaseClass.h"
using std::wstring;
using std::vector;
class ListBox:public UIBaseClass
{
private:
	HBITMAP m_hSrc1Bitmap, m_hSrc2Bitmap;
public:
	using SelProc = void(*)(UIBaseClass* pBase, int index, wstring str);
	using PlayingProc = void(*)(UIBaseClass* pBase, int index, wstring str);
	using SelectMenuProc = void(*)(UIBaseClass* pBase,int index, wstring str, int iId);
protected:
	const int iHeight = 50;
	HFONT m_hFont;
	BLENDFUNCTION m_bf;
	wstring m_strTitle;
	HBRUSH m_hSelBrush;
	vector<wstring> m_vecStr;
	int m_iNowItem;
	int m_iNowOverItem;
	int m_iNowPlaying;
	HMENU m_Menu;
	SelProc m_pSelProc;
	PlayingProc m_pPlayingProc;
	SelectMenuProc m_pSelectMenuProc;
	
	int CalcItemNum(POINT pt);

	void Paint();
	void LeftMouseButtonDown(POINT pt, WPARAM wParam);
	void LeftMouseButtonDoubleClick(POINT pt, WPARAM wParam);
	void RightMouseButtonDown(POINT pt, WPARAM wParam);
	void MouseMove(POINT pt, WPARAM wParam);
	void Menu(int id);
public:

	ListBox(HWND hwndParent, RECT rect, enFrameType enAngleType, POINT pt, const wstring &strTitle, HMENU hMenu, HBITMAP hBitmap);
	~ListBox();
	void SetSelProc(SelProc WindowProc){ m_pSelProc = WindowProc; }
	void SetPlayingProc(PlayingProc WindowProc){ m_pPlayingProc = WindowProc; }
	void SetSelectMenuProc(SelectMenuProc WindowProc){ m_pSelectMenuProc = WindowProc; }
	void SetSelItem(int index){ m_iNowItem = max(0, min(m_vecStr.size() - 1, index)); InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
	void SetPlayingItem(int index){ m_iNowPlaying = max(0, min(m_vecStr.size() - 1, index)); InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
	int GetSelItemIndex()const { return m_iNowItem; }
	int GetPlayingItemIndex()const{ return m_iNowPlaying; }
	void AddItem(const wstring &str){ m_vecStr.push_back(str); InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
	void DeleteItem(int index)
	{
		if (index < 0 || index >= m_vecStr.size())
			return;
		if (index == m_iNowItem)
		{
			m_iNowItem = -1;
		}
		if (index == m_iNowPlaying)
		{
			m_iNowPlaying = -1;
		}
		if (index < m_iNowItem)
		{
			--m_iNowItem;
		}
		if (index < m_iNowPlaying)
		{
			--m_iNowPlaying;
		}
		int i = 0;
		for (auto iter = m_vecStr.begin(); iter != m_vecStr.end();++i)
		{
			if (i == index)
			{
				m_vecStr.erase(iter);
				break;
			}
			else
				++iter;
		}
		InvalidateRect(m_hwnd, NULL, true);
		UpdateWindow(m_hwnd);
	}
	void ClearItem(){ m_vecStr.clear(); InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
};


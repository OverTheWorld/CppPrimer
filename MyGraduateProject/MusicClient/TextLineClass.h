#pragma once
#include"UIBaseClass.h"
class TextLineClass:public UIBaseClass
{
public:
	using InputFunc = void(*)(UIBaseClass* pBaseClass,const wstring &strInputText);
private:
	HBITMAP m_hBitmapSrc1, m_hBitmapSrc2;
protected:
	InputFunc m_InputFunc;
	SIZE m_TextSize;
	BLENDFUNCTION m_bf;
	HFONT m_hFont;
	HBITMAP m_SearchBitmap;
	wstring m_strText;
	bool m_bFocus;
	COLORREF m_TransparentColor;

	void SetTextSize();

	void Paint();
	void ImeChar(wchar_t ch);
	void GetFocus(HWND hwndLostFocus);
	void KillFocus(HWND hwndGetFocus);
	void KeyDown(WPARAM wParam, LPARAM lParam);
public:
	TextLineClass(HWND hwndParent, RECT rect, HBITMAP hParentBackBitmap, bool bHasSearchPic);
	~TextLineClass();
	void SetInputFunc(InputFunc func){ m_InputFunc = func; }
	wstring GetInputStr(){ return m_strText; }
	void SetInputStr(const wstring &strText){ m_strText = strText; }
};


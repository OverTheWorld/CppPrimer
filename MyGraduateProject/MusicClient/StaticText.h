#pragma once
#include"UIBaseClass.h"
class StaticText:public UIBaseClass
{
protected:
	wstring m_strText;
	void Paint();
public:
	StaticText(HWND hwndParent, RECT rect,HBITMAP hParentBackBitmap,const wstring &strText);
	~StaticText();
	void SetText(const wstring &strText){ m_strText = strText; InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
	wstring GetText()const{ return m_strText; }

};


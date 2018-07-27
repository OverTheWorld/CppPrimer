#pragma once
#include"UIBaseClass.h"
class Button:public UIBaseClass
{
private:
	wstring m_strText;
	bool isHover,isTransparent;
	HBITMAP m_InvertBitmap;
	HFONT m_hFont;
	
public:
	using CallBackFunc = void(*)(Button* pThis,POINT pt, WPARAM wParam);
protected:
	CallBackFunc m_pLDFunc,m_pLUFunc,m_pRDFunc,m_pRUFunc;
	void MouseMove(POINT pt, WPARAM wParam);
	void MouseHover(POINT pt, WPARAM wParam);
	void MouseLeave();
	void Paint();
	void LeftMouseButtonDown(POINT pt, WPARAM wParam);
	void RightMouseButtonDown(POINT pt, WPARAM wParam);
	void LeftMouseButtonUp(POINT pt, WPARAM wParam);
	void RightMouseButtonUp(POINT pt, WPARAM wParam);
	void SetInvertBitmap();
public:
	Button(HWND hwndParent, RECT rect, enType enUIType, const wstring &strBackBitmap, enFrameType enAngleType, POINT pt,HBITMAP hBitmap);
	~Button();
	void SetText(const wstring &strText){ m_strText = strText; }
	wstring GetText()const { return m_strText; }
	void SetLeftMouseButtonDownFunc(CallBackFunc pFunc){ m_pLDFunc = pFunc; }
	void SetLeftMouseButtonUpFunc(CallBackFunc pFunc){ m_pLUFunc = pFunc; }
	void SetRightMouseButtonDownFunc(CallBackFunc pFunc){ m_pRDFunc = pFunc; }
	void SetRightMouseButtonUpFunc(CallBackFunc pFunc){ m_pRUFunc = pFunc; }
	HBITMAP SetBackBitmap(HBITMAP hBitmap)
	{
		HBITMAP Bitmap = m_BackBitmap;
		m_BackBitmap = hBitmap;
		SetInvertBitmap();
		InvalidateRect(m_hwnd, NULL, true);
		return Bitmap;
	}
};


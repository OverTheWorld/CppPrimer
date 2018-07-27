#pragma once
#include"UIBaseClass.h"
enum enSliderType{enVertical = 0,enHorizon = 1};
class Slider:public UIBaseClass
{
public:
	using SliderProc = void(*)(int pos);
protected:
	SliderProc m_pFunc;
	HBRUSH m_BackBrush,m_ForeBrush;
	HPEN m_Pen;
	enSliderType m_enType;
	int m_length;
	int m_NowSite;
	int m_stepLength;
	COLORREF m_clrBack, m_clrFore;

	void Paint();
	void LeftMouseButtonDown(POINT pt, WPARAM wParam);
	void KeyDown(WPARAM wParam, LPARAM lParam);
public:
	Slider(HWND hwndParent, RECT rect, COLORREF clrBack, COLORREF clrProcess, int length, enSliderType enType,HBITMAP hBitmap);
	~Slider();
	void SetPos(int pos){ m_NowSite = max(0, min(m_length, pos)); InvalidateRect(m_hwnd, NULL, true); UpdateWindow(m_hwnd); }
	int GetPos()const{ return m_NowSite; }
	void SetLength(int length){ m_length = max(0, length); }
	int GetLength()const{ return m_length; }
	void SetSliderProc(SliderProc pFunc){ m_pFunc = pFunc; }
	void SetStepLength(int step){ m_stepLength = step; }
	int GetStepLength()const{ return m_stepLength; }
};


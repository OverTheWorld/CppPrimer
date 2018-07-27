#include "StaticText.h"


StaticText::StaticText(HWND hwndParent, RECT rect, HBITMAP hParentBackBitmap, const wstring &strText) :
UIBaseClass(hwndParent, rect, enRectangle, L"", enRightAngle, POINT{ 0, 0 }, hParentBackBitmap), m_strText(strText)
{
}
StaticText::~StaticText()
{
}
void StaticText::Paint()
{
	HDC hdc, hdcSrc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(m_hwnd,&ps);
	SetTextColor(hdc, RGB(0X7F, 0X7F, 0X7F));
	SetBkMode(hdc, TRANSPARENT);
	hdcSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcSrc, m_BackBitmap);
	BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, SRCCOPY);
	DrawText(hdc, m_strText.c_str(), m_strText.size(), &m_rect, DT_CENTER | DT_VCENTER);
	DeleteDC(hdcSrc);
	EndPaint(m_hwnd,&ps);
}
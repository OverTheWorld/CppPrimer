#include "Button.h"


Button::Button(HWND hwndParent, RECT rect, enType enUIType, const wstring &strBackBitmap, enFrameType enAngleType, POINT pt,HBITMAP hBitmap):
UIBaseClass(hwndParent,rect,enUIType,strBackBitmap,enAngleType,pt,hBitmap)
{
	SetInvertBitmap();
	if (strBackBitmap.empty())
		isTransparent = true;
	else
		isTransparent = false;
	m_hFont = CreateFont(30, 0, 0, 0, FW_THIN, false, false, false, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, L"Î¢ÈíÑÅºÚ");
}


Button::~Button()
{
	DeleteObject(m_InvertBitmap);
	DeleteObject(m_hFont);
}

void Button::MouseMove(POINT pt, WPARAM wParam)
{
	MouseHover(pt, wParam);
}
void Button::MouseHover(POINT pt, WPARAM wParam)
{
	if (!isHover)
	{
		isHover = true;
		InvalidateRect(m_hwnd, NULL, true);
		UpdateWindow(m_hwnd);
	}
}
void Button::MouseLeave()
{
	if (isHover)
	{
		isHover = false;
		InvalidateRect(m_hwnd, NULL, true);
		UpdateWindow(m_hwnd);
	}
}
void Button::Paint()
{
	HDC hdc,hdcSrc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(m_hwnd, &ps);
	SetBkMode(hdc, TRANSPARENT);
	SelectObject(hdc, m_hFont);
	if (isHover)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, RGB(0X7F, 0X7F, 0X7F));
	hdcSrc = CreateCompatibleDC(hdc);
	if (!isTransparent)
	{
		if (!isHover)
			SelectObject(hdcSrc, m_BackBitmap);
		else
			SelectObject(hdcSrc, m_InvertBitmap);
	}
	else
	{
		SelectObject(hdcSrc, m_BackBitmap);
	}
	BitBlt(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, SRCCOPY);
	DrawText(hdc, m_strText.c_str(), m_strText.size(), &m_rect, DT_CENTER | DT_VCENTER);
	DeleteDC(hdcSrc);
	EndPaint(m_hwnd, &ps);
}
void Button::LeftMouseButtonDown(POINT pt, WPARAM wParam)
{
	if (m_pLDFunc)
	{
		m_pLDFunc(this,pt, wParam);
	}
}
void Button::LeftMouseButtonUp(POINT pt, WPARAM wParam)
{
	if (m_pLUFunc)
	{
		m_pLUFunc(this,pt, wParam);
	}
}
void Button::RightMouseButtonDown(POINT pt, WPARAM wParam)
{
	if (m_pRDFunc)
	{
		m_pRDFunc(this,pt, wParam);
	}
}
void Button::RightMouseButtonUp(POINT pt, WPARAM wParam)
{
	if (m_pRUFunc)
	{
		m_pRUFunc(this,pt, wParam);
	}
}
void Button::SetInvertBitmap()
{
	HDC hdc = GetDC(m_hwnd);
	HDC hdcSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcSrc, m_BackBitmap);
	m_InvertBitmap = CreateCompatibleBitmap(hdcSrc, m_rect.right, m_rect.bottom);
	HDC hdcDst = CreateCompatibleDC(hdcSrc);
	SelectObject(hdcDst, m_InvertBitmap);
	BitBlt(hdcSrc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, DSTINVERT);
	BitBlt(hdcDst, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, SRCCOPY);
	BitBlt(hdcSrc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, DSTINVERT);
	DeleteDC(hdcDst);
	DeleteDC(hdcSrc);
	ReleaseDC(m_hwnd, hdc);
}

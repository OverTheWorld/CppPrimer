#include "TextLineClass.h"


TextLineClass::TextLineClass(HWND hwndParent, RECT rect, HBITMAP hParentBackBitmap, bool bHasSearchPic) :
UIBaseClass(hwndParent, rect, enRectangle, L"", enObtuseAngle, POINT{ 20, 20 }, hParentBackBitmap), m_bFocus(false), m_InputFunc(NULL)
{
	if (!bHasSearchPic)
	{
		m_SearchBitmap = NULL;
	}
	else
		m_SearchBitmap = (HBITMAP)LoadImage(NULL, L"SearchPic.bmp", 0, 50, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC hdc = GetDC(m_hwnd);
	m_hBitmapSrc1 = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);
	m_hBitmapSrc2 = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);
	ReleaseDC(m_hwnd, hdc);
	m_hFont = CreateFont(30, 0, 0, 0, FW_THIN, false, false, false, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, L"Î¢ÈíÑÅºÚ");
	m_bf.AlphaFormat = 0;
	m_bf.BlendFlags = 0;
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.SourceConstantAlpha = 128;
}
TextLineClass::~TextLineClass()
{
	if (m_SearchBitmap)
		DeleteObject(m_SearchBitmap);
	DeleteObject(m_hBitmapSrc1);
	DeleteObject(m_hBitmapSrc2);
	DeleteObject(m_hFont);
}

void TextLineClass::Paint()
{
	int distance = 0;
	HDC hdc, hdcSrc1,hdcSrc2;
	PAINTSTRUCT ps;
	hdc = BeginPaint(m_hwnd, &ps);
	hdcSrc1 = CreateCompatibleDC(hdc);
	hdcSrc2 = CreateCompatibleDC(hdc);
	SelectObject(hdcSrc1, m_hBitmapSrc1);
	SelectObject(hdcSrc1, m_hFont);
	SelectObject(hdcSrc2, m_BackBitmap);
	SetBkMode(hdcSrc1, TRANSPARENT);
	SetTextColor(hdcSrc1, RGB(0XFF, 0XAD, 0X06));
	BitBlt(hdcSrc1, 0, 0, m_rect.right, m_rect.bottom, hdcSrc2, 0, 0, SRCCOPY);
	if (!m_bFocus)
	{
		if (m_SearchBitmap)
		{
			SelectObject(hdcSrc2, m_SearchBitmap);
			TransparentBlt(hdcSrc1, 10, 10, 30, 30, hdcSrc2, 0, 0, 50, 50, RGB(0XD9, 0X6F, 0X0C));
			distance = 50;
		}
		TextOut(hdcSrc1, distance, 10, m_strText.c_str(), m_strText.size());
	}
	SelectObject(hdcSrc2, m_hBitmapSrc2);
	SelectObject(hdcSrc2, GetStockObject(WHITE_BRUSH));
	Rectangle(hdcSrc2, 0, 0, m_rect.right, m_rect.bottom);
	AlphaBlend(hdcSrc1, 0, 0, m_rect.right, m_rect.bottom, hdcSrc2, 0, 0, m_rect.right, m_rect.bottom, m_bf);
	DeleteDC(hdcSrc2);
	if (m_bFocus)
	{
		TextOut(hdcSrc1, 0, 10, m_strText.c_str(), m_strText.size());
	}
	BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, hdcSrc1, 0, 0, SRCCOPY);
	DeleteDC(hdcSrc1);
	EndPaint(m_hwnd, &ps);
}
void TextLineClass::ImeChar(wchar_t ch)
{
	m_strText = m_strText + ch;
	SetTextSize();
	HideCaret(m_hwnd);
	SetCaretPos(m_TextSize.cx, 10);
	ShowCaret(m_hwnd);
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
}
void TextLineClass::GetFocus(HWND hwndLostFocus)
{
	m_bFocus = true;
	CreateCaret(m_hwnd, NULL, 2, 30);
	SetCaretPos(m_TextSize.cx, 10);
	ShowCaret(m_hwnd);
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
}
void TextLineClass::KillFocus(HWND hwndGetFocus)
{
	m_bFocus = false;
	HideCaret(m_hwnd);
	DestroyCaret();
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
}
void TextLineClass::KeyDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_BACK)
	{
		if (m_strText.size() == 0)
			return;
		m_strText = m_strText.substr(0, m_strText.size() - 1);
		SetTextSize();
		HideCaret(m_hwnd);
		SetCaretPos(m_TextSize.cx, 10);
		ShowCaret(m_hwnd);
		InvalidateRect(m_hwnd, NULL, true);
		UpdateWindow(m_hwnd);
	}
	else if (wParam == VK_RETURN)
	{
		if (m_strText.empty())
			return;
		if (m_InputFunc != NULL)
		{
			m_InputFunc(this, m_strText);
		}
	}
}
void TextLineClass::SetTextSize()
{
	HDC hdc = GetDC(m_hwnd);
	SelectObject(hdc, m_hFont);
	GetTextExtentPoint(hdc, m_strText.c_str(), m_strText.size(), &m_TextSize);
	ReleaseDC(m_hwnd, hdc);
}
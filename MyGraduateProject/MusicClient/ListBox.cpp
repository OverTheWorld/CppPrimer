#include "ListBox.h"


ListBox::ListBox(HWND hwndParent, RECT rect, enFrameType enAngleType, POINT pt, const wstring &strTitle, HMENU hMenu, HBITMAP hBitmap) :
UIBaseClass(hwndParent, rect, enRectangle, L"", enAngleType, pt,hBitmap), m_strTitle(strTitle), m_iNowItem(-1), m_iNowPlaying(-1), m_Menu(hMenu), m_iNowOverItem(-1)
{
	m_hSelBrush = CreateSolidBrush(RGB(0XFF, 0XAD, 0X06));
	HDC hdc = GetDC(m_hwnd);
	m_hSrc1Bitmap = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);
	m_hSrc2Bitmap = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom);
	ReleaseDC(m_hwnd, hdc);
	m_hFont = CreateFont(30, 0, 0, 0, FW_THIN, false, false, false,CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,FF_MODERN, L"Î¢ÈíÑÅºÚ");
	m_bf.AlphaFormat = 0;
	m_bf.BlendFlags = 0;
	m_bf.BlendOp = AC_SRC_OVER;
	m_bf.SourceConstantAlpha = 128;
}
ListBox::~ListBox()
{
	DeleteObject(m_hSelBrush);
	DeleteObject(m_hFont);
	DeleteObject(m_hSrc1Bitmap);
	DeleteObject(m_hSrc2Bitmap);
}

void ListBox::Paint()
{
	PAINTSTRUCT ps;
	SIZE size;
	HDC hdc,hdcSrc1,hdcSrc2;
	hdc = BeginPaint(m_hwnd, &ps);
	hdcSrc2 = CreateCompatibleDC(hdc);
	hdcSrc1 = CreateCompatibleDC(hdc);
	SelectObject(hdcSrc1,m_BackBitmap);
	SelectObject(hdcSrc2, m_hSrc2Bitmap);
	BitBlt(hdcSrc2, 0, 0, m_rect.right, m_rect.bottom, hdcSrc1, 0, 0, SRCCOPY);
	SelectObject(hdcSrc1, GetStockObject(BLACK_BRUSH));
	SelectObject(hdcSrc1, m_hSrc1Bitmap);
	Rectangle(hdcSrc1, 0, 0, m_rect.right, m_rect.bottom);
	AlphaBlend(hdcSrc2, 0, 0, m_rect.right, m_rect.bottom, hdcSrc1, 0, 0, m_rect.right, m_rect.bottom, m_bf);
	SetTextColor(hdcSrc2, RGB(0X7F, 0X7F, 0X7F));
	SetBkMode(hdcSrc2, TRANSPARENT);
	SelectObject(hdcSrc2, m_hFont);
	GetTextExtentPoint(hdcSrc2, m_strTitle.c_str(), m_strTitle.size(), &size);
	TextOut(hdcSrc2, (m_rect.right - size.cx)/2, (iHeight - size.cy)/2, m_strTitle.c_str(), m_strTitle.size());
	MoveToEx(hdcSrc2, 0, iHeight, NULL);
	LineTo(hdcSrc2, m_rect.right, iHeight);
	int i = 0;
	for (const auto &s : m_vecStr)
	{
		if (i == m_iNowItem )
		{
			SelectObject(hdcSrc2, GetStockObject(BLACK_BRUSH));
			Rectangle(hdcSrc2, 0, (i+1) * iHeight, m_rect.right, (i+2)*iHeight);
		}
		if (i == m_iNowPlaying)
		{
			SelectObject(hdcSrc2, m_hSelBrush);
			Rectangle(hdcSrc2, 0, (i+1)*iHeight + 10, 5, (i+1)*iHeight + 40);
		}
		if (i == m_iNowOverItem)
		{
			SetTextColor(hdcSrc2, RGB(255, 255, 255));
		}
		TextOut(hdcSrc2, 50, i * iHeight + 60, s.c_str(), s.size());
		MoveToEx(hdcSrc2, 0, (i + 1) * iHeight, NULL);
		LineTo(hdcSrc2, m_rect.right, (i + 1) * iHeight);
		if (i == m_iNowOverItem)
		{
			SetTextColor(hdcSrc2, RGB(0X7F, 0X7F, 0X7F));
		}
		++i;
	}
	DeleteDC(hdcSrc1);
	BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, hdcSrc2, 0, 0, SRCCOPY);
	DeleteDC(hdcSrc2);
	EndPaint(m_hwnd, &ps);
}
void ListBox::LeftMouseButtonDoubleClick(POINT pt, WPARAM wParam)
{
	LeftMouseButtonDown(pt, wParam);
	if (m_iNowItem == -1)return;
	m_iNowPlaying = m_iNowItem;
	InvalidateRect(m_hwnd, NULL,true);
	UpdateWindow(m_hwnd);
	if (m_pPlayingProc)
	{
		m_pPlayingProc(this,m_iNowPlaying, m_vecStr.at(m_iNowPlaying));
	}
}
void ListBox::LeftMouseButtonDown(POINT pt, WPARAM wParam)
{
	m_iNowItem = CalcItemNum(pt);
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
	if (m_pSelProc)
	{
		m_pSelProc(this, m_iNowItem, m_vecStr.at(m_iNowItem));
	}
}
void ListBox::RightMouseButtonDown(POINT pt, WPARAM wParam)
{
	LeftMouseButtonDown(pt, wParam);
	if (m_Menu == NULL)return;
	if (m_iNowItem == -1)
	{
		EnableMenuItem(m_Menu, 1, MF_GRAYED);
		EnableMenuItem(m_Menu, 2, MF_GRAYED);
	}
	else
	{
		EnableMenuItem(m_Menu, 1, MF_ENABLED);
		EnableMenuItem(m_Menu, 2, MF_ENABLED);
	}
	ClientToScreen(m_hwnd, &pt);
	TrackPopupMenu(m_Menu, 0, pt.x, pt.y, 0, m_hwnd, NULL);
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
}
void ListBox::Menu(int id)
{
	if (m_pSelectMenuProc)
	{
		if (m_iNowItem == -1)
			m_pSelectMenuProc(this, m_iNowItem, L"", id);
		else
			m_pSelectMenuProc(this,m_iNowItem, m_vecStr.at(m_iNowItem), id);
	}
}
void ListBox::MouseMove(POINT pt, WPARAM wParam)
{
	m_iNowOverItem = CalcItemNum(pt);
	InvalidateRect(m_hwnd, NULL, true);
	UpdateWindow(m_hwnd);
}
int ListBox::CalcItemNum(POINT pt)
{
	int index = pt.y / iHeight - 1;
	int Site = pt.y % iHeight;
	if (Site >= 10 && Site <= 40)
	{
		if (index < m_vecStr.size())
		{
			return index;
		}
	}
	return -1;
}

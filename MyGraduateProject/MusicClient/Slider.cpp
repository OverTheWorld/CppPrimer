#include "Slider.h"


Slider::Slider(HWND hwndParent, RECT rect, COLORREF clrBack, COLORREF clrFore, int length, enSliderType enType, HBITMAP hBitmap) :
UIBaseClass(hwndParent, rect, enRectangle, L"", enObtuseAngle, enType == enVertical ? POINT{ rect.right, rect.right } : POINT{ rect.bottom, rect.bottom },hBitmap),
m_clrBack(clrBack), m_clrFore(clrFore), m_length(length), m_NowSite(0), m_enType(enType), m_pFunc(NULL), m_stepLength(1)
{
	m_BackBrush = CreateSolidBrush(m_clrBack);
	m_ForeBrush = CreateSolidBrush(m_clrFore);
	m_Pen = CreatePen(PS_SOLID, 1, m_clrBack);
}
Slider::~Slider()
{
	if (m_BackBrush)
		DeleteObject(m_BackBrush);
	if (m_ForeBrush)
		DeleteObject(m_ForeBrush);
	if (m_Pen)
		DeleteObject(m_Pen);
}
void Slider::Paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hwnd, &ps);
	SelectObject(hdc, m_BackBrush);
	SelectObject(hdc, m_Pen);
	Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	SelectObject(hdc, m_ForeBrush);
	int Pos;
	switch (m_enType)
	{
	case enVertical:
		if (m_length != 0)
			Pos = m_rect.bottom - m_NowSite*m_rect.bottom / m_length;
		else
			Pos = 0;
		RoundRect(hdc, m_rect.left, Pos, m_rect.right, m_rect.bottom , m_ptRound.x, m_ptRound.y);
		break;
	case enHorizon:
		if (m_length != 0)
			Pos = m_NowSite*m_rect.right / m_length;
		else
			Pos = 0;
		RoundRect(hdc, m_rect.left, m_rect.top, Pos, m_rect.bottom, m_ptRound.x, m_ptRound.y);
		break;
	}
	EndPaint(m_hwnd, &ps);
}
void Slider::LeftMouseButtonDown(POINT pt,WPARAM wParam)
{
	int pos = m_enType == enVertical ? (m_length - pt.y*m_length / m_rect.bottom) : pt.x*m_length / m_rect.right;
	SetPos(pos);
	if (m_pFunc)
		m_pFunc(GetPos());
}
void Slider::KeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (m_enType)
	{
	case enVertical:
		switch (wParam)
		{
		case VK_UP:
			SetPos(GetPos() + m_stepLength);
			break;
		case VK_DOWN:
			SetPos(GetPos() - m_stepLength);
			break;
		}
		break;
	case enHorizon:
		break;
	}
	if (m_pFunc)
	{
		m_pFunc(GetPos());
	}
}
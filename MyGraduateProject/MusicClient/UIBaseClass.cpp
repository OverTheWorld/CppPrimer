#include "UIBaseClass.h"


UIBaseClass::UIBaseClass(HWND hwndParent, RECT rect, enType enUIType, const wstring &strBackBitmap, enFrameType enAngleType, POINT pt, HBITMAP hParentBackBitmap)
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwndParent, GWLP_HINSTANCE);
	m_hwnd = CreateWindowEx(0, m_strClassName.c_str(), NULL, WS_CHILD|WS_TABSTOP, rect.left,rect.top, rect.right, rect.bottom, hwndParent, NULL, hInstance,(LPVOID)this);
	RECT rectWindow = rect;
	GetClientRect(m_hwnd, &rect);
	if (strBackBitmap.empty())
	{
		HDC hdc = GetDC(m_hwnd);
		HDC hdcSrc1, hdcSrc2;
		hdcSrc1 = CreateCompatibleDC(hdc);
		hdcSrc2 = CreateCompatibleDC(hdc);
		m_BackBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		SelectObject(hdcSrc1, hParentBackBitmap);
		SelectObject(hdcSrc2, m_BackBitmap);
		StretchBlt(hdcSrc2, 0, 0, rect.right, rect.bottom, hdcSrc1, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom,SRCCOPY);
		DeleteDC(hdcSrc1);
		DeleteDC(hdcSrc2);
		ReleaseDC(m_hwnd, hdc);
	}
	else
		m_BackBitmap = (HBITMAP)LoadImage(NULL, strBackBitmap.c_str(), 0, rect.right, rect.bottom, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	m_rect = rect;
	m_ptRound.x = 0;
	m_ptRound.y = 0;
	switch (enUIType)
	{
	case enRound:
		m_hRgn = CreateEllipticRgnIndirect(&rect);
		break;
	case enRectangle:
		switch (enAngleType)
		{
		case enObtuseAngle:
			m_ptRound = pt;
			m_hRgn = CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, pt.x, pt.y);
			break;
		case enRightAngle:
			m_hRgn = CreateRectRgnIndirect(&rect);
			break;
		}
		break;
	}
	SetWindowRgn(m_hwnd, m_hRgn, true);
	ShowWindow(m_hwnd, SW_NORMAL);
}
UIBaseClass::~UIBaseClass()
{
	if (m_BackBitmap)
		DeleteObject(m_BackBitmap);
	DeleteObject(m_hRgn);
	Destroy();
}
void UIBaseClass::Create(LPCREATESTRUCT pCreate)
{

}
void UIBaseClass::Paint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hwnd, &ps);
	if (m_BackBitmap)
	{
		HDC hdcSrc = CreateCompatibleDC(hdc);
		SelectObject(hdcSrc, m_BackBitmap);
		BitBlt(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, hdcSrc, 0, 0, SRCCOPY);
		DeleteDC(hdcSrc);
	}
	EndPaint(m_hwnd, &ps);
}
void UIBaseClass::Close()
{
	
}
void UIBaseClass::Destroy()
{
	
}
void UIBaseClass::LeftMouseButtonDown(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::RightMouseButtonDown(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::LeftMouseButtonUp(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::RightMouseButtonUp(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::LeftMouseButtonDoubleClick(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::MouseHover(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::MouseMove(POINT pt, WPARAM wParam)
{

}
void UIBaseClass::MouseLeave()
{

}
void UIBaseClass::KeyDown(WPARAM wParam, LPARAM lParam)
{

}
void UIBaseClass::Menu(int id)
{

}
void UIBaseClass::ImeChar(wchar_t ch)
{

}
void UIBaseClass::KillFocus(HWND hwndGetFocus)
{

}
void UIBaseClass::GetFocus(HWND hwndLostFocus)
{

}
void Init(HINSTANCE hInstance)
{
	WNDCLASSEX m_wndClass;
	m_wndClass.cbSize = sizeof(WNDCLASSEX);
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.style = CS_DBLCLKS;
	m_wndClass.hbrBackground = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	m_wndClass.hInstance = hInstance;
	m_wndClass.lpfnWndProc = UIBaseClass::m_WindowProc;
	m_wndClass.lpszClassName = m_strClassName.c_str();
	m_wndClass.lpszMenuName = NULL;
	if (!RegisterClassEx(&m_wndClass))
	{
		MessageBox(0, L"Fail to RegisterClass!", 0, 0);
		return;
	}
}
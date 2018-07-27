#pragma once
#include<Windows.h>
#include<string>
using std::wstring;
enum enType{ enRound = 0, enRectangle = 1 };
enum enFrameType{enObtuseAngle = 0,enRightAngle = 1};
const wstring m_strClassName = L"UIClass";
class UIBaseClass
{
	friend void Init(HINSTANCE);
private:
	static LRESULT CALLBACK m_WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		static TRACKMOUSEEVENT tme;
		UIBaseClass *pBase;
		POINT pt;
		switch (message)
		{
		case WM_CREATE:
			pBase = (UIBaseClass*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pBase);
			tme.cbSize = sizeof(tme);
			tme.dwHoverTime = 100;
			pBase->Create((LPCREATESTRUCT)lParam);
			break;
		case WM_PAINT:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->Paint();
			break;
		case WM_MOUSEMOVE:
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_LEAVE;
			TrackMouseEvent(&tme);
			tme.dwFlags = TME_HOVER;
			TrackMouseEvent(&tme);
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->MouseMove(pt, wParam);
			break;
		case WM_MOUSEHOVER:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->MouseHover(pt, wParam);
			break;
		case WM_MOUSELEAVE:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->MouseLeave();
			break;
		case WM_LBUTTONDOWN:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			SetFocus(hwnd);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->LeftMouseButtonDown(pt, wParam);
			break;
		case WM_LBUTTONUP:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->LeftMouseButtonUp(pt, wParam);
			break;
		case WM_RBUTTONDOWN:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->RightMouseButtonDown(pt, wParam);
			break;
		case WM_RBUTTONUP:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->RightMouseButtonUp(pt, wParam);
			break;
		case WM_LBUTTONDBLCLK:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->LeftMouseButtonDoubleClick(pt, wParam);
			break;
		case WM_COMMAND:
			if (lParam)//child Control
			{

			}
			else//Menu
			{
				pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
				pBase->Menu(LOWORD(wParam));
			}
			break;
		case WM_SETFOCUS:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->GetFocus((HWND)wParam);
			break;
		case WM_KILLFOCUS:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->KillFocus((HWND)wParam);
			break;
		case WM_KEYDOWN:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->KeyDown(wParam,lParam);
			break;
		case WM_IME_CHAR:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->ImeChar(wParam);
			break;
		case WM_CLOSE:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pBase->Close();
			break;
		case WM_DESTROY:
			pBase = (UIBaseClass*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			delete pBase;
			break;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
protected:
	HBITMAP m_BackBitmap;
	HWND m_hwnd;
	HRGN m_hRgn;
	RECT m_rect;
	POINT m_ptRound;
	virtual void Create(LPCREATESTRUCT pCreate);
	virtual void Paint();
	virtual void Close();
	virtual void Destroy();
	virtual void LeftMouseButtonDown(POINT pt, WPARAM wParam);
	virtual void LeftMouseButtonDoubleClick(POINT pt, WPARAM wParam);
	virtual void RightMouseButtonDown(POINT pt, WPARAM wParam);
	virtual void LeftMouseButtonUp(POINT pt, WPARAM wParam);
	virtual void RightMouseButtonUp(POINT pt, WPARAM wParam);
	virtual void MouseHover(POINT pt, WPARAM wParam);
	virtual void MouseMove(POINT pt, WPARAM wParam);
	virtual void MouseLeave();
	virtual void KeyDown(WPARAM wParam, LPARAM lParam);
	virtual void Menu(int id);
	virtual void ImeChar(wchar_t ch);
	virtual void GetFocus(HWND hwndLostFocus);
	virtual void KillFocus(HWND hwndGetFocus);
public:
	UIBaseClass(HWND hwndParent, RECT rect, enType enUIType, const wstring &strBackBitmap,enFrameType enAngleType,POINT pt,HBITMAP hParentBackBitmap);
	virtual~UIBaseClass();
	HBITMAP GetBackBitmap()const{ return m_BackBitmap; }
	virtual HBITMAP SetBackBitmap(HBITMAP backBitmap){ HBITMAP hBitmap = m_BackBitmap; m_BackBitmap = backBitmap; return hBitmap; }
	HWND GetHwnd()const{ return m_hwnd; }
	void SetShow(bool bShow)
	{
		if (bShow)
		{
			ShowWindow(m_hwnd, SW_NORMAL);
		}
		else
		{
			ShowWindow(m_hwnd, SW_HIDE);
		}
	}
};
void Init(HINSTANCE hInstance);
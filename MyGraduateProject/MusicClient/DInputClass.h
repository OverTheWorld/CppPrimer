#pragma once
#include<d3d9.h>
#include<dinput.h>
#include<string>

using std::wstring;
using std::to_string;

class DInputClass
{
private:
	LPDIRECTINPUTDEVICE8 m_pdiMouseDevice, m_pdiKeyboardDevice;
	DIMOUSESTATE m_diMouseState;
	char m_szKeyboard[256];

public:
	DInputClass(HWND hwnd);
	virtual ~DInputClass();

	bool MouseAcquire();
	bool KeyboardAcquire();
	bool isKeyDown(short i)const ;
	bool isMouseDown(short i)const ;
	void getMouseMove(long &x, long &y, long &z)const ;
};
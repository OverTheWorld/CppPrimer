#include "DInputClass.h"
#include"runtimeError.h"

DInputClass::DInputClass(HWND hwnd)
{
	LPDIRECTINPUT8 pdi;
	HINSTANCE hinst = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd, GWLP_HINSTANCE));
	if (FAILED(DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<LPVOID*>(&pdi), NULL)))
	{
		throw runtimeError(L"到处是问题！");
		//post an error
	}
	if (FAILED(pdi->CreateDevice(GUID_SysMouse, &m_pdiMouseDevice, NULL)))
	{
		//post an error
	}
	if (FAILED(pdi->CreateDevice(GUID_SysKeyboard, &m_pdiKeyboardDevice, NULL)))
	{
		//post an error
	}
	if (FAILED(pdi->Release()))
	{
		//post an error
	}
	if (FAILED(m_pdiMouseDevice->SetDataFormat(&c_dfDIMouse)))
	{
		//post an error
	}
	if (FAILED(m_pdiMouseDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		//post an error
	}
	if (FAILED(m_pdiKeyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		//post an error
	}
	if (FAILED(m_pdiKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
	{
		//post an error
	}
}
DInputClass::~DInputClass()
{
	m_pdiKeyboardDevice->Release();
	m_pdiMouseDevice->Release();
}

bool DInputClass::MouseAcquire()
{
	HRESULT hr;
	m_pdiMouseDevice->Acquire();
	m_pdiMouseDevice->Poll();
	m_pdiMouseDevice->Acquire();
	while (true)
	{
		if (SUCCEEDED(hr = m_pdiMouseDevice->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState)))
		{
			break;
		}
		if (hr != DIERR_ACQUIRED && hr != DIERR_INPUTLOST)
		{
			return false;
		}
		if (FAILED(m_pdiMouseDevice->Acquire()))
		{
			return false;
		}
	}
	return true;
}
bool DInputClass::KeyboardAcquire()
{
	HRESULT hr;
	m_pdiKeyboardDevice->Acquire();
	m_pdiKeyboardDevice->Poll();
	m_pdiKeyboardDevice->Acquire();
	while (true)
	{
		if (SUCCEEDED(hr = m_pdiKeyboardDevice->GetDeviceState(sizeof(m_szKeyboard), m_szKeyboard)))
		{
			break;
		}
		if (hr != DIERR_ACQUIRED && hr != DIERR_INPUTLOST)
		{
			return false;
		}
		if (FAILED(m_pdiKeyboardDevice->Acquire()))
		{
			return false;
		}
	}
	return true;
}
bool DInputClass::isKeyDown(short i)const
{
	return (m_szKeyboard[i] & 0x80) == 0x80 ? true : false;
}
bool DInputClass::isMouseDown(short i)const
{
	return (m_diMouseState.rgbButtons[i] & 0x80) == 0x80 ? true : false;
}
void DInputClass::getMouseMove(long &x, long &y, long &z)const
{
	x = m_diMouseState.lX;
	y = m_diMouseState.lY;
	z = m_diMouseState.lZ;
}

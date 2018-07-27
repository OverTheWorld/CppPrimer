#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class DCameraClass
{
private:
	D3DXVECTOR3 m_vecPos, m_vecLook, m_vecRight, m_vecUp;
	D3DXMATRIX m_viewMatrix;
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	void SetViewMatrix();
public:
	DCameraClass(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 pos, float fView);
	~DCameraClass();

	void rotationX(float fAngle);
	void rotationY(float fAngle);
	void rotationWorldY(float fAngle);
	void rotationZ(float fAngle);
	void SetMoveX(float funit);
	void SetMoveY(float funit);
	void SetMoveZ(float funit);
	bool SetViewTransform();
};




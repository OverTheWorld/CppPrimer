#include "DCameraClass.h"


DCameraClass::DCameraClass(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos = D3DXVECTOR3(0,0,-250),float fView = 1000.0f) :m_pd3dDevice(pDevice), m_vecPos(pos), m_vecLook(D3DXVECTOR3(0, 0, 1)), m_vecRight(1, 0, 0), m_vecUp(0,1,0)
{
	D3DXMATRIX mat;
	if (!SetViewTransform())
	{
		//post an error
	}
	D3DXMatrixPerspectiveFovLH(&mat, D3DX_PI / 4.0f, 1.0f, 1.0f, fView);
	if (FAILED(m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat)))
	{
		//post an error
	}

}
DCameraClass::~DCameraClass()
{
}


void DCameraClass::SetViewMatrix()
{
	D3DXVec3Normalize(&m_vecLook, &m_vecLook);
	D3DXVec3Cross(&m_vecUp, &m_vecLook, &m_vecRight);
	D3DXVec3Normalize(&m_vecUp, &m_vecUp);
	D3DXVec3Cross(&m_vecRight, &m_vecUp, &m_vecLook);
	D3DXVec3Normalize(&m_vecRight,&m_vecRight);

	m_viewMatrix._11 = m_vecRight.x;
	m_viewMatrix._12 = m_vecUp.x;
	m_viewMatrix._13 = m_vecLook.x;
	m_viewMatrix._14 = 0;

	m_viewMatrix._21 = m_vecRight.y;
	m_viewMatrix._22 = m_vecUp.y;
	m_viewMatrix._23 = m_vecLook.y;
	m_viewMatrix._24 = 0;

	m_viewMatrix._31 = m_vecRight.z;
	m_viewMatrix._32 = m_vecUp.z;
	m_viewMatrix._33 = m_vecLook.z;
	m_viewMatrix._34 = 0;

	m_viewMatrix._41 = -D3DXVec3Dot(&m_vecPos, &m_vecRight);
	m_viewMatrix._42 = -D3DXVec3Dot(&m_vecPos, &m_vecUp);
	m_viewMatrix._43 = -D3DXVec3Dot(&m_vecPos, &m_vecLook);
	m_viewMatrix._44 = 1.0f;
}
void DCameraClass::rotationX(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecRight, fAngle);
	D3DXVec3TransformCoord(&m_vecLook, &m_vecLook, &mat);
	D3DXVec3TransformCoord(&m_vecUp, &m_vecUp, &mat);
}
void DCameraClass::rotationY(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecUp, fAngle);
	D3DXVec3TransformCoord(&m_vecLook, &m_vecLook, &mat);
	D3DXVec3TransformCoord(&m_vecRight, &m_vecRight, &mat);
}
void DCameraClass::rotationWorldY(float fAngle)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 vecUp(0, 1, 0);
	D3DXMatrixRotationAxis(&mat, &vecUp, fAngle);
	D3DXVec3TransformCoord(&m_vecLook, &m_vecLook, &mat);
	D3DXVec3TransformCoord(&m_vecRight, &m_vecRight, &mat);
}
void DCameraClass::rotationZ(float fAngle)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationAxis(&mat, &m_vecLook, fAngle);
	D3DXVec3TransformCoord(&m_vecUp, &m_vecUp, &mat);
	D3DXVec3TransformCoord(&m_vecRight, &m_vecRight, &mat);
}
void DCameraClass::SetMoveX(float funit)
{
	m_vecPos += m_vecRight * funit;
}
void DCameraClass::SetMoveY(float funit)
{
	m_vecPos += m_vecUp * funit;
}
void DCameraClass::SetMoveZ(float funit)
{
	m_vecPos += m_vecLook*funit;
}
bool DCameraClass::SetViewTransform()
{
	SetViewMatrix();
	if (FAILED(m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_viewMatrix)))
	{
		return false;
	}
	return true;
}
#pragma once
#include<d3d9.h>
#include<d3dx9.h>

class DSkyClass
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pd3dVertexBuffer[5];
	LPDIRECT3DTEXTURE9 m_pd3dTexture[5];
	int m_length;
	
	struct CustomVertex
	{
		float x, y, z, u, v;
		CustomVertex(float x, float y, float z, float u, float v) :x(x), y(y), z(z), u(u), v(v)
		{}
		static const DWORD D3DFVF_CUSTOM = D3DFVF_XYZ | D3DFVF_TEX1;
	};

public:
	DSkyClass(
		LPDIRECT3DDEVICE9 pDevice,
		wchar_t *strLeftFile,
		wchar_t *strRightFile,
		wchar_t *strUpFile,
		wchar_t *strForwordFile,
		wchar_t *strBackFile,
		int lenth
		);
	~DSkyClass();

	void DrawSkyBox(D3DXMATRIX *pMatWorld);
};


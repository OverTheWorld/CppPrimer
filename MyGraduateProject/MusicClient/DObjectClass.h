#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<string>

using std::wstring;
using std::string;
using std::to_string;

class DObjectClass
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DTEXTURE9 *m_ppd3dTexture;
	D3DMATERIAL9 *m_pd3dMaterial;
	DWORD m_numMatrl;
	LPD3DXMESH m_pd3dMesh;
	
public:
	DObjectClass(LPCTSTR szFile, LPDIRECT3DDEVICE9 pDevice);
	~DObjectClass();

	bool DrawObject() const;
};


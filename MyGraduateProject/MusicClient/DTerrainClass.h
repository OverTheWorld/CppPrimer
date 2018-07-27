#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<vector>
#include<fstream>

using std::vector;
using std::ifstream;

class DTerrainClass
{
private:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DTEXTURE9 m_pd3dTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pd3dVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pd3dIndexBuffer;

	vector<float> m_vecHeightMap;
	float m_fScale, m_fSpace;
	int m_widthSpaceNum, m_heightSpaceNum;
	int m_widthVerticesNum, m_heightVerticesNum;
	float m_width, m_height;
	int m_AllSpaceNum, m_AllVerticesNum;

	struct CustomVertex
	{
		float x, y, z, u, v;
		CustomVertex(float x, float y, float z, float u, float v) :x(x), y(y), z(z), u(u), v(v)
		{}
		static const DWORD D3DFVF_CUSTOM = D3DFVF_XYZ | D3DFVF_TEX1;
	};

public:
	DTerrainClass(wchar_t *strHeightMapFile,wchar_t *strTexFile,LPDIRECT3DDEVICE9 pDevice,int widthSpaceNum,int heightSpaceNum,float fSpace,float fScale);
	~DTerrainClass();

	void DrawTerrain(bool bFrame);
};


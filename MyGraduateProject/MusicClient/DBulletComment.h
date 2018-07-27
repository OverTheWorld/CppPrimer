#pragma once
#include<d3d9.h>
#include<d3dx9.h>
#include<list>
#include"MusicFile.h"
using std::list;
const int NumLength = 500;
class DBulletComment
{
private:
	
	struct vertex
	{
		float x, y, z;
		float u, v;
	};

	struct danmaku
	{
		LPDIRECT3DSURFACE9 m_pSurface;
		LPDIRECT3DTEXTURE9 m_pTexture;
		LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
		float fLifeTime;
		float distance;
		float height;
		wstring strDanmaku;
	};

	const DWORD D3DFVF_DAN = D3DFVF_XYZ | D3DFVF_TEX1;
	D3DFORMAT m_d3dformat;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXFONT m_pFont;
	float m_fLifeTime;
	list<CommentClass> *m_plistComment;
	list<CommentClass>::iterator iTerNow;
	list<danmaku> listDanArr,listDanIng;
	void PopUp();
public:
	DBulletComment(LPDIRECT3DDEVICE9 pDevice, float fLifeTime, D3DFORMAT d3dformat);
	~DBulletComment();
	void SetCommentList(list<CommentClass> *plistComment);
	void Init();
	void Update(float DeltaTime, int timeNow);
	void Render();
	void CleanUp();
	void GetComment(CommentClass cc);
};


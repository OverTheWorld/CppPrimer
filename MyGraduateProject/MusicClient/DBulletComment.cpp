#include "DBulletComment.h"


DBulletComment::DBulletComment(LPDIRECT3DDEVICE9 pDevice, float fLifeTime, D3DFORMAT d3dformat) :m_pDevice(pDevice), m_plistComment(NULL), m_fLifeTime(fLifeTime), m_d3dformat(d3dformat)
{
	if (FAILED(D3DXCreateFontW(m_pDevice, 20, 0, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("微软雅黑"), &m_pFont)))
	{
		MessageBox(0, 0, 0, 0);
		//post an error
	}
}


DBulletComment::~DBulletComment()
{
	m_pFont->Release();
	CleanUp();
}

void DBulletComment::Init()
{
	danmaku dan;
	vertex Vertices[] =
	{
		{0,30,0,0,0},
		{100,30,0,1,0},
		{0,0,0,0,1},
		{100,0,0,1,1}
	};
	vertex *pVertices = NULL;
	for (int i = 0; i < NumLength; ++i)
	{
		if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(vertex)* 6, 0, D3DFVF_DAN, D3DPOOL_DEFAULT, &dan.m_pVertexBuffer, NULL)))
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}

		if (FAILED(dan.m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0)))
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}
		pVertices[0] = vertex{ -50.0f, -50.0f, 0.0f, 0.0f, 1.0f };
		pVertices[1] = vertex{ -50.0f, 50.0f, 0.0f, 0.0f, 0.0f };
		pVertices[2] = vertex{ 50.0f, -50.0f, 0.0f, 1.0f, 1.0f };
		pVertices[3] = vertex{ 50.0f, -50.0f, 0.0f, 1.0f, 1.0f };
		pVertices[4] = vertex{ -50.0f, 50.0f, 0.0f, 0.0f, 0.0f };
		pVertices[5] = vertex{ 50.0f, 50.0f, 0.0f, 1.0f, 0.0f };
		if (FAILED(dan.m_pVertexBuffer->Unlock()))
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}
		if (FAILED(m_pDevice->CreateTexture(100, 30, 1, D3DUSAGE_RENDERTARGET, m_d3dformat, D3DPOOL_DEFAULT, &dan.m_pTexture, NULL)))
		{
			MessageBox(0, 0, 0, 0);
			//post an error
		}
		dan.m_pTexture->GetSurfaceLevel(0, &dan.m_pSurface);
		dan.fLifeTime = 0;
		dan.distance = 1500;
		listDanArr.push_back(dan);
	}

}

void DBulletComment::SetCommentList(list<CommentClass> *plistComment)
{
	for (auto i = listDanIng.begin(); i != listDanIng.end(); )
	{
		listDanArr.push_back(*i);
		i = listDanIng.erase(i);
	}
	if (plistComment == NULL)
	{
		m_plistComment = NULL;
		return;
	}
	m_plistComment = plistComment;
	iTerNow = m_plistComment->begin();
}

void DBulletComment::Update(float DeltaTime,int timeNow)
{
	//首先加上时间，
	//检查正在运行的所有弹幕有无时间到期的，如果有将其撤出加到准备链上
	//然后检查下几条到时间点的弹幕，将其加到运行链上，准备发送。
	//
	
	if (!m_plistComment)return;

	for (auto i = listDanIng.begin(); i != listDanIng.end(); )
	{
		i->fLifeTime += DeltaTime;
		if (i->fLifeTime >= m_fLifeTime)
		{
			listDanArr.push_back(*i);
			i = listDanIng.erase(i);
		}
		else
			++i;
	}
	
	while (iTerNow != m_plistComment->end())
	{
		if (iTerNow->time >= timeNow)
		{
			break;
		}
		PopUp();
	}
}

void DBulletComment::PopUp()
{
	listDanIng.push_back(listDanArr.back());
	listDanArr.pop_back();
	auto iterNew = listDanIng.end();
	--iterNew;
	iterNew->strDanmaku = iTerNow->strComment;
	iterNew->distance = 500 +rand()%300;
	iterNew->height = 4500 + rand() % 500;
	iterNew->fLifeTime = 0;
	LPDIRECT3DSURFACE9 pBackBuffer;
	RECT rect;
	SetRect(&rect, 0, 0, 100, 30);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->GetRenderTarget(0, &pBackBuffer);
	m_pDevice->SetRenderTarget(0, iterNew->m_pSurface);
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(1,0, 0, 0), 1.0f, 0);
	m_pDevice->BeginScene();
	m_pFont->DrawTextW(NULL, iterNew->strDanmaku.c_str(), iterNew->strDanmaku.size(), &rect, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(rand()%256, rand() % 256, rand() % 256));
	m_pDevice->EndScene();
	m_pDevice->SetRenderTarget(0, pBackBuffer);
	pBackBuffer->Release();
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	++iTerNow;
}

void DBulletComment::Render()
{
	if (!m_plistComment)
		return;
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIX matWorld, matRy, matMove,matOld;
	m_pDevice->GetTransform(D3DTS_WORLD, &matOld);
	static int iCount = 0;
	++iCount;
	for (auto i = listDanIng.begin(); i != listDanIng.end(); ++i)
	{
		D3DXMatrixTranslation(&matMove, 0, i->height, i->distance);
		D3DXMatrixRotationY(&matRy, 2 * D3DX_PI*i->fLifeTime / m_fLifeTime);
		matWorld = matMove * matRy;
		m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pDevice->SetTexture(0, i->m_pTexture);
		m_pDevice->SetStreamSource(0, i->m_pVertexBuffer, 0, sizeof(vertex));
		m_pDevice->SetFVF(D3DFVF_DAN);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}

	m_pDevice->SetTransform(D3DTS_WORLD, &matOld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
void DBulletComment::CleanUp()
{
	for (auto i = listDanArr.begin(); i != listDanArr.end(); )
	{
		if (i->m_pSurface)
		{
			i->m_pSurface->Release();
		}
		if (i->m_pTexture)
		{
			i->m_pTexture->Release();
		}
		if (i->m_pVertexBuffer)
		{
			i->m_pVertexBuffer->Release();
		}
		i = listDanArr.erase(i);
	}
	for (auto i = listDanIng.begin(); i != listDanIng.end();)
	{
		if (i->m_pSurface)
		{
			i->m_pSurface->Release();
		}
		if (i->m_pTexture)
		{
			i->m_pTexture->Release();
		}
		if (i->m_pVertexBuffer)
		{
			i->m_pVertexBuffer->Release();
		}
		i = listDanIng.erase(i);
	}
	m_plistComment = NULL;
}
void DBulletComment::GetComment(CommentClass cc)
{
	if (m_plistComment)
		iTerNow = m_plistComment->insert(iTerNow, cc);
}

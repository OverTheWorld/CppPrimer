#include "DSkyClass.h"


DSkyClass::DSkyClass(
	LPDIRECT3DDEVICE9 pDevice,
	wchar_t *strLeftFile,
	wchar_t *strRightFile,
	wchar_t *strUpFile,
	wchar_t *strForwardFile,
	wchar_t *strBackFile,
	int length
	):
	m_pd3dDevice(pDevice),
	m_length(length)
{
	if (FAILED(D3DXCreateTextureFromFile(pDevice, strUpFile, &m_pd3dTexture[0])))
	{
		//post an error
	}
	if (FAILED(D3DXCreateTextureFromFile(pDevice, strLeftFile, &m_pd3dTexture[1])))
	{
		//post an error
	}
	if (FAILED(D3DXCreateTextureFromFile(pDevice, strRightFile, &m_pd3dTexture[2])))
	{
		//post an error
	}
	if (FAILED(D3DXCreateTextureFromFile(pDevice, strForwardFile, &m_pd3dTexture[3])))
	{
		//post an error
	}
	if (FAILED(D3DXCreateTextureFromFile(pDevice, strBackFile, &m_pd3dTexture[4])))
	{
		//post an error
	}

	const CustomVertex ALL[5][6] = {
		//Up
		CustomVertex(-length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(length / 2, length / 2, -length / 2, 1, 0),
		CustomVertex(length / 2, length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(length / 2, length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, length / 2, length / 2, 0, 1),
		//Left
		CustomVertex(-length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(-length / 2, length / 2, length / 2, 1, 0),
		CustomVertex(-length / 2, -length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(-length / 2, -length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, -length / 2, -length / 2, 0, 1),
		//Right
		CustomVertex(length / 2, length / 2, length / 2, 0, 0),
		CustomVertex(length / 2, length / 2, -length / 2, 1, 0),
		CustomVertex(length / 2, -length / 2, -length / 2, 1, 1),
		CustomVertex(length / 2, length / 2, length / 2, 0, 0),
		CustomVertex(length / 2, -length / 2, -length / 2, 1, 1),
		CustomVertex(length / 2, -length / 2, length / 2, 0, 1),
		//Forward
		CustomVertex(-length / 2, length / 2, length / 2, 0, 0),
		CustomVertex(length / 2, length / 2, length / 2, 1, 0),
		CustomVertex(length / 2, -length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, length / 2, length / 2, 0, 0),
		CustomVertex(length / 2, -length / 2, length / 2, 1, 1),
		CustomVertex(-length / 2, -length / 2, length / 2, 0, 1),
		//Back
		CustomVertex(length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(-length / 2, length / 2, -length / 2, 1, 0),
		CustomVertex(-length / 2, -length / 2, -length / 2, 1, 1),
		CustomVertex(length / 2, length / 2, -length / 2, 0, 0),
		CustomVertex(-length / 2, -length / 2, -length / 2, 1, 1),
		CustomVertex(length / 2, -length / 2, -length / 2, 0, 1)
	};
	CustomVertex *pData;
	for (int i = 0; i < 5; ++i)
	{
		if (FAILED(m_pd3dDevice->CreateVertexBuffer(sizeof(CustomVertex)* 6, 0, CustomVertex::D3DFVF_CUSTOM, D3DPOOL_DEFAULT, &m_pd3dVertexBuffer[i], NULL)))
		{
			//post an error
		}
		if (FAILED(m_pd3dVertexBuffer[i]->Lock(0, 0, reinterpret_cast<void**>(&pData), 0)))
		{
			//post an error
		}
		memcpy(pData, ALL[i], sizeof(ALL[i]));
		if (FAILED(m_pd3dVertexBuffer[i]->Unlock()))
		{
			//post an error
		}
	}
}
DSkyClass::~DSkyClass()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pd3dTexture[i]->Release();
		m_pd3dVertexBuffer[i]->Release();
	}
}
void DSkyClass::DrawSkyBox(D3DXMATRIX *pMatWorld)
{
	D3DXMATRIX mat;
	DWORD u, v;
	if (pMatWorld)
	{
		m_pd3dDevice->GetTransform(D3DTS_WORLD, &mat);
		m_pd3dDevice->SetTransform(D3DTS_WORLD, pMatWorld);
	}
	
	m_pd3dDevice->GetSamplerState(0, D3DSAMP_ADDRESSU, &u);
	m_pd3dDevice->GetSamplerState(0, D3DSAMP_ADDRESSV, &v);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	for (int i = 0; i < 5; ++i)
	{
		m_pd3dDevice->SetStreamSource(0, m_pd3dVertexBuffer[i], 0, sizeof(CustomVertex));
		m_pd3dDevice->SetTexture(0, m_pd3dTexture[i]);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	}
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pd3dDevice->SetTexture(0, NULL);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, u);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, v);
	if (pMatWorld)
	{
		m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
	}
}
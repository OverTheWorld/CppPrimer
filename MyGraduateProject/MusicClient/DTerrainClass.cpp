#include "DTerrainClass.h"


DTerrainClass::DTerrainClass(
	wchar_t *strHeightMapFile,
	wchar_t *strTexFile, 
	LPDIRECT3DDEVICE9 pDevice, 
	int widthSpaceNum,
	int heightSpaceNum, 
	float fSpace,
	float fScale
	) :
	m_pd3dDevice(pDevice),
	m_fScale(fScale),
	m_fSpace(fSpace),
	m_widthSpaceNum(widthSpaceNum),
	m_heightSpaceNum(heightSpaceNum),
	m_heightVerticesNum(heightSpaceNum+1),
	m_widthVerticesNum(widthSpaceNum+1),
	m_width(widthSpaceNum*fSpace),
	m_height(heightSpaceNum*fSpace),
	m_AllSpaceNum(widthSpaceNum*heightSpaceNum),
	m_AllVerticesNum((heightSpaceNum+1)*(widthSpaceNum+1))
{
	ifstream ifs(strHeightMapFile, std::ios::binary);
	ifs.seekg(0, std::ios::end);
	vector<BYTE> vecByte(ifs.tellg());
	ifs.seekg(0, std::ios::beg);
	ifs.read(reinterpret_cast<char*>(&vecByte[0]), vecByte.size());
	ifs.close();
	for (const auto &s : vecByte)
	{
		m_vecHeightMap.push_back(static_cast<float>(s)*fScale);
	}
	if (FAILED(D3DXCreateTextureFromFileW(m_pd3dDevice, strTexFile, &m_pd3dTexture)))
	{
		//post an error
	}


	if (FAILED(m_pd3dDevice->CreateVertexBuffer(sizeof(CustomVertex)*m_AllVerticesNum, 0, CustomVertex::D3DFVF_CUSTOM, D3DPOOL_DEFAULT, &m_pd3dVertexBuffer, NULL)))
	{
		//post an error
	}
	CustomVertex *pData;
	if (FAILED(m_pd3dVertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pData), 0)))
	{
		//post an error
	}
	int index = 0;
	float fStartX = -m_width / 2, fStartZ = m_height / 2;
	float fTexSpaceU = 3.0f / m_widthSpaceNum, fTexSpaceV = 3.0f / m_heightSpaceNum;
	for (int i = 0,j = 0; i < m_heightVerticesNum; ++i)
	{
		for (j = 0; j < m_widthVerticesNum; ++j)
		{
			index = i*m_widthVerticesNum + j;
			pData[index] = CustomVertex(fStartX + j*m_fSpace, m_vecHeightMap[index], fStartZ - i*m_fSpace, j*fTexSpaceU, i*fTexSpaceV);
		}
	}

	if (FAILED(m_pd3dVertexBuffer->Unlock()))
	{
		//post an error
	}

	WORD *pWord;
	if (FAILED(m_pd3dDevice->CreateIndexBuffer(sizeof(WORD)*m_AllSpaceNum * 6, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pd3dIndexBuffer, NULL)))
	{
		//post an error
	}
	if (FAILED(m_pd3dIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pWord), 0)))
	{
		//post an error
	}
	index = 0;
	for (int i = 0,j=0; i < m_heightSpaceNum; ++i)
	{
		for (j = 0; j < m_widthSpaceNum; ++j)
		{
			pWord[index++] = i*m_widthVerticesNum + j;
			pWord[index++] = i*m_widthVerticesNum + j + 1;
			pWord[index++] = (i + 1)*m_widthVerticesNum + j;
			pWord[index++] = (i + 1)*m_widthVerticesNum + j;
			pWord[index++] = i*m_widthVerticesNum + j + 1;
			pWord[index++] = (i + 1)*m_widthVerticesNum + j + 1;
		}

	}
	if (FAILED(m_pd3dIndexBuffer->Unlock()))
	{
		//post an error
	}
}
DTerrainClass::~DTerrainClass()
{
	m_pd3dIndexBuffer->Release();
	m_pd3dVertexBuffer->Release();
	m_pd3dTexture->Release();
}

void DTerrainClass::DrawTerrain(bool bFrame)
{
	D3DXMATRIX mat,matWorld;
	D3DXMatrixTranslation(&mat, 0, 0, 0);
	m_pd3dDevice->GetTransform(D3DTS_WORLD, &matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pd3dDevice->SetTexture(0, m_pd3dTexture);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_pd3dDevice->SetStreamSource(0, m_pd3dVertexBuffer, 0, sizeof(CustomVertex));
	m_pd3dDevice->SetFVF(CustomVertex::D3DFVF_CUSTOM);
	m_pd3dDevice->SetIndices(m_pd3dIndexBuffer);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_AllVerticesNum, 0, m_AllSpaceNum * 2);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pd3dDevice->SetTexture(0, m_pd3dTexture);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (bFrame)
	{
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_AllVerticesNum, 0, m_AllSpaceNum * 2);

		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}
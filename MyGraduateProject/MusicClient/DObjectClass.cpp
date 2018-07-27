#include "DObjectClass.h"


DObjectClass::DObjectClass(LPCTSTR szFile, LPDIRECT3DDEVICE9 pDevice) :m_pd3dDevice(pDevice)
{
	LPD3DXBUFFER pd3dAdjaBuffer, pd3dMaterial;
	if (FAILED(D3DXLoadMeshFromX(szFile, D3DPOOL_MANAGED, pDevice, &pd3dAdjaBuffer, &pd3dMaterial, NULL, &m_numMatrl, &m_pd3dMesh)))
	{
		//post an error
	}
	LPD3DXMATERIAL pd3dMat = static_cast<LPD3DXMATERIAL>(pd3dMaterial->GetBufferPointer());
	m_pd3dMaterial = new D3DMATERIAL9[m_numMatrl];
	m_ppd3dTexture = new LPDIRECT3DTEXTURE9[m_numMatrl];
	for (unsigned i = 0; i < m_numMatrl; ++i)
	{
		m_pd3dMaterial[i] = pd3dMat[i].MatD3D;

		string strtemp(pd3dMat[i].pTextureFilename);
		auto pos = strtemp.find_last_of("\\/");
		string str;
		if (pos != string::npos)
			str = strtemp.substr(pos);
		else
			str = strtemp;

		if (FAILED(D3DXCreateTextureFromFileA(pDevice, str.c_str(), &m_ppd3dTexture[i])))
		{
			//post an error
		}
	}
	pd3dAdjaBuffer->Release();
	pd3dMaterial->Release();
}
DObjectClass::~DObjectClass()
{
	delete m_pd3dMaterial;
	delete m_ppd3dTexture;
	m_pd3dMesh->Release();
}

bool DObjectClass::DrawObject() const
{
	for (unsigned i = 0; i < m_numMatrl; ++i)
	{
		if (FAILED(m_pd3dDevice->SetMaterial(&m_pd3dMaterial[i])))
		{
			return false;
		}
		if (FAILED(m_pd3dDevice->SetTexture(0,m_ppd3dTexture[i])))
		{
			return false;
		}
		if (FAILED(m_pd3dMesh->DrawSubset(i)))
		{
			return false;
		}
	}
	return true;
}
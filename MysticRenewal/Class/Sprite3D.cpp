#include "Stdafx.h"


CSprite3D::CSprite3D()
{

}


CSprite3D::~CSprite3D()
{
}

void CSprite3D::Update(float Tick)
{
}

void CSprite3D::Rander()
{
	TextureVerTex	vertices[4];

	// Set vertices
	vertices[0].x = Position_LT.x;
	vertices[0].y = Position_LT.y;
	vertices[0].z = Position_LT.z;
	vertices[0].tu = 0.f;
	vertices[0].tv = 0.f;

	vertices[1].x = Position_RT.x;
	vertices[1].y = Position_RT.y;
	vertices[1].z = Position_RT.z;
	vertices[1].tu = 1.f;
	vertices[1].tv = 0.f;

	vertices[2].x = Position_LB.x;
	vertices[2].y = Position_LB.y;
	vertices[2].z = Position_LB.z;
	vertices[2].tu = 0.f;
	vertices[2].tv = 1.f;

	vertices[3].x = Position_RB.x;
	vertices[3].y = Position_RB.y;
	vertices[3].z = Position_RB.z;
	vertices[3].tu = 1.0f;
	vertices[3].tv = 1.0f;

	//vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = Color;
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);


	Direct3dx::GetInstance()->Set_World_View_Matrix(Position_One.x, Position_One.y, Position_One.z);
	Direct3dx::GetInstance()->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Direct3dx::GetInstance()->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	Direct3dx::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Direct3dx::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	Direct3dx::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
	Direct3dx::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	//m_pd3dDevice->SetVertexShader(0);
	Direct3dx::GetInstance()->GetD3DDevice()->SetTexture(0, CTextureManager::GetInstance()->GetTexture(filename)->GetTexture());
	//m_pd3dDevice->SetStreamSource(0, m_pVB_Texture, 0, sizeof(TextureVerTex));
	Direct3dx::GetInstance()->GetD3DDevice()->SetFVF(D3DVERTEXTEXTURE);
	Direct3dx::GetInstance()->GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	Direct3dx::GetInstance()->GetD3DDevice()->SetTexture(0, NULL);
}

void CSprite3D::Control(UINT msg, LPARAM lParam)
{
}

bool CSprite3D::initWithFile(LPCSTR pszFilename)
{
	if (pszFilename == NULL)
	{
		return false;
	}

	CTextureManager::GetInstance()->LoadBitmapFile(pszFilename);
	CTexture * A = CTextureManager::GetInstance()->GetTexture(pszFilename);

	this->SetContentRect(
		0, 0,
		A->getPixelsWide(),
		A->getPixelsHigh()
		);

	this->SetImageSize(
		A->getPixelsWide(),
		A->getPixelsHigh()
		);

	filename = pszFilename;

	return true;
}

void CSprite3D::SetPosition(C3Point LT, C3Point RT, C3Point LB, C3Point RB)
{
	Position_LT = LT;
	Position_RT = RT;
	Position_LB = LB;
	Position_RB = RB;
}

void CSprite3D::SetPosition(C3Point Po)
{
	Position_One = Po;
}

void CSprite3D::SetPositionZ(float Z)
{
	Position_One.z = Z;
}

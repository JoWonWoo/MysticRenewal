#include "Stdafx.h"

Direct3dx* Direct3dx::Singleten = NULL;

//CDirectX_Singleton를 Singleton으로 만듬
Direct3dx* Direct3dx::GetInstance()
{
	if (Singleten == NULL)
	{
		Singleten = new Direct3dx;
	}
	return Singleten;
}

Direct3dx::Direct3dx()
{
	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	//m_pSprite = NULL;

	ZeroMemory(&m_pd3dpp, sizeof(m_pd3dpp));

}

Direct3dx::~Direct3dx()
{
	ReleaseDirect3D();
}

BOOL Direct3dx::Load(LPCSTR FileName, LPDIRECT3DTEXTURE9 * pTexture, D3DCOLOR ColorKey, BOOL bColorKey /*= TRUE*/)
{
	if (FAILED(D3DXCreateTextureFromFileExA(
		m_pd3dDevice,
		FileName,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		//	D3DPOOL_SYSTEMMEM,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR,
		D3DX_FILTER_LINEAR,
		(!bColorKey ? NULL : ColorKey),
		NULL,
		NULL,
		pTexture)))
	{
		MessageBox(NULL, "리소스 파일이 없습니다. 로그를 확인하세요", "알림", MB_OK);
		CCLog("%s 리소스 파일이 없습니다.", FileName);
		return FALSE;
	}
	return TRUE;
}

//HRESULT Direct3dx::InitDirect3D(HWND hWnd, int Width, int Height , BOOL Window_flag, D3DSWAPEFFECT SwapEffect)
HRESULT Direct3dx::InitDirect3D(HWND hWnd, int Width, int Height, BOOL Window_flag)
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;	//에러 방지
	ZeroMemory(&m_pd3dpp, sizeof(m_pd3dpp));	//초기화

	m_pd3dpp.Windowed = Window_flag;					//전체화면 설정 true = 윈도우
	m_pd3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 백버퍼 스왑방식 설정, 
	/************************************************************************/
	/*
	DISCARD : 백버퍼를 복사하지 않고 프론트 버퍼로 교체하는 방식.
	COPY : 백버퍼를 프론트 버퍼로 복사하여 Present 한다.
	FLIP : 다중의 백버퍼가 프론트 버퍼로 복사되어진다.
	DISCARD+FLIP : 다중의 백버퍼가 돌아가면서 프론트 버퍼로 설정
	*/
	/************************************************************************/
	//m_pd3dpp.BackBufferFormat = D3DFMT_UNKNOWN;						// 디바이스가 지원하는 포멧설정,윈도우모드에선 D3DFMT_WNKNOWN설정하면 디스플레이 포멧으로 자동설정 
	//7.25 블로그 까페에서 삼각형이 안떠서 수정함.ㅣ.......

	m_pd3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;					// 디바이스가 지원하는 포멧설정,윈도우모드에선 D3DFMT_WNKNOWN설정하면 디스플레이 포멧으로 자동설정 
	m_pd3dpp.BackBufferWidth = Width;								//백버퍼 크기 설정 : 전체화면이 아닐때 가로 사이즈
	m_pd3dpp.BackBufferHeight = Height;								//백버퍼 크기 설정 : 전체화면이 아닐때 세로 사이즈
	m_pd3dpp.BackBufferCount = 1;									// 그냥 1입력한다.(?)
	m_pd3dpp.EnableAutoDepthStencil = true;							// 깊이, 스텐실 버퍼 사용설정
	m_pd3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	// 깊이 스텐실 버퍼 포멧설정
	//m_pd3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//m_pd3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//m_pd3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// Create the D3DDevice
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_pd3dpp,
		&m_pd3dDevice
		))
		)
	{
		return E_FAIL;
	}

	/************************************************************************/
	/*
	LoadCursor 2번째 매개변수는 리소스 명
	SetCursor(LoadCursor(0 , IDC_WAIT));
	SetCursor(LoadCursor(0 , IDC_CROSS));
	SetCursor(LoadCursor(0 , IDC_IBEAM));
	SetCursor(LoadCursor(0 , IDC_UPARROW));
	[출처] [API]LoadCursor,SetCursor사용|작성자 헤더막스
	*/
	/************************************************************************/
	//D3DSAMP_MAGFILTER 확대된 필터
	//D3DSAMP_MINFILTER 축소된 필터
	//D3DSAMP_MIPFILTER 표준 필터

	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);	//퀼리티는 낮지만 속도가 가장빠름
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );		//평균 품질에 속도는 평균
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC );	//높은 품질에 속도는 최하
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC );
	//m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC );

	/*if (D3DXCreateSprite(m_pd3dDevice, &m_pSprite) != S_OK)
	{
	return E_FAIL;
	}*/
	//	

	/// 정점에 색깔값이 있으므로, 광원기능을 끈다.
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	InItFontA(30, 30);

	if (FAILED(m_pd3dDevice->CreateVertexBuffer(4 * sizeof(TextureVerTex), 0, D3DVERTEXTEXTURE, D3DPOOL_DEFAULT, &m_pVB_Texture, NULL)))
		return E_FAIL;

	if (FAILED(this->m_pd3dDevice->CreateVertexBuffer(4 * sizeof(ColorBoxVertex), 0, D3DVERTEXCOLORBOX, D3DPOOL_DEFAULT, &m_pVB_Color_Box, NULL)))
		return E_FAIL;

	Set_Camera_Matrix();

	return S_OK;
}

void Direct3dx::InItFontA(int _x, int _y)
{
	D3DXCreateFontA(m_pd3dDevice, _x, _y, 0, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "돋움체", &m_pFont);
}

BOOL Direct3dx::BeginScreen()
{
	if (m_pd3dDevice)
	{
		m_pd3dDevice->BeginScene();

		return TRUE;
	}
	CCLog("CDirectX_Singleton::BeginScreen에서 에러");
	return FALSE;
}

BOOL Direct3dx::EndScreen()
{
	if (m_pd3dDevice)
	{
		m_pd3dDevice->EndScene();

		return TRUE;
	}
	CCLog("CDirectX_Singleton::EndScreen에서 에러");

	return FALSE;
}

BOOL Direct3dx::BeginSprite()
{
	if (m_pSprite)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		return TRUE;
	}
	CCLog("CDirectX_Singleton::BeginSprite에서 에러");

	return FALSE;
}

BOOL Direct3dx::EndSprite()
{
	if (m_pSprite)
	{
		m_pSprite->End();
		return TRUE;
	}
	CCLog("CDirectX_Singleton::EndSprite에서 에러");
	return FALSE;

}

BOOL Direct3dx::Present()
{
	if (m_pd3dDevice)
	{
		m_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		return TRUE;
	}
	CCLog("CDirectX_Singleton::Present에서 에러");
	return FALSE;

}

BOOL Direct3dx::Clear(D3DCOLOR color)
{
	if (m_pd3dDevice)
	{
		//	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, color, 1.0f, 0);
		m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, color, 100.0f, 0);
		//Direct3dx::GetInstance()->GetD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
		return TRUE;
	}
	CCLog("CDirectX_Singleton::Clear에서 에러");

	return FALSE;
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, 0, 1, 1, 0);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, 1, 1, 0);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float Angle)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, Angle, D3DCOLOR_XRGB(255, 255, 255), 1, 1, 1, 1);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float Angle, D3DXCOLOR Color)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, Angle, Color, 1, 1, 1, 1);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, D3DXCOLOR Color)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, Color, 1, 1, 1, 1);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, AngleZ, Color, 1, 1, 1, 1);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y,
	int z_order, float ScaleX, float ScaleY, float Angle, D3DXCOLOR Color, float m_vid_width /*= 1.0f*/, float m_tex_width /*= 1.0f*/, float m_vid_height /*= 1.0f*/, float m_tex_height /*= 1.0f*/)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, Angle, Angle, Color, m_vid_width, m_tex_width, m_vid_height, m_tex_height);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y,
	int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, 0, Color, m_vid_width, m_tex_width, m_vid_height, m_tex_height);

}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y,
	int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, AngleZ, Color, m_vid_width, m_tex_width, m_vid_height, m_tex_height, 0, 0);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y,
	int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY,
		AngleX, AngleY, AngleZ, Color,
		Texture_Rect.m_size.width, Image_Width, Texture_Rect.m_size.height, Image_Height, 0, 0);

	//TextureVerTex	vertices[4];

	//float old_x = Image_Width * ScaleX;
	//float old_y = Image_Height * ScaleY;
	//float x = (old_x * cos(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * sin(CC_DEGREES_TO_RADIANS(AngleZ)));
	//float y = -(old_x * sin(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * cos(CC_DEGREES_TO_RADIANS(AngleZ)));
	////	x = x*cos(CC_DEGREES_TO_RADIANS(AngleY));	//Y축 회전
	////	y = y*cos(CC_DEGREES_TO_RADIANS(AngleX));	//y축 회전

	//// Set vertices
	//vertices[0].x = 0;
	//vertices[0].y = 0;
	//vertices[0].tu = Texture_Rect.m_positon.x == Image_Width ? 0.0f : (float)(Texture_Rect.m_positon.x / Image_Width);
	//vertices[0].tv = Texture_Rect.m_positon.y == Image_Height ? 0.0f : (float)(Texture_Rect.m_positon.y / Image_Height);

	//vertices[1].x = x;
	//vertices[1].y = 0;
	//vertices[1].tu = 1.0f *(float)((Texture_Rect.m_positon.x + Texture_Rect.m_size.width) / Image_Width);
	//vertices[1].tv = Texture_Rect.m_positon.y == Image_Height ? 0.0f : (float)(Texture_Rect.m_positon.y / Image_Height);

	//vertices[2].x = 0;
	//vertices[2].y = y;
	//vertices[2].tu = Texture_Rect.m_positon.x == Image_Width ? 0.0f : (float)(Texture_Rect.m_positon.x / Image_Width);
	//vertices[2].tv = 1.0f *(float)((Texture_Rect.m_positon.y + Texture_Rect.m_size.height) / Image_Height);

	//vertices[3].x = x;
	//vertices[3].y = y;
	//vertices[3].tu = 1.0f *(float)((Texture_Rect.m_positon.x + Texture_Rect.m_size.width) / Image_Width);
	//vertices[3].tv = 1.0f *(float)((Texture_Rect.m_positon.y + Texture_Rect.m_size.height) / Image_Height);

	//vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.0f;
	//vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = Color;
	////vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);

	//Set_World_View_Matrix(Position_x, Position_y, z_order);
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	///*m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//*/
	///////////////////////////////// 색상 ///////////////////////////////////////
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);     //< 연산자 ( 연산 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);     //< 대상 ( 인수 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);             //< 대상 ( 인수 )
	/////////////////////////////// 투명도 ////////////////////////////////////
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);    //< 연산자 ( 연산 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);    //< 대상 ( 인수 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);            //< 대상 ( 인수 )


	//m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
	////	m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCMP_GREATER);

	//m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////m_pd3dDevice->SetVertexShader(0);
	//m_pd3dDevice->SetTexture(0, Texture);
	////m_pd3dDevice->SetStreamSource(0, m_pVB_Texture, 0, sizeof(TextureVerTex));
	//m_pd3dDevice->SetFVF(D3DVERTEXTEXTURE);
	//m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	//m_pd3dDevice->SetTexture(0, NULL);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX,
	float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height, float anchor_x, float anchor_y)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY,
		AngleX, AngleY, AngleZ, Color,
		0,0,m_vid_width, m_tex_width, m_vid_height, m_tex_height, anchor_x, anchor_y);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect, float anchor_x, float anchor_y)
{
	DrawTexture_2D(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY,
		AngleX, AngleY, AngleZ, Color, Texture_Rect.m_positon.x, Texture_Rect.m_positon.y,
		Texture_Rect.m_size.width, Image_Width, Texture_Rect.m_size.height, Image_Height, anchor_x, anchor_y);
}

void Direct3dx::DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vld_x, float m_vld_y, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height, float anchor_x, float anchor_y)
{
	TextureVerTex	vertices[4];

	//float old_x = Image_Width * ScaleX;
	//float old_y = Image_Height * ScaleY;
	//D3DXVECTOR2 te = D3DXVECTOR2(0, 0);
	//D3DXMATRIXA16 angle;
	//D3DXMatrixRotationZ(&angle, CC_DEGREES_TO_RADIANS(AngleZ));
	//D3DXVec2TransformCoord(&te, &te, &angle);
	//D3DXMatrixTranslation(&angle, old_x, old_y, 0);
	//D3DXVec2TransformCoord(&te, &te, &angle);


	//float x = te.x;// (old_x * cos(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * sin(CC_DEGREES_TO_RADIANS(AngleZ)));
	//float y = te.y;// -(old_x * sin(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * cos(CC_DEGREES_TO_RADIANS(AngleZ)));
	////	x = x*cos(CC_DEGREES_TO_RADIANS(AngleY));	//Y축 회전
	////	y = y*cos(CC_DEGREES_TO_RADIANS(AngleX));	//x축 회전

	float x = Image_Width * ScaleX;
	float y = Image_Height * ScaleY;

	D3DXVECTOR2 po1 = D3DXVECTOR2(0 - (anchor_x * x), 0 - (anchor_y * y));
	D3DXVECTOR2 po2 = D3DXVECTOR2(x - (anchor_x * x), 0 - (anchor_y * y));
	D3DXVECTOR2 po3 = D3DXVECTOR2(0 - (anchor_x * x), y - (anchor_y * y));
	D3DXVECTOR2 po4 = D3DXVECTOR2(x - (anchor_x * x), y - (anchor_y * y));
	D3DXMATRIXA16 angleZ;
	D3DXMATRIXA16 angleY;
	D3DXMATRIXA16 angleX;
	D3DXMATRIXA16 angle;
	D3DXMatrixRotationZ(&angleZ, CC_DEGREES_TO_RADIANS(AngleZ));
	D3DXMatrixRotationY(&angleY, CC_DEGREES_TO_RADIANS(AngleY));
	D3DXMatrixRotationX(&angleX, CC_DEGREES_TO_RADIANS(AngleX));
	angle = angleZ * angleY * angleX;
	D3DXVec2TransformCoord(&po1, &po1, &angle);
	D3DXVec2TransformCoord(&po2, &po2, &angle);
	D3DXVec2TransformCoord(&po3, &po3, &angle);
	D3DXVec2TransformCoord(&po4, &po4, &angle);


	// Set vertices
	vertices[0].x = po1.x;
	vertices[0].y = po1.y;
	vertices[0].tu = 1.0f *((float)m_vld_x / m_tex_width);
	vertices[0].tv = 1.0f *((float)m_vld_y / m_tex_height);

	vertices[1].x = po2.x;
	vertices[1].y = po2.y;
	vertices[1].tu = 1.0f *((float)(m_vld_x+m_vid_width) / m_tex_width);
	vertices[1].tv = 1.0f *((float)m_vld_y / m_tex_height);

	vertices[2].x = po3.x;
	vertices[2].y = po3.y;
	vertices[2].tu = 1.0f *((float)m_vld_x / m_tex_width);
	vertices[2].tv = 1.0f *((float)(m_vld_y + m_vid_height) / m_tex_height);

	vertices[3].x = po4.x;
	vertices[3].y = po4.y;
	vertices[3].tu = 1.0f *((float)(m_vld_x + m_vid_width) / m_tex_width);
	vertices[3].tv = 1.0f *((float)(m_vld_y+m_vid_height )/ m_tex_height);

	vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.0f;
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = Color;
	//vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);

	Set_World_View_Matrix(Position_x, Position_y, z_order);

	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	/*m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	*/
	/////////////////////////////// 색상 ///////////////////////////////////////
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);     //< 연산자 ( 연산 )
	//	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);     //< 연산자 ( 연산 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);     //< 대상 ( 인수 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);             //< 대상 ( 인수 )
	///////////////////////////// 투명도 ////////////////////////////////////
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);    //< 연산자 ( 연산 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);    //< 대상 ( 인수 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);            //< 대상 ( 인수 )

	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pd3dDevice->SetVertexShader(0);
	m_pd3dDevice->SetTexture(0, Texture);
	//m_pd3dDevice->SetStreamSource(0, m_pVB_Texture, 0, sizeof(TextureVerTex));
	m_pd3dDevice->SetFVF(D3DVERTEXTEXTURE);
	m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	m_pd3dDevice->SetTexture(0, NULL);
}

void Direct3dx::DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height)
{
	DrawTexture_2D_UI(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, AngleZ, Color, m_vid_width, m_tex_width, m_vid_height, m_tex_height, 0, 0);
}

void Direct3dx::DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect)
{
	DrawTexture_2D_UI(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, AngleZ, Color,
		Texture_Rect.m_size.width, Image_Width, Texture_Rect.m_size.height, Image_Height, 0, 0);


	//TextureVerTexUI	vertices[4];

	//float old_x = Image_Width * ScaleX;
	//float old_y = Image_Height * ScaleY;
	//float x = (old_x * cos(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * sin(CC_DEGREES_TO_RADIANS(AngleZ)));
	//float y = -(old_x * sin(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * cos(CC_DEGREES_TO_RADIANS(AngleZ)));
	////	x = x*cos(CC_DEGREES_TO_RADIANS(AngleY));	//Y축 회전
	////	y = y*cos(CC_DEGREES_TO_RADIANS(AngleX));	//y축 회전

	//// Set vertices
	//vertices[0].x = Position_x;
	//vertices[0].y = Position_y;
	//vertices[0].tu = Texture_Rect.m_positon.x == Image_Width ? 0.0f : (float)(Texture_Rect.m_positon.x / Image_Width);
	//vertices[0].tv = Texture_Rect.m_positon.y == Image_Height ? 0.0f : (float)(Texture_Rect.m_positon.y / Image_Height);

	//vertices[1].x = Position_x+x;
	//vertices[1].y = Position_y;
	//vertices[1].tu = 1.0f *(float)((Texture_Rect.m_positon.x + Texture_Rect.m_size.width) / Image_Width);
	//vertices[1].tv = Texture_Rect.m_positon.y == Image_Height ? 0.0f : (float)(Texture_Rect.m_positon.y / Image_Height);

	//vertices[2].x = Position_x;
	//vertices[2].y = Position_y+y;
	//vertices[2].tu = Texture_Rect.m_positon.x == Image_Width ? 0.0f : (float)(Texture_Rect.m_positon.x / Image_Width);
	//vertices[2].tv = 1.0f *(float)((Texture_Rect.m_positon.y + Texture_Rect.m_size.height) / Image_Height);

	//vertices[3].x = Position_x+x;
	//vertices[3].y = Position_y+y;
	//vertices[3].tu = 1.0f *(float)((Texture_Rect.m_positon.x + Texture_Rect.m_size.width) / Image_Width);
	//vertices[3].tv = 1.0f *(float)((Texture_Rect.m_positon.y + Texture_Rect.m_size.height) / Image_Height);

	//vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.0f;
	//vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = Color;
	//vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0;
	////vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);

	//Set_World_View_Matrix(0, 0,0);

	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	///*m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pd3dDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//*/
	///////////////////////////////// 색상 ///////////////////////////////////////
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);     //< 연산자 ( 연산 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);     //< 대상 ( 인수 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);             //< 대상 ( 인수 )
	/////////////////////////////// 투명도 ////////////////////////////////////
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);    //< 연산자 ( 연산 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);    //< 대상 ( 인수 )
	//m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);            //< 대상 ( 인수 )


	//m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
	////	m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCMP_GREATER);

	//m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pd3dDevice->SetTexture(0, Texture);
	//m_pd3dDevice->SetFVF(D3DVERTEXTEXTUREUI);
	//m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	//m_pd3dDevice->SetTexture(0, NULL);
}

void Direct3dx::DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height, float anchor_x, float anchor_y)
{
	TextureVerTexUI	vertices[4];

	float old_x = Image_Width * ScaleX;
	float old_y = Image_Height * ScaleY;
	float x = (old_x * cos(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * sin(CC_DEGREES_TO_RADIANS(AngleZ)));
	float y = -(old_x * sin(CC_DEGREES_TO_RADIANS(AngleZ))) + (old_y * cos(CC_DEGREES_TO_RADIANS(AngleZ)));
	//	x = x*cos(CC_DEGREES_TO_RADIANS(AngleY));	//Y축 회전
	//	y = y*cos(CC_DEGREES_TO_RADIANS(AngleX));	//y축 회전

	// Set vertices
	vertices[0].x = Position_x - (anchor_x * x);
	vertices[0].y = Position_y - (anchor_y * y);
	vertices[0].tu = 0.0f;
	vertices[0].tv = 0.0f;

	vertices[1].x = Position_x + x - (anchor_x * x);
	vertices[1].y = Position_y - (anchor_y * y);
	vertices[1].tu = 1.0f *((float)m_vid_width / m_tex_width);
	vertices[1].tv = 0.0f;

	vertices[2].x = Position_x - (anchor_x * x);
	vertices[2].y = Position_y + y - (anchor_y * y);
	vertices[2].tu = 0.0f;
	vertices[2].tv = 1.0f *((float)m_vid_height / m_tex_height);

	vertices[3].x = Position_x + x - (anchor_x * x);
	vertices[3].y = Position_y + y - (anchor_y * y);
	vertices[3].tu = 1.0f *((float)m_vid_width / m_tex_width);
	vertices[3].tv = 1.0f *((float)m_vid_height / m_tex_height);

	vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.0f;
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = Color;
	vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
	//vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = D3DCOLOR_XRGB(255, 255, 255);

	Set_World_View_Matrix(0, 0, 0);

	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	/*m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(3, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	*/
	/////////////////////////////// 색상 ///////////////////////////////////////
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);     //< 연산자 ( 연산 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);     //< 대상 ( 인수 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);             //< 대상 ( 인수 )
	///////////////////////////// 투명도 ////////////////////////////////////
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);    //< 연산자 ( 연산 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);    //< 대상 ( 인수 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);            //< 대상 ( 인수 )


	m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);
	//	m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCMP_GREATER);

	m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pd3dDevice->SetVertexShader(0);
	m_pd3dDevice->SetTexture(0, Texture);
	//m_pd3dDevice->SetStreamSource(0, m_pVB_Texture, 0, sizeof(TextureVerTex));
	m_pd3dDevice->SetFVF(D3DVERTEXTEXTUREUI);
	m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	m_pd3dDevice->SetTexture(0, NULL);
}

void Direct3dx::DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height, float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect, float anchor_x, float anchor_y)
{
	DrawTexture_2D_UI(Texture, Image_Width, Image_Height, Position_x, Position_y, z_order, ScaleX, ScaleY, AngleX, AngleY, AngleZ, Color,
		Texture_Rect.m_size.width, Image_Width, Texture_Rect.m_size.height, Image_Height, anchor_x, anchor_y);
}

void Direct3dx::DrawColorBox(CPoint potision, CSize _Size, D3DCOLOR Color)
{
	ColorBoxVertex vertices[] =
	{
		{ 0, 0, 0.0f, Color, },
		{ 0 + _Size.width, 0, 0.0f, Color, },
		{ 0, 0 + _Size.height, 0.0f, Color, },
		{ 0 + _Size.width, 0 + _Size.height, 0.0f, Color, },
	};
	Set_World_View_Matrix(potision.x, potision.y, 10);
	m_pd3dDevice->SetFVF(D3DVERTEXCOLORBOX);
	DWORD temp;
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pd3dDevice->GetTextureStageState(0, D3DTSS_COLOROP, &temp);     //< 연산자 ( 연산 )
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);     //< 연산자 ( 연산 )
	m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(vertices[0]));
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, temp);     //< 연산자 ( 연산 )
}


void Direct3dx::SetTextFLOAT(TCHAR *_Str, int _cx, int _cy)
{
	RECT rectTemp = { _cx, _cy, _cx + 350, _cy + 300 }; // 출력할 영역 설정
	m_pFont->DrawTextA(m_pSprite, _Str, -1, &rectTemp, 0, 0xFFFFFFFF);
}

void Direct3dx::ReleaseDirect3D()
{
	/*if (m_pSprite != NULL)
	{
	m_pSprite->Release();
	m_pSprite = NULL;
	}*/
	/*if (m_pd3dDevice != NULL)
	{
	m_pd3dDevice->Release();
	m_pd3dDevice = NULL;
	}
	if (m_pD3D != NULL)
	{
	m_pD3D->Release();
	m_pD3D = NULL;
	}

	if (m_pVB_Texture != NULL)
	{
	m_pVB_Texture->Release();
	m_pVB_Texture = NULL;
	}

	if (m_pVB_Color_Box != NULL)
	{
	m_pVB_Color_Box->Release();
	m_pVB_Color_Box = NULL;
	}*/

}

void Direct3dx::Destory()
{
	if (Singleten != NULL)
		delete Singleten;
}

void Direct3dx::DrawTest()
{
	/// 삼각형을 렌더링하기위해 세개의 정점을 선언
	ColorBoxVertex g_Vertices[] =
	{
		{ -1.0f, -1.0f, 0.0f, 0xffff0000, },
		{ 1.0f, -1.0f, 0.0f, 0xff0000ff, },
		{ 0.0f, 1.0f, 0.0f, 0xffffffff, },
	};

	/// 정점버퍼를 값으로 채운다. 
	VOID* pVertices;
	if (FAILED(m_pVB_Color_Box->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	m_pVB_Color_Box->Unlock();
	//VOID * pVertices;
	//if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	//	return;

	//memcpy(pVertices, vertices, sizeof(vertices));

	//m_pVB->Unlock();

	/// 컬링기능을 끈다. 삼각형의 앞면, 뒷면을 모두 렌더링한다.
	//	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	//	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	Set_Camera_Matrix();

	/// 정점버퍼의 내용을 그린다.
	m_pd3dDevice->SetStreamSource(0, m_pVB_Color_Box, 0, sizeof(ColorBoxVertex));
	m_pd3dDevice->SetFVF(D3DVERTEXCOLORBOX);
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);


	//m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(ColorBoxVertex));
	//m_pd3dDevice->SetFVF(D3DVERTEXCOLORBOX);
}

void Direct3dx::Set_World_View_Matrix(float x, float y)
{
	Set_World_View_Matrix(CPoint(x, y));
}


//월드 행렬
void Direct3dx::Set_World_View_Matrix(CPoint _Position)
{
	Set_World_View_Matrix(D3DXVECTOR3(_Position.x, _Position.y, 0));
}

void Direct3dx::Set_World_View_Matrix(float x, float y, float z)
{
	Set_World_View_Matrix(D3DXVECTOR3(x, y, z));
}

void Direct3dx::Set_World_View_Matrix(D3DXVECTOR3 _Position)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixTranslation(&matWorld, _Position.x, _Position.y, _Position.z);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}


void Direct3dx::Set_Camera_Matrix()
{
	/*/// 뷰행렬을 정의하기 위해서는 세가지값이 필요하다.
	D3DXVECTOR3 vEyePt(Director::GetInstance()->Get_Winodw_Size().width / 2 + Camera.x, Director::GetInstance()->Get_Winodw_Size().height / 2 + Camera.y, 5.0f);							/// 1. 눈의 위치( 0, 3.0, -5)
	D3DXVECTOR3 vLookatPt(Director::GetInstance()->Get_Winodw_Size().width / 2 + Camera.x, Director::GetInstance()->Get_Winodw_Size().height / 2 + Camera.y, 0.0f);						/// 2. 눈이 바라보는 위치( 0, 0, 0 )
	D3DXVECTOR3 vUpVec(0.0f, -1.0f, 0.0f);							/// 3. 천정방향을 나타내는 상방벡터( 0, 1, 0 )

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성
	*/
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &Camera::GetInstance()->Get_Camera_Matrix());				/// 생성한 뷰행렬을 디바이스에 설정

	///// 프로젝션 행렬을 정의하기 위해서는 시야각(FOV=Field Of View)과 종횡비(aspect ratio), 클리핑 평면의 값이 필요하다.
	//D3DXMATRIXA16 matProj;
	///// matProj   : 값이 설정될 행렬
	///// D3DX_PI/4 : FOV(D3DX_PI/4 = 45도)
	///// 1.0f      : 종횡비
	///// 1.0f      : 근접 클리핑 평면(near clipping plane)
	///// 100.0f    : 원거리 클리핑 평면(far clipping plane)
	////	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	//D3DXMatrixOrthoLH(&matProj, Director::GetInstance()->Get_Winodw_Size().width, Director::GetInstance()->Get_Winodw_Size().height, 0, 100);

	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &Camera::GetInstance()->Get_Proj_Matrix());		/// 생성한 프로젝션 행렬을 디바이스에 설정


}

void Direct3dx::Set_Camera_2D(float x, float y)
{
	Camera.x = x;
	Camera.y = y;
}

void Direct3dx::Set_Camera_2D(CPoint _Position)
{
	Camera = _Position;
}

void Direct3dx::Move_Camera_2D(float x, float y)
{
	Camera.x += x;
	Camera.y += y;
}

void Direct3dx::Move_Camera_2D(CPoint _Position)
{
	Camera += _Position;
}

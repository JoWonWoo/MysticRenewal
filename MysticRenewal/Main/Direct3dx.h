#pragma once

#include "Stdafx.h"

#define D3DVERTEXCOLORBOX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define D3DVERTEXTEXTURE (D3DFVF_XYZ | D3DFVF_DIFFUSE |  D3DFVF_TEX1)

#define D3DVERTEXTEXTUREUI (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |  D3DFVF_TEX1)

struct ColorBoxVertex
{
	FLOAT x, y, z;
	//	FLOAT rhw;
	DWORD color;
};

struct TextureVerTex
{
	FLOAT x, y, z;
	//	FLOAT rhw;
	DWORD color;
	FLOAT tu, tv;
};

struct TextureVerTexUI
{
	FLOAT x, y, z;
	FLOAT rhw;
	DWORD color;
	FLOAT tu, tv;
};

class Direct3dx
{
private:
	static Direct3dx* Singleten;
	Direct3dx();
	virtual  ~Direct3dx();
public:
	static Direct3dx* GetInstance();



	void DrawObject(int iXPos, int iYPos, float fXSize, float fYSize, int iTexture);

	BOOL Load(LPCSTR FileName, LPDIRECT3DTEXTURE9 * pTexture, D3DCOLOR ColorKey, BOOL bColorKey = TRUE);

	//DX 초기화및 기본 설정 
	HRESULT InitDirect3D(HWND hWnd, int Width, int Height, BOOL Window_flag = TRUE);

	void ReleaseDirect3D();			//Direct3D 해제
	BOOL BeginScreen();				//스크린 Begin
	BOOL EndScreen();				//스크린 End
	BOOL BeginSprite();				//스프라이트 Begin
	BOOL EndSprite();				//스프라이트 End
	BOOL Clear(D3DCOLOR color);		//화면포멧
	BOOL Present();					//화면 교체

	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float Angle);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float Angle, D3DXCOLOR Color);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, D3DXCOLOR Color);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX,
		float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX,
		float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect, float anchor_x, float anchor_y);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float Angle,
		D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY,
		D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ,
		D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height);
	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX,
		float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height,
		float m_tex_height, float anchor_x, float anchor_y);

	void DrawTexture_2D(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX,
		float AngleY, float AngleZ, D3DXCOLOR Color,float m_vld_x, float m_vld_y, float m_vid_width, float m_tex_width, float m_vid_height,
		float m_tex_height, float anchor_x, float anchor_y);


	void DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect);
	void DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, CRect Texture_Rect, float anchor_x, float anchor_y);
	void DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX, float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height, float m_tex_height);
	void DrawTexture_2D_UI(LPDIRECT3DTEXTURE9 Texture, float Image_Width, float Image_Height,
		float Position_x, float Position_y, int z_order, float ScaleX, float ScaleY, float AngleX,
		float AngleY, float AngleZ, D3DXCOLOR Color, float m_vid_width, float m_tex_width, float m_vid_height,
		float m_tex_height, float anchor_x, float anchor_y);



	void DrawColorBox(CPoint potision, CSize _Size, D3DCOLOR Color);

	void DrawTest();

	LPDIRECT3DDEVICE9 GetD3DDevice(){ return m_pd3dDevice; }
	void Destory();


	void Set_Camera_2D(float x, float y);
	void Set_Camera_2D(CPoint _Position);
	void Move_Camera_2D(float x, float y);
	void Move_Camera_2D(CPoint _Position);

	//텍스트 뿌리기
	void SetTextFLOAT(TCHAR *_Str, int _cx, int _cy);

	//월드좌표
	void Set_World_View_Matrix(float x, float y);
	void Set_World_View_Matrix(CPoint _Position);
	void Set_World_View_Matrix(float x, float y, float z);
	void Set_World_View_Matrix(D3DXVECTOR3 _Position);

private:
	CPoint Camera;
public:
	//카메라
	void Set_Camera_Matrix();

	void InItFontA(int _x, int _y);


public:
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	LPDIRECT3DVERTEXBUFFER9 m_pVB_Color_Box;
	LPDIRECT3DVERTEXBUFFER9 m_pVB_Texture;

	LPDIRECT3D9 GetD3D9(){ return m_pD3D; }
protected:
	LPDIRECT3D9 m_pD3D;
	D3DPRESENT_PARAMETERS m_pd3dpp;
};


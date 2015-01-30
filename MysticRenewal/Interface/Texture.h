#pragma once
#include "Stdafx.h"
class CTexture : public CNode
{
private:
	int PixelsWide;
	int PixelsHigh;

	void Reset_Pixelsize();

	//LPCSTR FileName;
public:
	LPDIRECT3DTEXTURE9 Texture;
	
	CTexture();
	~CTexture();

	LPDIRECT3DTEXTURE9 GetTexture();
	void SetTexture(LPDIRECT3DTEXTURE9 tex);
	void SetTexture(CTexture *tex);

	int getPixelsWide();
	int getPixelsHigh();

	void SetPixelSize(CSize _size);
	void SetPixelSize(int wide, int high);

	void SetFileName(std::string _name);

	void Release();
};
//나중에 뭐가 추가될지 몰라서 작성..


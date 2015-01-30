#include "Stdafx.h"


CTexture::CTexture()
{
	PixelsWide = -1;
	PixelsHigh = -1;
	Texture = NULL;
}


CTexture::~CTexture()
{
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return Texture;
}

void CTexture::SetTexture(LPDIRECT3DTEXTURE9 tex)
{
	Texture = tex;
}

void CTexture::SetTexture(CTexture *tex)
{
	Texture = tex->GetTexture();
}

int CTexture::getPixelsWide()
{
	return PixelsWide;

}

int CTexture::getPixelsHigh()
{
	return PixelsHigh;
}

void CTexture::Reset_Pixelsize()
{

	D3DXIMAGE_INFO ImageInfo;
	D3DXGetImageInfoFromFile(filename.c_str(), &ImageInfo);

	this->SetPixelSize(
	ImageInfo.Width,
	ImageInfo.Height
	);


}

void CTexture::SetPixelSize(CSize _size)
{
	PixelsWide = _size.width;
	PixelsHigh = _size.height;
}

void CTexture::SetPixelSize(int wide, int high)
{
	SetPixelSize(CSize(wide, high));
}

void CTexture::Release()
{
	CTextureManager::GetInstance()->ReleaseTexture(filename);
}

void CTexture::SetFileName(std::string _name)
{
	filename = _name;
}

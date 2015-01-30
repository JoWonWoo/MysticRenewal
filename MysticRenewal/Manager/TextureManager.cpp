#include "Stdafx.h"


CTextureManager * CTextureManager::Singleten = NULL;
CTextureManager * CTextureManager::GetInstance()
{
	if (Singleten == NULL)
		Singleten = new CTextureManager();

	return Singleten;
}

CTextureManager::CTextureManager()
{

}

CTextureManager::~CTextureManager(void)
{

	auto it =  mBitmapMap.begin();

	while (it != mBitmapMap.end())
	{
		CTexture * _pD3Texture = it->second;
		if (_pD3Texture != NULL)
		{
			_pD3Texture->GetTexture()->Release();
			delete _pD3Texture;
		}

		it = mBitmapMap.erase(it);
		it++;

	}
	if (mBitmapMap.empty() != NULL)
	{
		mBitmapMap.clear();
	}
}

CTexture * CTextureManager::GetTexture(std::string FileName)
{
	auto it = mBitmapMap.begin();
	for (; it != mBitmapMap.end(); it++)
	{
		if (FileName == it->first)
		{
			return it->second;
		}
	}
	//로딩된게 있으면 재 로딩 하지않는다.

	LoadBitmapFile(FileName); //없다면 로딩을 한다.
	it = mBitmapMap.find(FileName);

	return it->second;
}

void CTextureManager::LoadBitmapFile(std::string FileName)
{
	auto it = mBitmapMap.begin();
	for (; it != mBitmapMap.end(); it++)
	{
		if (FileName == it->first)
		{
			return;	//로딩된게있다면 하지않는다.
		}
	}

	CTexture * _texture = new CTexture();

	mBitmapMap.insert(std::pair <std::string, CTexture *>(FileName, _texture));
	it = mBitmapMap.find(FileName);

	Direct3dx::GetInstance()->Load(FileName.c_str(), &it->second->Texture, NULL);

	D3DXIMAGE_INFO ImageInfo;
	D3DXGetImageInfoFromFile(FileName.c_str(), &ImageInfo);

	it->second->SetPixelSize(CSize(ImageInfo.Width, ImageInfo.Height));
	it->second->SetFileName(FileName);
	it->second->SetContentRect(0,0,ImageInfo.Width, ImageInfo.Height);
	it->second->SetImageSize(CSize(ImageInfo.Width, ImageInfo.Height));
	
	//this->SetContentSize(
	//	ImageInfo.Width,
	//	ImageInfo.Height
	//	);
}

void CTextureManager::ReleaseBitmapManager()
{
	delete Singleten;
}

void CTextureManager::AllDestroy()
{
	auto it = mBitmapMap.begin();

	while (it != mBitmapMap.end())
	{
		CTexture * _pD3Texture = it->second;
		if (_pD3Texture != NULL)
		{ 
			_pD3Texture->GetTexture()->Release();
			delete _pD3Texture;
			_pD3Texture = NULL;
		}

		it = mBitmapMap.erase(it);
		it = mBitmapMap.begin();
		//	it++;
	}
	if (mBitmapMap.empty() != NULL)
	{
		mBitmapMap.clear();
	}
	mBitmapMap.clear();
}

void CTextureManager::Destsory()
{
	if (Singleten != NULL)
	{
		delete Singleten;
		Singleten = NULL;
	}
}

void CTextureManager::ReleaseTexture(std::string FileName)
{
	auto it = mBitmapMap.begin();
	for (; it != mBitmapMap.end(); it++)
	{
		if (FileName == it->first)
		{
			//로딩 된게 있다면 릴리즈해 삭제한다.
			CTexture * _pD3Texture = it->second;
			if (_pD3Texture != NULL)
			{
				_pD3Texture->GetTexture()->Release();
				delete _pD3Texture;
				_pD3Texture = NULL;
				it = mBitmapMap.erase(it);
				return;
			}
		}
	}
	//로딩된게 없다면 끝내자
	return;
}

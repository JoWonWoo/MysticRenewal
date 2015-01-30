#pragma once
#include "Stdafx.h"

class CTextureManager
{
private:
	static CTextureManager* Singleten;
public:
	static CTextureManager* GetInstance();

	CTextureManager();
	virtual ~CTextureManager();


	CTexture * GetTexture(std::string  FileName);
	void LoadBitmapFile(std::string FileName);

	void ReleaseTexture(std::string FileName);

	void ReleaseBitmapManager();
	void AllDestroy();
	void Destsory();
private:
	std::map<std::string, CTexture *> mBitmapMap;
};


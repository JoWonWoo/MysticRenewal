#pragma once

#include "Stdafx.h"
#define  LPCSprite CSprite*

class CSprite : public CNode
{
private:
//	CTexture * m_Texture;

public:
	CSprite();
	~CSprite();

	virtual bool init();
	virtual bool initWithFile();
	virtual bool initWithFile(LPCSTR pszFilename);
	virtual bool initWithFile(LPCSTR pszFilename, const CRect& rect);
	
	virtual bool initWithTexture(CTexture * Texture);

	virtual void Update(float Tick);
	virtual void Rander();
	virtual void Control(UINT msg, LPARAM lParam);


};


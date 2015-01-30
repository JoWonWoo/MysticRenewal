#include "Stdafx.h"



CSprite::CSprite(void)
{
	init();
}
CSprite::~CSprite(void)
{
}

void CSprite::Update(float Tick)
{
	CNode::Update(Tick);
}
void CSprite::Rander()
{
	CNode::Rander();
}
void CSprite::Control(UINT msg, LPARAM lParam)
{
	CNode::Control(msg,lParam);
}
bool CSprite::init()
{
	return initWithFile();
}
bool CSprite::initWithFile()
{
	this->SetContentSize(0, 0);
	this->SetImageSize(0, 0);
//	m_Texture = NULL;
	return true;
}
bool CSprite::initWithFile(LPCSTR pszFilename)
{
	if (pszFilename == NULL)
	{
		return false;
	}

	CTextureManager::GetInstance()->LoadBitmapFile(pszFilename);
	CTexture * A = CTextureManager::GetInstance()->GetTexture(pszFilename);
	this->SetContentRect(
		0,0,
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
bool CSprite::initWithFile(LPCSTR pszFilename, const CRect& rect)
{
	if (pszFilename == NULL)
		return false;

	CTextureManager::GetInstance()->LoadBitmapFile(pszFilename);

	this->SetContentRect(rect.m_positon.x, rect.m_positon.y, rect.m_size.width, rect.m_size.height);
	CTexture * A = CTextureManager::GetInstance()->GetTexture(pszFilename);
	this->SetImageSize(
		A->getPixelsWide(),
		A->getPixelsHigh()
		); 
	
	filename = pszFilename;

	return true;
}
bool CSprite::initWithTexture(CTexture * Texture)
{
//	m_Texture = Texture;
	filename = Texture->Get_FileName();

	this->SetContentRect(0,0,Texture->getPixelsWide(), Texture->getPixelsHigh());
	this->SetImageSize(Texture->getPixelsWide(), Texture->getPixelsHigh());
	
	return true;
}

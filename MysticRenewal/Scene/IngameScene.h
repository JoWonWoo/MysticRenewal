#pragma once
#include "Stdafx.h"
class CIngameScene :
	public CScene
{
public:
	static CScene * Scene();
private:
	CIngameScene();
	~CIngameScene();
public:

	virtual void init();

	virtual void Update(float Tick);

	virtual void Rander();


	CSprite * m_BackGround;
};


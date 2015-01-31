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


	void MapDataLoad(const char * Filename);


private:
	std::vector<LPCSprite> m_TileVector;
	int m_TileWidthCnt;	//타일의 가로갯수.
	int ** m_Crash_Blocks;
};




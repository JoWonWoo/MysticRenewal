#pragma once
#include "Stdafx.h"
class CScene : public CNode
{
protected:
	int SceneNum;

public:
	CScene();
	~CScene();

	void Update(float Tick);
	void Rander();
	void Control(UINT msg, LPARAM lParam);

public:
	virtual void init();
};


#pragma once
#include "Stdafx.h"
class CGameObjectInit :
	public CNode
{
public:
	CGameObjectInit();
	~CGameObjectInit();

	virtual void Update(float Tick);

	virtual void Rander();


};


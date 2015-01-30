#pragma once
#include "Stdafx.h"
//3D스프라이트는 AddChild로 추가하지말고, 따로 랜더를 불러줄것. 기존 Node함수를 사용하지말것..!
class CSprite3D :
	public CSprite
{
private:
	C3Point Position_LT;	//좌상단
	C3Point Position_RT;	//우상단
	C3Point Position_LB;	//좌하단
	C3Point Position_RB;	//우하단

	C3Point Position_One;
public:
	CSprite3D();
	~CSprite3D();

	virtual void Update(float Tick);
	virtual void Rander();
	virtual void Control(UINT msg, LPARAM lParam);
	virtual bool initWithFile(LPCSTR pszFilename);

	void SetPosition(C3Point LT, C3Point RT, C3Point LB, C3Point RB);
	void SetPosition(C3Point Po);
	void SetPositionZ(float Z);

};


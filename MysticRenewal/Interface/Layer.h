#pragma once
#include "Stdafx.h"

class CLayer : public CNode
{
public:
	CLayer();
	~CLayer();

private:
	int R, G, B, A;
	CSize Layer_Size;
public:
	virtual void init();
	virtual void init(int R, int G, int B, int A);

	virtual void Update(float Tick);

	virtual void Rander();

	virtual void Control(UINT msg, LPARAM lParam);

	virtual void Keyboard_DownEvent(BYTE Key[MAX_KEY]);

	virtual void MouseEvent( DIMOUSESTATE MouseState);

	void Set_Layer_Size(CSize _size);
	void Set_Layer_SizeBy(CSize _size);
	CSize Get_Layer_Size();

};


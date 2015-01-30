#pragma once
#include "Stdafx.h"
class CLogoScene :
	public CLayer
{
public:
	static CScene * Scene();
private:
	CLogoScene();
	~CLogoScene();
public:

	virtual void init();

	virtual void Update(float Tick);

	virtual void Rander();

	virtual void Control(UINT msg, LPARAM lParam);

	virtual void Keyboard_DownEvent(BYTE Key[MAX_KEY]);

	virtual void MouseEvent( DIMOUSESTATE MouseState);


public:

	CSprite * m_Logo;
	CSprite * m_Coin;
	CSprite * m_LogWall;

	bool m_LogoMove;

	float m_Title_Begin_Time;

	enum Title_State{
		TitleUp,
		TitleBackGround,
		Idle
	};
	Title_State m_Update_State;


	int mButtonInex;
	CSprite * m_Start;
	CSprite * m_Exit;

	bool m_InPut_Downkey;
	bool m_InPut_Upkey;
	void Change_Button();

};


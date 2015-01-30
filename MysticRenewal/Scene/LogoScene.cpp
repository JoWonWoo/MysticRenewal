#include "Stdafx.h"

CScene * CLogoScene::Scene()
{
	auto * scene = new CScene();
	auto * This = new CLogoScene();

	This->init();
	scene->AddChild(This);

	return scene;
}


CLogoScene::CLogoScene()
{
}


CLogoScene::~CLogoScene()
{
}

void CLogoScene::init()
{
	Director::GetInstance()->Set_Use_3D_Camera(true);
	
	m_Logo = new CSprite();
	m_Logo->initWithFile("Resource/Logo/0.png");
	m_Logo->Set_Anchor_Point(CPoint(0.5f, 0.0f));
	m_Logo->SetPosition(CPoint(320, 380));
	this->AddChild(m_Logo, 1);
	m_LogoMove = false;
	m_Title_Begin_Time = 0.0f;
	m_Update_State = TitleUp;


	m_Coin = new CSprite();
	m_Coin->initWithFile("Resource/Logo/1.png");
	m_Coin->Set_Anchor_Point(CPoint(0.5f, 0.5f));
	this->AddChild(m_Coin, 0);
	m_Coin->SetPosition(CPoint(320, 180));
	m_Coin->SetAlpa(0);

	m_LogWall = new CSprite();
	m_LogWall->initWithFile("Resource/Logo/3.png");
	m_LogWall->Set_Anchor_Point(CPoint(0.5f, 0.5f));
	this->AddChild(m_LogWall, -1);
	m_LogWall->SetPosition(CPoint(320, 240));
	m_LogWall->SetAlpa(0);


	m_Start = new CSprite();
	m_Start->initWithFile("Resource/Logo/menu/2.png");
	m_Start->Set_Anchor_Point(CPoint(0.5f, 0.5f));
	this->AddChild(m_Start, 2);
	m_Start->SetPosition(CPoint(320, 350));
	m_Start->SetAlpa(0);

	m_Exit = new CSprite();
	m_Exit->initWithFile("Resource/Logo/menu/15.png");
	m_Exit->Set_Anchor_Point(CPoint(0.5f, 0.5f));
	this->AddChild(m_Exit, 2);
	m_Exit->SetPosition(CPoint(320, 400));
	m_Exit->SetAlpa(0);


	mButtonInex = -1;
	m_InPut_Downkey = false;
	m_InPut_Upkey = false;
}

void CLogoScene::Update(float Tick)
{
	switch (m_Update_State)
	{
	case TitleUp:
		if (m_Logo->GetPositionY() >= 10)
		{
			m_Logo->SetPositionBy(0, -3.0f);
			return;
		}
		else
			m_Logo->SetPositionY(10.0f);
		m_Update_State = TitleBackGround;
		break;
	case TitleBackGround:
		m_Title_Begin_Time += Tick;
		if (m_Title_Begin_Time >= 1000.0f)
		{
			float delta = (m_Title_Begin_Time - 1000.0f) * 255.0f / 1000.0f;
			if (delta >= 255)
			{
				delta = 255;
				m_Update_State = Idle;
				m_Start->SetAlpa(255);
				m_Exit->SetAlpa(255);
			}
			m_Coin->SetAlpa(delta);
			m_LogWall->SetAlpa(delta);
		}
		break;
	case Idle:
		if (mButtonInex == -1)
			return;
		else
		{
			if (mButtonInex == 1)
			{
				m_Start->initWithFile("Resource/Logo/menu/1.png");
				m_Exit->initWithFile("Resource/Logo/menu/15.png");
			}
			else if (mButtonInex == 2)
			{
				m_Start->initWithFile("Resource/Logo/menu/2.png");
				m_Exit->initWithFile("Resource/Logo/menu/5.png");
			}
		}
			break;
	}
}

void CLogoScene::Rander()
{
}

void CLogoScene::Control(UINT msg, LPARAM lParam)
{
}

void CLogoScene::Keyboard_DownEvent(BYTE Key[MAX_KEY])
{
	//아래쪽 방향키가 눌러졌는지 체크.
	if (Key[DIK_DOWN] & 0x80 && !m_InPut_Downkey)
	{
		Log("아래 방향키 눌림");
		Change_Button();
		m_InPut_Downkey = true;
	}
	else if (!(Key[DIK_DOWN] & 0x80) && m_InPut_Downkey)
	{
		m_InPut_Downkey = false;
	}
	//위쪽 방향키가 눌러졌는지 체크.
	if (Key[DIK_UP] & 0x80 && !m_InPut_Upkey)
	{
		Log("위 방향키 눌림");
		m_InPut_Upkey = true;
		Change_Button();
	}
	else if (!(Key[DIK_UP] & 0x80) && m_InPut_Upkey)
	{
		m_InPut_Upkey = false;
	}
}

void CLogoScene::MouseEvent( DIMOUSESTATE MouseState)
{
}

void CLogoScene::Change_Button()
{
	if (mButtonInex == 1)
		mButtonInex = 2;
	else
		mButtonInex = 1;
}

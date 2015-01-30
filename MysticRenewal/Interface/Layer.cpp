#include "Stdafx.h"


CLayer::CLayer()
{
	Layer_Size = Director::GetInstance()->Get_Winodw_Size();
}


CLayer::~CLayer()
{
}

void CLayer::init()
{
	R = 0;
	G = 0;
	B = 255;
	A = 0;

}

void CLayer::init(int R, int G, int B, int A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

void CLayer::Update(float Tick)
{
	
}

void CLayer::Rander()
{
	Direct3dx::GetInstance()->DrawColorBox(GetPosition(), Layer_Size, D3DCOLOR_ARGB(A, R, G, B));
}

void CLayer::Control(UINT msg, LPARAM lParam)
{
}

void CLayer::Keyboard_DownEvent(BYTE Key[MAX_KEY])
{
	////아래쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_DOWN] & 0x80)
	//{
	//	Log("아래 방향키 눌림");
	//}
	////위쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_UP] & 0x80)
	//{
	//	Log("위 방향키 눌림");
	//}
	////왼쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_LEFT] & 0x80)
	//{
	//	Log("왼쪽 방향키 눌림");
	//}
	////오른쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_RIGHT] & 0x80)
	//{
	//	Log("오른쪽 방향키 눌림");
	//}
}

void CLayer::MouseEvent( DIMOUSESTATE MouseState)
{
	//CCLog("마우스 값 %0.f, %0.f", m_Mouse.x, m_Mouse.y);
	/*if (m_mouse_state.rgbButtons[0] & 0x80)
	{
	Log("왼쪽 버튼 클릭!");
	}
	if (m_mouse_state.rgbButtons[1] & 0x80)
	{
	Log("오른쪽 버튼 클릭!");
	}
	if (m_mouse_state.rgbButtons[2] & 0x80)
	{
	Log("중앙 버튼 클릭!");
	}*/
}

void CLayer::Set_Layer_Size(CSize _size)
{
	Layer_Size = _size;
	this->SetContentRect(0, 0, _size.width, _size.height);
	this->SetImageSize(_size);
	
}

CSize CLayer::Get_Layer_Size()
{
	return Layer_Size;
}

void CLayer::Set_Layer_SizeBy(CSize _size)
{
	Layer_Size += _size;
	this->SetContentRect(0, 0, Layer_Size.width, Layer_Size.height);
	this->SetImageSize(Layer_Size); 
}

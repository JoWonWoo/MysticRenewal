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
	////�Ʒ��� ����Ű�� ���������� üũ.
	//if (Key[DIK_DOWN] & 0x80)
	//{
	//	Log("�Ʒ� ����Ű ����");
	//}
	////���� ����Ű�� ���������� üũ.
	//if (Key[DIK_UP] & 0x80)
	//{
	//	Log("�� ����Ű ����");
	//}
	////���� ����Ű�� ���������� üũ.
	//if (Key[DIK_LEFT] & 0x80)
	//{
	//	Log("���� ����Ű ����");
	//}
	////������ ����Ű�� ���������� üũ.
	//if (Key[DIK_RIGHT] & 0x80)
	//{
	//	Log("������ ����Ű ����");
	//}
}

void CLayer::MouseEvent( DIMOUSESTATE MouseState)
{
	//CCLog("���콺 �� %0.f, %0.f", m_Mouse.x, m_Mouse.y);
	/*if (m_mouse_state.rgbButtons[0] & 0x80)
	{
	Log("���� ��ư Ŭ��!");
	}
	if (m_mouse_state.rgbButtons[1] & 0x80)
	{
	Log("������ ��ư Ŭ��!");
	}
	if (m_mouse_state.rgbButtons[2] & 0x80)
	{
	Log("�߾� ��ư Ŭ��!");
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

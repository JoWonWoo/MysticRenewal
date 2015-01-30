#include "Stdafx.h"

Director* Director::Singleten = NULL;

//CDirectX_Singleton�� Singleton���� ����
Director* Director::GetInstance()
{
	if (Singleten == NULL)
	{
		Singleten = new Director;
	}
	return Singleten;
}
Director::Director()
{
	Camera_3D = false;
}

Director::~Director()
{
}

void Director::Set_Window_Size(CSize A)
{
	Window_Size = A;
}

CSize Director::Get_Winodw_Size()
{
	return Window_Size;
}

void Director::Set_Window_hWnd(HWND _hWnd)
{
	m_hWnd = _hWnd;
}

HWND Director::Get_Window_hWnd()
{
	return m_hWnd;
}
void Director::Set_Camera_2D(float x, float y)
{
	Direct3dx::GetInstance()->Set_Camera_2D(x, y);
}

void Director::Set_Camera_2D(CPoint _Position)
{
	Direct3dx::GetInstance()->Set_Camera_2D(_Position);
}

void Director::Move_Camera_2D(float x, float y)
{
	Direct3dx::GetInstance()->Move_Camera_2D(x,y);
}

void Director::Move_Camera_2D(CPoint _Position)
{
	Direct3dx::GetInstance()->Move_Camera_2D(_Position);
}

void Director::Set_Debug(bool _debug)
{
	Debug = _debug;
}

bool Director::Get_Debug()
{
	return Debug;
}

//150127 �� �Լ� �۵��ǹ̾���
/*
ī�޶� �����ڿ��� �� �Լ��� ȣ���� 2D���� 3D���� �Ǵ�������, 
ī�޶� �̱��汸���� �Ǿ������Ƿ� ��ó�� �ѹ��� ȣ���..
�׷��� ī�޶󿡼� Init_2D �Ǵ� Init_3D �� ����ϴ°� �� ȿ�����̶� �Ǵ�.
*/
void Director::Set_Use_3D_Camera(bool _is3d)
{
	Camera_3D = _is3d;
}

bool Director::Get_Use_3D_Camera()
{
	return Camera_3D;
}

void Director::Set_hInstance(HINSTANCE _hins)
{
	m_hInstance = _hins;
}

HINSTANCE Director::Get_hInstance()
{
	return m_hInstance;
}

void Director::Set_Mouse_By(CPoint _Point)
{
	m_Mouse += _Point;
	float MaxX = Camera::GetInstance()->Get_Eye_Vector().x;
	float MaxY = Camera::GetInstance()->Get_Eye_Vector().y;

	if (m_Mouse.x <= MaxX - (Director::GetInstance()->Get_Winodw_Size().width / 2) * Camera::GetInstance()->Get_Camera_Scale_2D())
		m_Mouse.x = MaxX - (Director::GetInstance()->Get_Winodw_Size().width / 2) * Camera::GetInstance()->Get_Camera_Scale_2D();
	else if (m_Mouse.x >= MaxX + (Director::GetInstance()->Get_Winodw_Size().width / 2) * Camera::GetInstance()->Get_Camera_Scale_2D()-50)
		m_Mouse.x = MaxX + (Director::GetInstance()->Get_Winodw_Size().width / 2) * Camera::GetInstance()->Get_Camera_Scale_2D()-50;

	if (m_Mouse.y <= MaxY - (Director::GetInstance()->Get_Winodw_Size().height / 2) * Camera::GetInstance()->Get_Camera_Scale_2D())
		m_Mouse.y = MaxY - (Director::GetInstance()->Get_Winodw_Size().height / 2) * Camera::GetInstance()->Get_Camera_Scale_2D();

	else if (m_Mouse.y >= MaxY + (Director::GetInstance()->Get_Winodw_Size().height / 2) * Camera::GetInstance()->Get_Camera_Scale_2D() - 50)
		m_Mouse.y = MaxY + (Director::GetInstance()->Get_Winodw_Size().height / 2) * Camera::GetInstance()->Get_Camera_Scale_2D() - 50;

//	Log("���� ���콺 ��ġ %f, %f", m_Mouse.x, m_Mouse.y);
}

void Director::Set_Mouse_To(CPoint _Point)
{
	m_Mouse = _Point;
}

CPoint Director::Get_Mouse()
{
	return m_Mouse;
}

void Director::ReSet_Mouse()
{
	Set_Mouse_To(CPoint(Window_Size.width / 2, Window_Size.height / 2));
}

void Director::Set_Sound_Listen_Position(CPoint _Sound_Listen_Position)
{
	Sound_Listen_Position = _Sound_Listen_Position;
}

CPoint Director::Get_Sound_Listen_Position()
{
	return Sound_Listen_Position;
}


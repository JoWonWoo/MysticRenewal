#pragma once
#include "Stdafx.h"
class Director
{
private:
	static Director* Singleten;
	Director();
	virtual  ~Director();

	CSize Window_Size;
	HWND m_hWnd;

	bool Debug;

	bool Camera_3D;
	HINSTANCE m_hInstance;

	CPoint m_Mouse;
public:
	static Director* GetInstance();

	//////////////////////////////////////////////////////////////////////////
	//사용하지 말것.
	void Set_Window_Size(CSize A);
	void Set_Window_hWnd(HWND _hWnd);
	//////////////////////////////////////////////////////////////////////////
	
	CSize Get_Winodw_Size();
	HWND Get_Window_hWnd();

	void Set_Camera_2D(float x, float y);
	void Set_Camera_2D(CPoint _Position);
	void Move_Camera_2D(float x, float y);
	void Move_Camera_2D(CPoint _Position);


	void Set_Debug(bool _debug);
	bool Get_Debug();

	void Set_Use_3D_Camera(bool _is3d);
	bool Get_Use_3D_Camera();

	void Set_hInstance(HINSTANCE _hins);
	HINSTANCE Get_hInstance();

	void ReSet_Mouse();
	void Set_Mouse_By(CPoint _Point);
	void Set_Mouse_To(CPoint _Point);
	CPoint Get_Mouse();

private:
	CPoint Sound_Listen_Position;
public:
	void Set_Sound_Listen_Position(CPoint _Sound_Listen_Position);
	CPoint Get_Sound_Listen_Position();
};


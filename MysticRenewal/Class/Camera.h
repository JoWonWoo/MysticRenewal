#pragma once
#include "Stdafx.h"
class Camera
{
private:
	D3DXVECTOR3 vEyePt;							/// 1. 눈의 위치
	D3DXVECTOR3 vLookatPt;						/// 2. 눈이 바라보는 위치
	D3DXVECTOR3 vUpVec;							/// 3. 업 벡터

	D3DXMATRIXA16 matView;						/// 카메라 행렬
	
	D3DXVECTOR3 vMove;							/// 3. 업 벡터


	static Camera* Singleten;
	Camera();

	D3DXMATRIXA16 matProj;						// 프로젝션 행렬

	float m_Scale;

public:
	~Camera();
	static Camera* GetInstance();

	void Init_2D();
	void Init_2D(float Window_widht, float Window_Height);
	void Init_3D();

	D3DXMATRIXA16 Get_Camera_Matrix();

	D3DXMATRIXA16 Get_Proj_Matrix();
	void Set_Proj_Ortho_WindowSize();
	void Set_Proj_Ortho(float width, float height, float front, float back);

	D3DXVECTOR3 Get_Eye_Vector();

	void Set_Proj_Pers(float angle, float height, float front, float back);
	void Set_Proj_Pers_default();

	void Set_Camera_Move(D3DXVECTOR3 _move);
	void Set_Camera_Move(float x, float y, float z);

	void Setting_Camera();

	void Set_Camera_Move_Front_3D(float move);
	void Set_Camera_Move_Back_3D(float move);
	void Set_Camera_Move_Left_3D(float move);
	void Set_Camera_Move_Right_3D(float move);

	void Set_Camera_Move_Angle_3D(float X_Angle, float Y_Angle);

	void Set_Camera_LootAt(float x, float y, float z = 0);
	void Set_Camera_Eye(float x, float y, float z = 0);

	void Set_Camera_MoveBy_2D(float x, float y);
	void Set_Camera_MoveBy_2D(CPoint _Position);
	void Set_Camera_MoveTo_2D(float x, float y);
	void Set_Camera_MoveTo_2D(CPoint _Position);

	CPoint CameraToReal(CPoint _point);
	CPoint CameraToReal(float _x, float _y);

	void Set_Camera_ScaleBy_2D(float _scale);
	void Set_Camera_ScaleTo_2D(float _scale);

	float Get_Camera_Scale_2D();
};


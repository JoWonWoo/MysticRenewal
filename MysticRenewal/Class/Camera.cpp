#include "Stdafx.h"

Camera* Camera::Singleten = NULL;

Camera* Camera::GetInstance()
{
	if (Singleten == NULL)
	{
		Singleten = new Camera;
	}
	return Singleten;
}
Camera::Camera()
{
	////디폴트값 생성
	
	if (Director::GetInstance()->Get_Use_3D_Camera())
		Init_3D();
	else
		Init_2D();

}


Camera::~Camera()
{
}


void Camera::Init_2D()
{
	vEyePt = D3DXVECTOR3(Director::GetInstance()->Get_Winodw_Size().width / 2, Director::GetInstance()->Get_Winodw_Size().height / 2, 50.0f);							/// 1. 눈의 위치( 0, 3.0, -5)
	vLookatPt = D3DXVECTOR3(Director::GetInstance()->Get_Winodw_Size().width / 2, Director::GetInstance()->Get_Winodw_Size().height / 2, 0.0f);						/// 2. 눈이 바라보는 위치( 0, 0, 0 )
	vUpVec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);							/// 3. 천정방향을 나타내는 상방벡터( 0, 1, 0 )
	
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성

	Set_Proj_Ortho_WindowSize();

	m_Scale = 1.0f;
	Director::GetInstance()->Set_Use_3D_Camera(false);
}

void Camera::Init_2D(float Window_widht, float Window_Height)
{
	vEyePt = D3DXVECTOR3(Window_widht / 2, Window_Height / 2, 5.0f);							/// 1. 눈의 위치( 0, 3.0, -5)
	vLookatPt = D3DXVECTOR3(Window_widht / 2, Window_Height / 2, 0.0f);						/// 2. 눈이 바라보는 위치( 0, 0, 0 )
	vUpVec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);							/// 3. 천정방향을 나타내는 상방벡터( 0, 1, 0 )

	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성
	Director::GetInstance()->Set_Use_3D_Camera(false);
}

//윈도우 사이즈가 화면에 딱 들어올수있게, 카메라 생성.
void Camera::Init_3D()
{
	float temp;
	float seta;
	float d;	//내가 구해야하는값
	temp = Director::GetInstance()->Get_Winodw_Size().height;
	temp /= 2;	//세로값
	seta = (D3DX_PI / 4) / 2;	//FOV /2
	d = temp / tan(seta);
	/*
	// 917;
	//800 과 900사이
	//왜?
	//가로 1280 세로 720
	1/d = tan(fov/2)
	d = 1 / tan(fov/2)
	= cot(fov/2)
	[출처] Perspective Projection Matrix 프로젝션행렬 유도 과정|작성자 양창선
	http://blog.naver.com/destinycs/140117769971
	*/

	vEyePt = D3DXVECTOR3(Director::GetInstance()->Get_Winodw_Size().width / 2,
		Director::GetInstance()->Get_Winodw_Size().height / 2,
		d);							/// 1. 눈의 위치( 0, 3.0, -5)
	vLookatPt = D3DXVECTOR3(Director::GetInstance()->Get_Winodw_Size().width / 2, Director::GetInstance()->Get_Winodw_Size().height / 2, 0.0f);						/// 2. 눈이 바라보는 위치( 0, 0, 0 )
	vUpVec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);							/// 3. 천정방향을 나타내는 상방벡터( 0, 1, 0 )
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성
	Set_Proj_Pers_default();
	Director::GetInstance()->Set_Use_3D_Camera(true);
}

D3DXMATRIXA16 Camera::Get_Camera_Matrix()
{
	return matView;
}

D3DXMATRIXA16 Camera::Get_Proj_Matrix()
{
	return matProj;
}

void Camera::Set_Proj_Ortho(float width, float height, float front, float back)
{
	D3DXMatrixOrthoLH(&matProj, width, height, front, back);
}

void Camera::Set_Proj_Ortho_WindowSize()
{
	Set_Proj_Ortho(Director::GetInstance()->Get_Winodw_Size().width, Director::GetInstance()->Get_Winodw_Size().height, 0, 100);
}


void Camera::Set_Proj_Pers(float angle, float height, float front, float back)
{
	D3DXMatrixPerspectiveFovLH(&matProj, angle, height, front, back);
}

void Camera::Set_Proj_Pers_default()
{
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, Director::GetInstance()->Get_Winodw_Size().width/Director::GetInstance()->Get_Winodw_Size().height, 1.0f, 5000.0f);
//	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, Director::GetInstance()->Get_Winodw_Size().height / Director::GetInstance()->Get_Winodw_Size().width, 1.0f, 1000.0f);
}

void Camera::Set_Camera_Move(float x, float y, float z)
{
	Set_Camera_Move(D3DXVECTOR3(x, y, z));
}

void Camera::Set_Camera_Move(D3DXVECTOR3 _move)
{
	vEyePt += _move;
	vLookatPt += _move;

	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성
	Direct3dx::GetInstance()->Set_Camera_Matrix();
}

void Camera::Set_Camera_Move_Front_3D(float move)
{
	D3DXVec3Normalize(&vMove, &D3DXVECTOR3(vLookatPt - vEyePt));

	vMove *= move;

	vEyePt += vMove;
	vLookatPt += vMove;
	//vUpVec += vMove;
	Setting_Camera();
}

void Camera::Set_Camera_Move_Back_3D(float move)
{
	D3DXVec3Normalize(&vMove, &D3DXVECTOR3(vLookatPt - vEyePt));

	vMove *= move;

	vEyePt -= vMove;
	vLookatPt -= vMove;
	//vUpVec -= vMove;
	Setting_Camera();
}

void Camera::Set_Camera_Move_Left_3D(float move)
{
	D3DXMATRIXA16 mRotation;						/// 회전행렬 결과
	D3DXVECTOR3 result;

	D3DXVec3Normalize(&vMove, &D3DXVECTOR3(vLookatPt - vEyePt));
	D3DXMatrixRotationAxis(&mRotation, &vUpVec, D3DX_PI / 2);
	D3DXVec3TransformCoord(&result, &vMove, &mRotation);

	result *= move;

	vEyePt -= result;
	vLookatPt -= result;
	Setting_Camera();
}

void Camera::Set_Camera_Move_Right_3D(float move)
{
	D3DXMATRIXA16 mRotation;						/// 회전행렬 결과
	D3DXVECTOR3 result;

	D3DXVec3Normalize(&vMove, &D3DXVECTOR3(vLookatPt - vEyePt));
	D3DXMatrixRotationAxis(&mRotation, &vUpVec, D3DX_PI / 2);
	D3DXVec3TransformCoord(&result, &vMove, &mRotation);

	result *= move;

	vEyePt += result;
	vLookatPt += result;
	Setting_Camera();
}

void Camera::Setting_Camera()
{
	if (!Director::GetInstance()->Get_Use_3D_Camera())
		Set_Proj_Ortho(Director::GetInstance()->Get_Winodw_Size().width * m_Scale, Director::GetInstance()->Get_Winodw_Size().height *m_Scale, -200, 200);
	
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);	/// 1,2,3의 값으로 뷰행렬 생성
	Direct3dx::GetInstance()->Set_Camera_Matrix();
}

void Camera::Set_Camera_Move_Angle_3D(float X_Angle, float Y_Angle)
{
	D3DXMATRIXA16 mRotation;						/// 회전행렬 결과
	D3DXVECTOR3 result;
	X_Angle *= 0.01;
	D3DXMatrixRotationAxis(&mRotation, &vUpVec, X_Angle);

	D3DXVec3TransformCoord(&result, &(vLookatPt - vEyePt), &mRotation);
	vLookatPt = result + vEyePt;



	D3DXVec3Normalize(&vMove, &D3DXVECTOR3(vLookatPt - vEyePt));
	D3DXMatrixRotationAxis(&mRotation, &vUpVec, D3DX_PI / 2);
	D3DXVec3TransformCoord(&result, &vMove, &mRotation);


	Y_Angle *= 0.01;
	D3DXMatrixRotationAxis(&mRotation, &result, Y_Angle);

	D3DXVec3TransformCoord(&result, &(vLookatPt - vEyePt), &mRotation);
	vLookatPt = result + vEyePt;

	Setting_Camera();
}

D3DXVECTOR3 Camera::Get_Eye_Vector()
{
	return vEyePt;
}

CPoint Camera::CameraToReal(float _x, float _y)
{
	/*D3DXVECTOR2 tempVec;
	tempVec.x = m_OrtEyeMat.x + (_x - CD3DApp::GetInstance()->g_dScnX / 2.f)*(2048.f / m_Scale) / CD3DApp::GetInstance()->g_dScnX;
	tempVec.y = m_OrtEyeMat.y + (CD3DApp::GetInstance()->g_dScnY / 2.f - _y)*(2048.f / m_Scale) / CD3DApp::GetInstance()->g_dScnY;
	#if DEBUG
	printf("x = %f, y = %f\n", tempVec.x, tempVec.y);
	#endif
	return tempVec;*/

	CPoint tempVec;
//	tempVec.x = vEyePt.x + (_x - Director::GetInstance()->Get_Winodw_Size().width / 2);// / CD3DApp::GetInstance()->g_dScnX;
//	tempVec.y = vEyePt.y + (_y - Director::GetInstance()->Get_Winodw_Size().height / 2);// / CD3DApp::GetInstance()->g_dScnY;

	int x = vEyePt.x - Director::GetInstance()->Get_Winodw_Size().width / 2;
	int y = vEyePt.y - Director::GetInstance()->Get_Winodw_Size().height/ 2;
	// * (2048.f/m_Scale)/화면크기X
	// * (2048.f/m_Scale)/화면크기Y
	tempVec.x = vEyePt.x + (_x - Director::GetInstance()->Get_Winodw_Size().width / 2)*m_Scale;
	tempVec.y = vEyePt.y + (_y - Director::GetInstance()->Get_Winodw_Size().height / 2)*m_Scale;

//	tempVec.x = _x + x;// +(_x - CDirect3dx::GetInstance()->g_dScnX / 2.f) / CDirect3dx::GetInstance()->g_dScnX;
//	tempVec.y = _y + y;//vEyePt.y - Director::GetInstance()->Get_Winodw_Size().height / 2;// +(CDirect3dx::GetInstance()->g_dScnY / 2.f - _y) / CDirect3dx::GetInstance()->g_dScnY;
#if DEBUG
//	Log("x = %f, y = %f\n", tempVec.x, tempVec.y);
#endif
	return tempVec;
}

CPoint Camera::CameraToReal(CPoint _point)
{
	return CameraToReal(_point.x, _point.y);
}

void Camera::Set_Camera_MoveBy_2D(float x, float y)
{
	D3DXVECTOR3 vMove(x, y, 0);
	vEyePt += vMove;
	vLookatPt += vMove;
	Setting_Camera();
}

void Camera::Set_Camera_MoveBy_2D(CPoint _Position)
{
	Set_Camera_MoveBy_2D(_Position.x, _Position.y);
}

void Camera::Set_Camera_MoveTo_2D(float x, float y)
{
	D3DXVECTOR3 vMove(x, y, 0);
	D3DXVECTOR3 vMove2(x, y, 5);
	vEyePt = vMove2;
	vLookatPt = vMove;
	Setting_Camera();
}

void Camera::Set_Camera_MoveTo_2D(CPoint _Position)
{
	Set_Camera_MoveTo_2D(_Position.x, _Position.y);
}

void Camera::Set_Camera_ScaleBy_2D(float _scale)
{
	m_Scale += _scale/1000;
 
	Setting_Camera();
}

void Camera::Set_Camera_ScaleTo_2D(float _scale)
{
	m_Scale = _scale / 1000;
	Setting_Camera();
}

float Camera::Get_Camera_Scale_2D()
{
	return m_Scale;
}

void Camera::Set_Camera_LootAt(float x, float y, float z)
{
	D3DXVECTOR3 vMove(x, y, z);
	vLookatPt = vMove;
	Setting_Camera();
}

void Camera::Set_Camera_Eye(float x, float y, float z)
{
	D3DXVECTOR3 vMove(x, y, z);
	vEyePt = vMove;
	Setting_Camera();
}

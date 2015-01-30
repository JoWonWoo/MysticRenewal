#include "Stdafx.h"

CDirectInPut* CDirectInPut::Singleten = NULL;

//CDirectX_Singleton를 Singleton으로 만듬
CDirectInPut* CDirectInPut::GetInstance()
{
	if (Singleten == NULL)
	{
		Singleten = new CDirectInPut;
	}
	return Singleten;
}

CDirectInPut::CDirectInPut()
{

}

CDirectInPut::~CDirectInPut()
{
}

BOOL CDirectInPut::InitDirectInput(HWND hWnd)
{
	HRESULT hr;

	//DirectInput 객체를 생성한다.
	if (DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDX8, NULL) == -1)
	{
		return FALSE;
	}
	// Keyboard Device 객체를 생성한다.
	if (m_pDX8->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) == -1)
	{
		return FALSE;
	}
	// 키보드의 데이터 형식을 설정한다.
	if (m_pKeyboard->SetDataFormat(&c_dfDIKeyboard) == -1)
	{
		return FALSE;
	}
	// Keyboard Device의 협력레벨을 설정한다.
	hr = m_pKeyboard->SetCooperativeLevel(hWnd,
		DISCL_FOREGROUND /*| DISCL_NONEXCLUSIVE*/);

	if (hr == DIERR_UNSUPPORTED)
	{
		return FALSE;
	}
	m_pKeyboard->Acquire();

	//////////////////////////////////////////////////////////////////////////
	// 마우스
	//////////////////////////////////////////////////////////////////////////

	// Mouse Device 객체를 생성한다.
	if (m_pDX8->CreateDevice(GUID_SysMouse, &m_pMouse, NULL) == -1)
	{
		return FALSE;
	}
	// Mouse 데이터 형식을 설정한다.
	if (m_pMouse->SetDataFormat(&c_dfDIMouse) == -1)
	{
		return FALSE;
	}
	// Mouse Device의 협력레벨을 설정한다.
	hr = m_pMouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);


	if (hr == DIERR_UNSUPPORTED)
	{
		return FALSE;
	}


	// Device의 사용을 알린다.
	hr = m_pMouse->Acquire();
	//POINT A;
	//GetCursorPos(&A);
	//ScreenToClient(hWnd, &A); // 해당 클라이언트 기준으로 좌표를 변환한다
	//m_Mouse.x = A.x;
	//m_Mouse.y = A.y;

	return TRUE;
}
void CDirectInPut::ReleaseDirectInput()
{
	CC_SAFE_RELEASE(m_pKeyboard);
	CC_SAFE_RELEASE(m_pMouse);
	CC_SAFE_RELEASE(m_pDX8);
}
void CDirectInPut::OnUpdateKeyboard()
{
	HRESULT       hr;

	if (NULL == m_pKeyboard) return;
	ZeroMemory(&m_Key, sizeof(m_Key));

	hr = m_pKeyboard->GetDeviceState(sizeof(m_Key), &m_Key);

	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST)
		{
			hr = m_pKeyboard->Acquire();
		}
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	//이곳의 씬매니저의 컨트롤을 불러온다.(포커싱여부테스트)
	CSceneManager::GetInstance()->GetTopScene()->_KeyboardControl(m_Key);




	////아래쪽 방향키가 눌러졌는지 체크.
	//if (m_Key[DIK_DOWN] & 0x80)
	//{
	//	Log("아래 방향키 눌림");
	//}
	////위쪽 방향키가 눌러졌는지 체크.
	//if (m_Key[DIK_UP] & 0x80)
	//{
	//	Log("위 방향키 눌림");
	//}
	////왼쪽 방향키가 눌러졌는지 체크.
	//if (m_Key[DIK_LEFT] & 0x80)
	//{
	//	Log("왼쪽 방향키 눌림");
	//}
	////오른쪽 방향키가 눌러졌는지 체크.
	//if (m_Key[DIK_RIGHT] & 0x80)
	//{
	//	Log("오른쪽 방향키 눌림");
	//}
}

void CDirectInPut::OnUpdateMouse(HWND hWnd)
{
	HRESULT       hr;

	if (NULL == m_pMouse) return;
	ZeroMemory(&m_Key, sizeof(m_Key));

	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouse_state);
	if (FAILED(hr))
	{
		if (hr == DIERR_INPUTLOST)
		{
			hr = m_pMouse->Acquire();
		}
		return;
	}
	//	POINT A;
	//	GetCursorPos(&A);
	//	ScreenToClient(hWnd, &A); // 해당 클라이언트 기준으로 좌표를 변환한다

	//	m_Mouse.x = A.x;
	//	m_Mouse.y = A.y;
	//이곳의 씬매니저의 컨트롤을 불러온다. 여기서 포커싱 여부테스트?
	Director::GetInstance()->Set_Mouse_By(CPoint(m_mouse_state.lX, m_mouse_state.lY));
	CSceneManager::GetInstance()->GetTopScene()->_MouseControl(m_mouse_state);


	//CCLog("마우스 값 변화량 %d, %d, %d", m_mouse_state.lX, m_mouse_state.lY, m_mouse_state.lZ);
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

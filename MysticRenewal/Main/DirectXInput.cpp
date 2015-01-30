#include "Stdafx.h"

CDirectInPut* CDirectInPut::Singleten = NULL;

//CDirectX_Singleton�� Singleton���� ����
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

	//DirectInput ��ü�� �����Ѵ�.
	if (DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDX8, NULL) == -1)
	{
		return FALSE;
	}
	// Keyboard Device ��ü�� �����Ѵ�.
	if (m_pDX8->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) == -1)
	{
		return FALSE;
	}
	// Ű������ ������ ������ �����Ѵ�.
	if (m_pKeyboard->SetDataFormat(&c_dfDIKeyboard) == -1)
	{
		return FALSE;
	}
	// Keyboard Device�� ���·����� �����Ѵ�.
	hr = m_pKeyboard->SetCooperativeLevel(hWnd,
		DISCL_FOREGROUND /*| DISCL_NONEXCLUSIVE*/);

	if (hr == DIERR_UNSUPPORTED)
	{
		return FALSE;
	}
	m_pKeyboard->Acquire();

	//////////////////////////////////////////////////////////////////////////
	// ���콺
	//////////////////////////////////////////////////////////////////////////

	// Mouse Device ��ü�� �����Ѵ�.
	if (m_pDX8->CreateDevice(GUID_SysMouse, &m_pMouse, NULL) == -1)
	{
		return FALSE;
	}
	// Mouse ������ ������ �����Ѵ�.
	if (m_pMouse->SetDataFormat(&c_dfDIMouse) == -1)
	{
		return FALSE;
	}
	// Mouse Device�� ���·����� �����Ѵ�.
	hr = m_pMouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);


	if (hr == DIERR_UNSUPPORTED)
	{
		return FALSE;
	}


	// Device�� ����� �˸���.
	hr = m_pMouse->Acquire();
	//POINT A;
	//GetCursorPos(&A);
	//ScreenToClient(hWnd, &A); // �ش� Ŭ���̾�Ʈ �������� ��ǥ�� ��ȯ�Ѵ�
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

	//�̰��� ���Ŵ����� ��Ʈ���� �ҷ��´�.(��Ŀ�̿����׽�Ʈ)
	CSceneManager::GetInstance()->GetTopScene()->_KeyboardControl(m_Key);




	////�Ʒ��� ����Ű�� ���������� üũ.
	//if (m_Key[DIK_DOWN] & 0x80)
	//{
	//	Log("�Ʒ� ����Ű ����");
	//}
	////���� ����Ű�� ���������� üũ.
	//if (m_Key[DIK_UP] & 0x80)
	//{
	//	Log("�� ����Ű ����");
	//}
	////���� ����Ű�� ���������� üũ.
	//if (m_Key[DIK_LEFT] & 0x80)
	//{
	//	Log("���� ����Ű ����");
	//}
	////������ ����Ű�� ���������� üũ.
	//if (m_Key[DIK_RIGHT] & 0x80)
	//{
	//	Log("������ ����Ű ����");
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
	//	ScreenToClient(hWnd, &A); // �ش� Ŭ���̾�Ʈ �������� ��ǥ�� ��ȯ�Ѵ�

	//	m_Mouse.x = A.x;
	//	m_Mouse.y = A.y;
	//�̰��� ���Ŵ����� ��Ʈ���� �ҷ��´�. ���⼭ ��Ŀ�� �����׽�Ʈ?
	Director::GetInstance()->Set_Mouse_By(CPoint(m_mouse_state.lX, m_mouse_state.lY));
	CSceneManager::GetInstance()->GetTopScene()->_MouseControl(m_mouse_state);


	//CCLog("���콺 �� ��ȭ�� %d, %d, %d", m_mouse_state.lX, m_mouse_state.lY, m_mouse_state.lZ);
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

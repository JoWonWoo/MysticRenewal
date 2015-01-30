#pragma once
class CDirectInPut
{
private:
	static CDirectInPut* Singleten;
	CDirectInPut();
	virtual  ~CDirectInPut();
private:
	//DirectInput °´Ã¼.
	LPDIRECTINPUT8        m_pDX8 = NULL;
	//Device °´Ã¼.
	LPDIRECTINPUTDEVICE8  m_pKeyboard = NULL;

	BYTE                  m_Key[MAX_KEY];

	//////////////////////////////////////////////////////////////////////////
	LPDIRECTINPUTDEVICE8  m_pMouse = NULL;
	DIMOUSESTATE          m_mouse_state;

	CPoint m_Mouse;
public:
	static CDirectInPut* GetInstance();

	BOOL InitDirectInput(HWND hWnd);
	void ReleaseDirectInput();
	void OnUpdateKeyboard();
	void OnUpdateMouse(HWND hWnd);


};


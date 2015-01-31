#include "Stdafx.h"

//#define RELEASE

LPCSTR WindowName = "MysticRenewal";
float g_iWindowWidth = 640;
float g_iWindowHeight = 480;

#ifdef RELEASE
bool g_bWindowed_Mode = false;
#else
bool g_bWindowed_Mode = true;
#endif
HWND g_hWnd;

//////////////////////////////////////////////////////////////////////////

BOOL GameLoop();
bool GameInit();
BOOL GameControl(UINT msg, LPARAM lParam);
BOOL GameUpdate(float Tick);
BOOL GameRander();
BOOL GameDestroy();

long fFPSCount = 0;
long elapsed = 0;
int FPS = 0;
long OldCount = 0;
long Tick = 0;
long NewCount = GetTickCount();

long g_Frame = 60;

UINT g_msg;
LPARAM g_lParam;


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	g_msg = msg;
	g_lParam = lParam;

	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		GameControl(msg, lParam);// 컨트롤로 이동
		break;
	case WM_LBUTTONUP:
		GameControl(msg, lParam);// 컨트롤로 이동
		break;
	case WM_RBUTTONDOWN:
		GameControl(msg, lParam);// 컨트롤로 이동
		break;
	case WM_RBUTTONUP:
		GameControl(msg, lParam);// 컨트롤로 이동
		break;
	case WM_MOUSEMOVE:
		GameControl(msg, lParam);// 컨트롤로 이동
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		WindowName, LoadIcon(NULL, IDI_APPLICATION)
	};
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WindowName, WindowName,
		WS_OVERLAPPEDWINDOW, 0, 0, g_iWindowWidth, g_iWindowHeight,
		NULL, NULL, wc.hInstance, NULL);

	Director::GetInstance()->Set_Window_Size(CSize(g_iWindowWidth, g_iWindowHeight));
	Director::GetInstance()->Set_Window_hWnd(hWnd);


	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	RECT rcCilent = { 0, 0, g_iWindowWidth, g_iWindowHeight };

	AdjustWindowRect(&rcCilent, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(hWnd, NULL, 0, 0, (rcCilent.right - rcCilent.left), (rcCilent.bottom - rcCilent.top), SWP_NOZORDER | SWP_NOMOVE);

	g_hWnd = hWnd;

	if (!GameInit())
	{
		MessageBox(NULL, "DirectX 생성 실패", "알림", MB_OK);
		return -1;
	}
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//맨처음 씬
#ifdef RELEASE
	//CSceneManager::GetInstance()->PushScene(1, CSageScene::Scene());	//로고씬 (1번씬)
#else
//	CSceneManager::GetInstance()->PushScene(1, CLogoScene::Scene());	//로고씬 (1번씬)
	CSceneManager::GetInstance()->PushScene(1, CIngameScene::Scene());	//로고씬 (1번씬)

	//////////////////////////////////////////////////////////////////////////
	//Tool
	//////////////////////////////////////////////////////////////////////////
//	CSceneManager::GetInstance()->PushScene(1, MaptoolScene::Scene());	//로고씬 (1번씬)



#endif
	//Direct Input
	if (CDirectInPut::GetInstance()->InitDirectInput(hWnd) == FALSE)
	{
		MessageBox(NULL, "DirectX InPut 실패", "알림", MB_OK);
		CDirectInPut::GetInstance()->ReleaseDirectInput();
		return FALSE;
	}

	Director::GetInstance()->Set_hInstance(hInstance);

	srand(time(NULL));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameLoop();
		}
	}


	//clear
	GameDestroy();
	UnregisterClass(WindowName, wc.hInstance);

	//	_CrtDumpMemoryLeaks();
	return 0;
}


bool GameInit()
{
	Direct3dx::GetInstance()->InitDirect3D(g_hWnd, g_iWindowWidth, g_iWindowHeight, g_bWindowed_Mode);

	return true;
}
//
BOOL GameLoop()
{
	if (GetTickCount() - NewCount > (500 / g_Frame)) //1초가 1000인데.. 왜 500으로해야 정상 프레임이 나오는지 모르겠음.
	{
		OldCount = NewCount;
		NewCount = GetTickCount();

		Tick = NewCount - OldCount;
		if (Tick > 0)
			elapsed = elapsed + Tick;
#if DEBUG
		++fFPSCount;
		if (elapsed >= 1000)
		{
			FPS = fFPSCount;
			fFPSCount = 0;
			elapsed = elapsed - 1000;
			CCLog("[%d] 프레임 중...", FPS);
		}
#endif
		CDirectInPut::GetInstance()->OnUpdateKeyboard();
		CDirectInPut::GetInstance()->OnUpdateMouse(g_hWnd);
		GameUpdate(Tick);
		GameRander();

#ifdef RELEASE
		SetCursor(NULL);	//마우스 커서 제거
		SetCursorPos(Director::GetInstance()->Get_Winodw_Size().width / 2, Director::GetInstance()->Get_Winodw_Size().height / 2);
#endif
	}
	return TRUE;
}

BOOL GameControl(UINT msg, LPARAM lParam)
{
	return TRUE;
}

BOOL GameUpdate(float Tick)
{
	CSceneManager::GetInstance()->GetTopScene()->_Update(Tick);
	return TRUE;
}

BOOL GameRander()
{
	//백버퍼를 검은색으로 클린
	//Direct3dx::GetInstance()->Clear(D3DCOLOR_XRGB(255, 255, 255));
	Direct3dx::GetInstance()->Clear(D3DCOLOR_ARGB(0, 0, 0, 0));
	Direct3dx::GetInstance()->BeginScreen();

	CSceneManager::GetInstance()->GetTopScene()->_Rander();

#if DEBUG
	if (Director::GetInstance()->Get_Debug())
	{
		//프레임출력
		char s[80];
		sprintf_s(s, sizeof(s), "프레임 : %d", FPS);
		Direct3dx::GetInstance()->SetTextFLOAT(s, 0, Director::GetInstance()->Get_Winodw_Size().height - 100);
	}
#endif

	//	Direct3dx::GetInstance()->EndSprite();
	Direct3dx::GetInstance()->EndScreen();
	Direct3dx::GetInstance()->Present();
	return TRUE;
}

BOOL GameDestroy()
{
	Direct3dx::GetInstance()->ReleaseDirect3D();
	Direct3dx::GetInstance()->Destory();
	CDirectInPut::GetInstance()->ReleaseDirectInput();

	CTextureManager::GetInstance()->AllDestroy();
	CSceneManager::GetInstance()->AllDestroyScene();


	//CSoundManager::GetInstance()->AllDestroy();


	return TRUE;
}

#pragma once
#include "Stdafx.h"
#include "..\..\resource.h"
//////////////////////////////////////////////////////////////////////////
//맵툴
//맵툴 추가로 인해 Point, Rect, Size 에 전부 앞에 C추가
//////////////////////////////////////////////////////////////////////////
#include <GdiPlus.h>
#pragma comment(lib ,"gdiplus.lib")
using namespace Gdiplus;

class ColorBoxNode;
class MaptoolScene :
	public CScene
{
public:
	static CScene * Scene();
private:
	MaptoolScene();
	~MaptoolScene();

	static MaptoolScene* NowScene;
public:
	static MaptoolScene * GetNowScene();

	virtual void Update(float Tick);

	virtual void Rander();

	virtual void Keyboard_DownEvent(BYTE Key[MAX_KEY]);

	virtual void MouseEvent(DIMOUSESTATE MouseState);

	virtual void init();

	//////////////////////////////////////////////////////////////////////////
	/*
	윈도우 크기 640 480
	비율로 나누면 
	64 48,	32 24,	16 12,	8 4,	2 1...
	이중 타일로써 사용시 나오는 크기는
	10,20,40,80,320개
	10x10인 100개의 타일을 이용하는 64,28을 이용하는게 가장 효율적. 
	혹은 동적으로 할당..?
	*/
	//////////////////////////////////////////////////////////////////////////

	//수정, std Vector를 사용하는것이 좀더 효율적으로 보임.
	//void Init_Tile();
	//LPCSprite * * MapTile;	//3차원 포이..ㄴ..터..
	//int m_Tile_Cutting_Num; //타일을 몇개로 쪼갤것인지. 가로세로 동일


	std::vector<LPCSprite> m_TileVector;
	int m_TileWidthCnt;	//타일의 가로갯수.

	LPCSprite BackGround;

	//////////////////////////////////////////////////////////////////////////
	void Draw_Line();
	void OpenDlg();
	void CloseDlg();
	HWND		m_hDlg;		// 대화상자의 핸들
	static BOOL CALLBACK ObjectProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL Object_Proc(HWND hDlg, UINT iMSg, WPARAM wParam, LPARAM lParam);

	int m_StageIndex;
	Bitmap*		m_Tilemap01;	//타일맵
	Bitmap*		m_Tilemap02;	//타일맵
	Bitmap*		m_Tilemap03;	//타일맵

	Rect m_BmpRect_gdi;
	RECT m_BmpRect;
	//GDI 초기화
	ULONG_PTR gpToken;

	//다이럴로그안 타일 인덱스
	POINT mDlg_Mouse_Position;
	int m_Select_Tile_Index_Start;
	int m_Select_Tile_Index_End;
	int m_Select_Tile_Index;
	int m_Can_Select_Tile_Index;
	
	bool m_LButtonDown_dlr;
	//////////////////////////////////////////////////////////////////////////
	HWND		m_hDlg_st;		// 대화상자의 핸들
	static BOOL CALLBACK ObjectProc_st(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL Object_Proc_st(HWND hDlg, UINT iMSg, WPARAM wParam, LPARAM lParam);

	//////////////////////////////////////////////////////////////////////////


	LPCSprite SelectTile;
	int m_MapTileIndex;
	bool m_LButtonDown;
	bool m_RButtonDown;

	int ** m_Crash_Blocks;
	ColorBoxNode * ColorNode;

	enum MapToolState{
		ETextureSetting,
		ECrashBoxSetting
	};
	int mMapToolState;
};

class ColorBoxNode :
	public CNode
{
	virtual void Rander();
};

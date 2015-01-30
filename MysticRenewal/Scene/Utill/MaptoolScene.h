#pragma once
#include "Stdafx.h"
#include "..\..\resource.h"
//////////////////////////////////////////////////////////////////////////
//����
//���� �߰��� ���� Point, Rect, Size �� ���� �տ� C�߰�
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
	������ ũ�� 640 480
	������ ������ 
	64 48,	32 24,	16 12,	8 4,	2 1...
	���� Ÿ�Ϸν� ���� ������ ũ���
	10,20,40,80,320��
	10x10�� 100���� Ÿ���� �̿��ϴ� 64,28�� �̿��ϴ°� ���� ȿ����. 
	Ȥ�� �������� �Ҵ�..?
	*/
	//////////////////////////////////////////////////////////////////////////

	//����, std Vector�� ����ϴ°��� ���� ȿ�������� ����.
	//void Init_Tile();
	//LPCSprite * * MapTile;	//3���� ����..��..��..
	//int m_Tile_Cutting_Num; //Ÿ���� ��� �ɰ�������. ���μ��� ����


	std::vector<LPCSprite> m_TileVector;
	int m_TileWidthCnt;	//Ÿ���� ���ΰ���.

	LPCSprite BackGround;

	//////////////////////////////////////////////////////////////////////////
	void Draw_Line();
	void OpenDlg();
	void CloseDlg();
	HWND		m_hDlg;		// ��ȭ������ �ڵ�
	static BOOL CALLBACK ObjectProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL Object_Proc(HWND hDlg, UINT iMSg, WPARAM wParam, LPARAM lParam);

	int m_StageIndex;
	Bitmap*		m_Tilemap01;	//Ÿ�ϸ�
	Bitmap*		m_Tilemap02;	//Ÿ�ϸ�
	Bitmap*		m_Tilemap03;	//Ÿ�ϸ�

	Rect m_BmpRect_gdi;
	RECT m_BmpRect;
	//GDI �ʱ�ȭ
	ULONG_PTR gpToken;

	//���̷��α׾� Ÿ�� �ε���
	POINT mDlg_Mouse_Position;
	int m_Select_Tile_Index_Start;
	int m_Select_Tile_Index_End;
	int m_Select_Tile_Index;
	int m_Can_Select_Tile_Index;
	
	bool m_LButtonDown_dlr;
	//////////////////////////////////////////////////////////////////////////
	HWND		m_hDlg_st;		// ��ȭ������ �ڵ�
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

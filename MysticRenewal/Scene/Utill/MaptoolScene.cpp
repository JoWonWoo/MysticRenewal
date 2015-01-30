#include "Stdafx.h"

MaptoolScene * MaptoolScene::NowScene;
CScene * MaptoolScene::Scene()
{
	auto * scene = new CScene();
	auto * This = new MaptoolScene();

	This->init();
	scene->AddChild(This);
	NowScene = This;
	return scene;
}

MaptoolScene * MaptoolScene::GetNowScene()
{
	return NowScene;
}


MaptoolScene::MaptoolScene()
{
	m_TileWidthCnt = 80;
	m_StageIndex = 1;
}


MaptoolScene::~MaptoolScene()
{
	CloseDlg();
	GdiplusShutdown(gpToken);
}

void MaptoolScene::init()
{
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok)
	{
		MessageBox(NULL, TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."), TEXT("알림"), MB_OK);
		return ;
	}

	mMapToolState = ETextureSetting;
	m_Select_Tile_Index = -1;
	m_Can_Select_Tile_Index = -1;
	m_LButtonDown_dlr = false;
	m_Select_Tile_Index_Start = -1;
	m_Select_Tile_Index_End = -1;
	m_LButtonDown = false;
	m_RButtonDown = false;
	m_hDlg = NULL;
	BackGround = new CSprite();
	BackGround->initWithFile("Resource/Stage/st01_bg.bmp");
	this->AddChild(BackGround, 0 );

	m_Tilemap01 = new Bitmap(L"Resource/Stage/st01_tile.png");
	m_Tilemap02 = new Bitmap(L"Resource/Stage/st02_tile.png");
	m_Tilemap03 = new Bitmap(L"Resource/Stage/st03_tile.png");
	//640 112
	//64 48
	//10 x 4
	m_BmpRect_gdi = Rect(10, 50, 640, 112);
	SetRect(&m_BmpRect, 10, 50, 640+10, 112+50+50);

	OpenDlg();	


	SelectTile = new CSprite();
	SelectTile->initWithFile("Resource/Stage/st01_tile.png", CRect(0, 0, 0, 0));
	this->AddChild(SelectTile, 1 );


	int width = 640 / m_TileWidthCnt;
	int height = 480 / m_TileWidthCnt;
	m_Crash_Blocks = new int*[m_TileWidthCnt];
	for (int i = 0; i < m_TileWidthCnt; ++i)
	{
		m_Crash_Blocks[i] = new int[m_TileWidthCnt];
		memset(m_Crash_Blocks[i], 0, sizeof(int)*m_TileWidthCnt);   // 메모리 공간을 0으로 초기화
	}
	for (int i = 0; i < m_TileWidthCnt; i++)
	{
		for (int j = 0; j < m_TileWidthCnt; j++)
		{
			m_Crash_Blocks[j][i] = 0;
		}
	}

	ColorNode = new ColorBoxNode();
	this->AddChild(ColorNode, 10);
	ColorNode->Set_Visible(false);

}

void MaptoolScene::Update(float Tick)
{
//	throw std::logic_error("The method or operation is not implemented.");
	

}

void MaptoolScene::Rander()
{
//	throw std::logic_error("The method or operation is not implemented.");
	Draw_Line();
	//Draw_Crash_Box();
}


void MaptoolScene::Keyboard_DownEvent(BYTE Key[MAX_KEY])
{

//	throw std::logic_error("The method or operation is not implemented.");
}

void MaptoolScene::MouseEvent(DIMOUSESTATE MouseState)
{
	POINT Mouse;
	GetPhysicalCursorPos(&Mouse);
	ScreenToClient(Director::GetInstance()->Get_Window_hWnd(), &Mouse);
	switch (mMapToolState)
	{
	case ETextureSetting:
	{
							if (MouseState.rgbButtons[1] & 0x80 && !m_RButtonDown)
							{
								Log("오른쪽 버튼 클릭!");
								m_RButtonDown = true;

								auto it = m_TileVector.begin();
								while (it != m_TileVector.end())
								{
									if ((*it)->IsIn(CPoint(Mouse.x, Mouse.y)))
									{

										int width = 640 / m_TileWidthCnt;
										int height = 480 / m_TileWidthCnt;
										int x2 = (*it)->GetPosition().x / width;
										int y2 = (*it)->GetPosition().y / height;
										m_MapTileIndex = x2 + y2*m_TileWidthCnt;
										int x = m_MapTileIndex % m_TileWidthCnt;
										int y = m_MapTileIndex / m_TileWidthCnt;
										m_Crash_Blocks[x][y] = 0;

										int start = m_MapTileIndex;
										x2 = ((*it)->GetPosition().x + (*it)->GetContentSize().width) / width;
										y2 = ((*it)->GetPosition().y + (*it)->GetContentSize().height )/ height;
										m_MapTileIndex = x2 + y2*m_TileWidthCnt;
										int end = m_MapTileIndex;

										int ch = end - start;
										if (ch < 0) ch = -ch;
										int tx = ch % m_TileWidthCnt;
										int ty = ch / m_TileWidthCnt;
										for (int i = 0; i <= tx; i++)
										{
											for (int j = 0; j <= ty; j++)
											{
												if (x + i < m_TileWidthCnt &&
													y + j < m_TileWidthCnt)
													m_Crash_Blocks[x + i][y + j] = 0;
											}
										}
										this->RemoveChild(*it);
										m_TileVector.erase(it);
										return;
									}
									it++;
								}
							}
							else if (!(MouseState.rgbButtons[1] & 0x80) && m_RButtonDown)
								m_RButtonDown = false;

							if (m_Select_Tile_Index_Start == -1 || m_Select_Tile_Index_End == -1)
								return;
							if (
								Mouse.x < 0 || Mouse.x> Director::GetInstance()->Get_Winodw_Size().width ||
								Mouse.y < 0 || Mouse.y> Director::GetInstance()->Get_Winodw_Size().height
								)
								return;
							int width = 640 / m_TileWidthCnt;
							int height = 480 / m_TileWidthCnt;

							int x2 = Mouse.x / width;
							int y2 = Mouse.y / height;
							m_MapTileIndex = x2 + y2*m_TileWidthCnt;

							Pen p(Color(0, 0, 255), 2);
							//float형으로 하면 귀찮음으로.. 만약float형일때는 오류발생.
							int x = m_MapTileIndex % m_TileWidthCnt * width;
							int y = m_MapTileIndex / m_TileWidthCnt * height;
							SelectTile->SetPosition(x, y);
							//CCLog("마우스 값 %0.f, %0.f", m_Mouse.x, m_Mouse.y);
							if (MouseState.rgbButtons[0] & 0x80 && !m_LButtonDown)
							{
								Log("왼쪽 버튼 클릭!");
								m_LButtonDown = true;
								LPCSprite SpriteClone = new CSprite(*SelectTile);
								this->AddChild(SpriteClone, 2);
								m_TileVector.push_back(SpriteClone);

								int x = m_MapTileIndex % m_TileWidthCnt;
								int y = m_MapTileIndex / m_TileWidthCnt;
								m_Crash_Blocks[x][y] = 1;

								int ch = m_Select_Tile_Index_End - m_Select_Tile_Index_Start;
								if (ch < 0) ch = -ch;
								int tx = ch % m_TileWidthCnt;
								int ty = ch / m_TileWidthCnt;
								for (int i = 0; i <= tx; i++)
								{
									for (int j = 0; j <= ty; j++)
									{
										if (x + i < m_TileWidthCnt &&
											y + j < m_TileWidthCnt)
											m_Crash_Blocks[x + i][y + j] = 1;
									}
								}


							}
							else if (!(MouseState.rgbButtons[0] & 0x80) && m_LButtonDown)
								m_LButtonDown = false;
	}break;
	case ECrashBoxSetting:
	{

							 if (
								 Mouse.x < 0 || Mouse.x> Director::GetInstance()->Get_Winodw_Size().width ||
								 Mouse.y < 0 || Mouse.y> Director::GetInstance()->Get_Winodw_Size().height
								 )
								 return;
							 int width = 640 / m_TileWidthCnt;
							 int height = 480 / m_TileWidthCnt;

							 int x2 = Mouse.x / width;
							 int y2 = Mouse.y / height;
							 m_MapTileIndex = x2 + y2*m_TileWidthCnt;

							 int x = m_MapTileIndex % m_TileWidthCnt;
							 int y = m_MapTileIndex / m_TileWidthCnt;
							 //CCLog("마우스 값 %0.f, %0.f", m_Mouse.x, m_Mouse.y);
							 if (MouseState.rgbButtons[0] & 0x80)
							 {
								 if (IsDlgButtonChecked(m_hDlg_st, IDC_RADIO1))
									 m_Crash_Blocks[x][y] = 1;
								 else 
									 m_Crash_Blocks[x][y] = 2;
							 }

							 if (MouseState.rgbButtons[1] & 0x80 && !m_RButtonDown)
							 {
								 m_Crash_Blocks[x][y] = 0;
							 }
	}
	}
}

void MaptoolScene::Draw_Line()
{
	//640 480
	ID3DXLine *Line;
	D3DXCreateLine(Direct3dx::GetInstance()->GetD3DDevice(), &Line);
	Line->SetWidth(1);
	D3DXCOLOR LineColor = D3DCOLOR_RGBA(255, 0, 0, 0);
	D3DXVECTOR2 points[2];

	int Cnt = 640 / m_TileWidthCnt;
	for (int i = 0; i < m_TileWidthCnt; i++)
	{
		points[0] = D3DXVECTOR2(i*Cnt, 0);
		points[1] = D3DXVECTOR2(i*Cnt, 480);

		Line->Begin();
		Direct3dx::GetInstance()->Set_World_View_Matrix(0, 0);
		Line->Draw(points, 2, LineColor);    // 이런식으로도 그리기 가능
		Line->End();

		Direct3dx::GetInstance()->GetD3DDevice()->SetFVF(D3DFVF_XYZ);
		Direct3dx::GetInstance()->GetD3DDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 2, points, sizeof(points[0]));
	}
	Cnt = 480 / m_TileWidthCnt;
	for (int i = 0; i < m_TileWidthCnt; i++)
	{
		points[0] = D3DXVECTOR2(0, i*Cnt);
		points[1] = D3DXVECTOR2(640, i*Cnt);

		Line->Begin();
		Direct3dx::GetInstance()->Set_World_View_Matrix(0, 0);
		Line->Draw(points, 2, LineColor);    // 이런식으로도 그리기 가능
		Line->End();

		Direct3dx::GetInstance()->GetD3DDevice()->SetFVF(D3DFVF_XYZ);
		Direct3dx::GetInstance()->GetD3DDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 2, points, sizeof(points[0]));
	}
	Line->Release();
}

void MaptoolScene::OpenDlg()
{
	if (m_hDlg == NULL)
	{
		m_hDlg = CreateDialog(Director::GetInstance()->Get_hInstance(), MAKEINTRESOURCE(IDD_DIALOG1), Director::GetInstance()->Get_Window_hWnd(), (DLGPROC)ObjectProc);
		ShowWindow(m_hDlg, SW_SHOW);
	}
	if (m_hDlg_st == NULL)
	{
		m_hDlg_st = CreateDialog(Director::GetInstance()->Get_hInstance(), MAKEINTRESOURCE(IDD_DIALOG2), Director::GetInstance()->Get_Window_hWnd(), (DLGPROC)ObjectProc_st);
		ShowWindow(m_hDlg_st, SW_SHOW);
	}
}

void MaptoolScene::CloseDlg()
{
	if (m_hDlg != NULL)
	{
		DestroyWindow(m_hDlg);
		m_hDlg = NULL;
	}
	if (m_hDlg_st != NULL)
	{
		DestroyWindow(m_hDlg_st);
		m_hDlg_st = NULL;
	}
	
}
BOOL CALLBACK MaptoolScene::ObjectProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return MaptoolScene::GetNowScene()->Object_Proc(hDlg, iMsg, wParam, lParam);
}

BOOL MaptoolScene::Object_Proc(HWND hDlg, UINT iMSg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMSg)
	{
	case WM_CREATE:
		return 0;
	case WM_INITDIALOG:
		SetTimer(hDlg, 1, 60, NULL);//0.06초마다
		return 1;
	case WM_PAINT:
	{
					 if (  mMapToolState == ECrashBoxSetting)
						 return 0;
					 hdc = BeginPaint(hDlg, &ps);
					 HBRUSH hBr, oBr;
					 oBr = (HBRUSH)SelectObject(hdc, hBr = CreateSolidBrush(RGB(255, 255, 255)));

					// Rectangle(hdc, m_BmpRect_gdi.X, m_BmpRect_gdi.Y, m_BmpRect_gdi.Width, m_BmpRect_gdi.Height);
					 Rectangle(hdc, m_BmpRect.left, m_BmpRect.top, m_BmpRect.right, m_BmpRect.bottom);

					 SelectObject(hdc, oBr);
					 DeleteObject(hBr);

					 Graphics g(hdc);
					 switch (m_StageIndex)
					 {
					 case 1:
						 g.DrawImage(m_Tilemap01, m_BmpRect_gdi);
						 break;
					 case 2:
						 g.DrawImage(m_Tilemap02, m_BmpRect_gdi);
						 break;
					 case 3:
						 g.DrawImage(m_Tilemap03, m_BmpRect_gdi);
						 break;
					 }


					 if (m_Select_Tile_Index_Start != -1)
					 {
						 Pen p(Color(255, 0, 0), 2);
						 int width = 640 / m_TileWidthCnt;
						 int height = 480 / m_TileWidthCnt;
						 int x = m_Select_Tile_Index_Start % m_TileWidthCnt * width + m_BmpRect_gdi.X;
						 int y = m_Select_Tile_Index_Start / m_TileWidthCnt * height + m_BmpRect_gdi.Y;
						 Rect Select_Rect;
						 CRect Rt_Tile;
						 if (m_Select_Tile_Index_End == -1)
							 Select_Rect = Rect(
								 x, y, width, height
								 );
						 else
						 {
							 int ch = m_Select_Tile_Index_End - m_Select_Tile_Index_Start;
							 if (ch < 0) ch = -ch;
							 int tx = ch % m_TileWidthCnt * width + width;
							 int ty = ch / m_TileWidthCnt * height+height;
							 Select_Rect = Rect(
							 x, y, tx, ty
							 );
							 Rt_Tile.setRect(x - m_BmpRect_gdi.X, y - m_BmpRect_gdi.Y, tx, ty);
						 }
						 g.DrawRectangle(&p, Select_Rect);
						 SelectTile->initWithFile(SelectTile->Get_FileName(), Rt_Tile);
						 SelectTile->SetScaleX(SelectTile->GetContentSize().width / SelectTile->GetImageSize().width);
						 SelectTile->SetScaleY(SelectTile->GetContentSize().height / SelectTile->GetImageSize().height);
					 }

					 if (m_Select_Tile_Index != -1)
					 {
						 Pen p(Color(255, 0, 0),2);
						 //float형으로 하면 귀찮음으로.. 만약float형일때는 오류발생.
						 int width = 640 / m_TileWidthCnt;
						 int height = 480 / m_TileWidthCnt;
						 int x = m_Select_Tile_Index % m_TileWidthCnt * width + m_BmpRect_gdi.X;
						 int y = m_Select_Tile_Index / m_TileWidthCnt * height + m_BmpRect_gdi.Y;
						 Rect Select_Rect(
							 x, y, width, height
							 );
						 g.DrawRectangle(&p, Select_Rect);
					 }
					 if (m_Can_Select_Tile_Index != -1)
					 {
						 Pen p(Color(0, 0, 255),2);
						 //float형으로 하면 귀찮음으로.. 만약float형일때는 오류발생.
						 int width = 640 / m_TileWidthCnt;
						 int height = 480 / m_TileWidthCnt;
						 int x = m_Can_Select_Tile_Index % m_TileWidthCnt * width + m_BmpRect_gdi.X;
						 int y = m_Can_Select_Tile_Index / m_TileWidthCnt * height + m_BmpRect_gdi.Y;
						 Rect Select_Rect(
							 x, y, width, height
							 );
						 g.DrawRectangle(&p, Select_Rect);
					 }
					 EndPaint(hDlg, &ps);
	}
		break;
	case WM_TIMER:
	{
					 if ( mMapToolState == ECrashBoxSetting)
						 return 0;
					 GetPhysicalCursorPos(&mDlg_Mouse_Position);
					 ScreenToClient(hDlg, &mDlg_Mouse_Position);
					 //10 , 50 640 112
					 if (mDlg_Mouse_Position.x > 10 && 
						 mDlg_Mouse_Position.y>50 &&
						 mDlg_Mouse_Position.x < 650 &&
						 mDlg_Mouse_Position.y < 162)
					 {
						 int tempx = mDlg_Mouse_Position.x - 10;
						 int tempy = mDlg_Mouse_Position.y - 50;
						 tempx /= (640 / m_TileWidthCnt);
						 tempy /= (480 / m_TileWidthCnt);

						 m_Can_Select_Tile_Index = tempx + (tempy * m_TileWidthCnt);
					 }
					 else 
						 m_Can_Select_Tile_Index = -1;

					 //		KillTimer(hDlg, 1);
					 InvalidateRect(hDlg, &m_BmpRect, FALSE);
					 break;
	}
	case WM_LBUTTONDOWN:
		if (  mMapToolState == ECrashBoxSetting)
			return 0;
		if (m_Can_Select_Tile_Index == -1)
		{
			m_Select_Tile_Index_Start = -1;
			m_Select_Tile_Index_End = -1;
			return 0;
		}
		m_LButtonDown_dlr = true;
		m_Select_Tile_Index_Start = m_Can_Select_Tile_Index;
		m_Select_Tile_Index_End = -1;
		return 0;
	case WM_MOUSEMOVE:
		if (  mMapToolState == ECrashBoxSetting)
			return 0;
		if (m_LButtonDown_dlr)
		{
			if (m_Can_Select_Tile_Index == -1)
			{
				m_Select_Tile_Index_Start = -1;
				return 0;
			}
			m_Select_Tile_Index_End = m_Can_Select_Tile_Index;
		}
		return 0;
	case WM_LBUTTONUP:
		if (  mMapToolState == ECrashBoxSetting)
			return 0;
		m_LButtonDown_dlr = false;
		if (m_Can_Select_Tile_Index == -1)
		{
			m_Select_Tile_Index_Start = -1;
			m_Select_Tile_Index_End = -1;
			return 0;
		}
		m_Select_Tile_Index_End = m_Can_Select_Tile_Index;
		return 0;
	case WM_COMMAND:
		if (  mMapToolState == ECrashBoxSetting)
			return 0;
		switch (LOWORD(wParam))
		{
		case IDSTAGE01:
			m_StageIndex = 1;
			BackGround->initWithFile("Resource/Stage/st01_bg.bmp");
			SelectTile->initWithFile("Resource/Stage/st01_tile.png", CRect(0,0,0,0));
			InvalidateRect(hDlg, &m_BmpRect, FALSE);
			break;
		case IDSTAGE02:
			m_StageIndex = 2;
			BackGround->initWithFile("Resource/Stage/st02_bg.bmp");
			SelectTile->initWithFile("Resource/Stage/st02_tile.png", CRect(0, 0, 0, 0));
			InvalidateRect(hDlg, &m_BmpRect, FALSE);
			break;
		case IDSTAGE03:
			m_StageIndex =3;
			BackGround->initWithFile("Resource/Stage/st03_bg.bmp");
			SelectTile->initWithFile("Resource/Stage/st03_tile.png", CRect(0, 0, 0, 0));
			InvalidateRect(hDlg, &m_BmpRect, FALSE);
			break;
		//	switch (HIWORD(wParam))
		//	{
		//		// 선택이 변경되었다.
		//	case LBN_SELCHANGE:
		//	{
		//						  int index = SendMessage(m_hBmpList, LB_GETCURSEL, 0, 0);
		//						  char fileName[50];
		//						  SendMessage(m_hBmpList, LB_GETTEXT, index, (LPARAM)fileName);
		//						  auto iter = m_Bmps.find(fileName);
		//						  m_pSelBmp = iter->second;
		//						  if (m_pSelBmp->GetWidth() > m_pSelBmp->GetHeight())
		//						  {
		//							  if (m_pSelBmp->GetWidth() > m_BmpRect.right - m_BmpRect.left - 20.f)
		//								  m_BmpScale = (m_BmpRect.right - m_BmpRect.left - 20.f) / m_pSelBmp->GetWidth();
		//							  else
		//								  m_BmpScale = 1.f;
		//						  }
		//						  else
		//						  {
		//							  if (m_pSelBmp->GetHeight() > m_BmpRect.bottom - m_BmpRect.top - 20.f)
		//								  m_BmpScale = (m_BmpRect.bottom - m_BmpRect.top - 20.f) / m_pSelBmp->GetHeight();
		//							  else
		//								  m_BmpScale = 1.f;
		//						  }
		//						  InvalidateRect(hDlg, &m_BmpRect, FALSE);
		//	}
		//		break;
		//	}
		//	break;

		//case IDAMAKEOBJ:
		//{
		//				   int index = SendMessage(m_hBmpList, LB_GETCURSEL, 0, 0);
		//				   if (index == -1)
		//					   break;
		//				   char fileName[50];
		//				   SendMessage(m_hBmpList, LB_GETTEXT, index, (LPARAM)fileName);
		//				   //resources/map/object/%s

		//				   D3DXVECTOR3 pos = Camera::GetInstance()->Get_Eye_Vector();
		//				   char filePath[100];
		//				   //string * FileName = new string("resources/map/object/");// +fileName;
		//				   //FileName->append(fileName);
		//				   wsprintf(filePath, "resources/map/object/%s", fileName);
		//				   if (m_pObjs != NULL)
		//				   {
		//					   auto tempObj = new CSprite();
		//					   tempObj->initWithTexture(CTextureManager::GetInstance()->GetTexture(filePath));
		//					   tempObj->SetPosition(CPoint(pos.x, pos.y));
		//					   m_pObjs->push_back(tempObj);
		//				   }
		//}
		//	break;

		case IDCANCEL:
			DestroyWindow(hDlg);
			m_hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK MaptoolScene::ObjectProc_st(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return MaptoolScene::GetNowScene()->Object_Proc_st(hDlg, iMsg, wParam, lParam);
}

BOOL MaptoolScene::Object_Proc_st(HWND hDlg, UINT iMSg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMSg)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			//지형설치모드
			mMapToolState = ETextureSetting;
			ColorNode->Set_Visible(false);
			SelectTile->Set_Visible(true);
			break;
		case IDC_BUTTON2:
			//충돌박스설치모드
			mMapToolState = ECrashBoxSetting;
			ColorNode->Set_Visible(true);
			SelectTile->Set_Visible(false);
			break;
		case IDCANCEL:
			DestroyWindow(hDlg);
			m_hDlg = NULL;
			return 0;
		}
		break;
	}
	return 0;
}

//수정, std Vector를 사용하는것이 좀더 효율적으로 보임.
//void MaptoolScene::Init_Tile()
//{
//	MapTile = new LPCSprite*[m_Tile_Cutting_Num];
//	for (int i = 0; i < m_Tile_Cutting_Num; ++i) 
//	{
//		MapTile[i] = new LPCSprite[m_Tile_Cutting_Num];
//		memset(MapTile[i], 0, sizeof(LPCSprite)*m_Tile_Cutting_Num);   // 메모리 공간을 0으로 초기화
//	}
//}

void ColorBoxNode::Rander()
{
	if (!Get_Visible())
		return;
	MaptoolScene * MapS = MaptoolScene::GetNowScene();

	int width = 640 / MapS->m_TileWidthCnt;
	int height = 480 / MapS->m_TileWidthCnt;

	for (int i = 0; i < MapS->m_TileWidthCnt; i++)
	{
		for (int j = 0; j < MapS->m_TileWidthCnt; j++)
		{
			if (MapS->m_Crash_Blocks[j][i] == 0)
				continue;
			else if (MapS->m_Crash_Blocks[j][i] == 1)
			{//충돌박스
				CPoint Po = CPoint(j*width, i*height);
				CSize Si = CSize(width, height);
				Direct3dx::GetInstance()->DrawColorBox(Po, Si, D3DCOLOR_RGBA(255, 0, 0, 100));
			}
			else if (MapS->m_Crash_Blocks[j][i] == 2)
			{//충돌플랫폼
				CPoint Po = CPoint(j*width, i*height);
				CSize Si = CSize(width, height);
				Direct3dx::GetInstance()->DrawColorBox(Po, Si, D3DCOLOR_RGBA(0, 0, 255, 100));
			}
		}
	}
}

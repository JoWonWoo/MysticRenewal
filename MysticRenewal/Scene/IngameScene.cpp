#include "Stdafx.h"

CScene * CIngameScene::Scene()
{
	auto * scene = new CScene();
	auto * This = new CIngameScene();

	This->init();
	scene->AddChild(This);

	return scene;
}

CIngameScene::CIngameScene()
{
}


CIngameScene::~CIngameScene()
{
}

void CIngameScene::init()
{
	m_TileWidthCnt = 80;
	int width = 640 / m_TileWidthCnt;
	int height = 480 / m_TileWidthCnt;
	m_Crash_Blocks = new int*[m_TileWidthCnt];
	for (int i = 0; i < m_TileWidthCnt; ++i)
	{
		m_Crash_Blocks[i] = new int[m_TileWidthCnt];
		memset(m_Crash_Blocks[i], 0, sizeof(int)*m_TileWidthCnt);   // 메모리 공간을 0으로 초기화
	}

	Camera::GetInstance()->Init_3D();
	//전개도 모양으로 


	m_BackGround = new CSprite();
	m_BackGround->initWithFile("Resource/Stage/st01_bg.bmp");
	this->AddChild(m_BackGround, -1);
	m_BackGround->SetPosition(CPoint(0, 0));


	MapDataLoad("Resource/MapData/example.Jmdb");
}

void CIngameScene::Update(float Tick)
{

//	throw std::logic_error("The method or operation is not implemented.");
}

void CIngameScene::Rander()
{

//	throw std::logic_error("The method or operation is not implemented.");
}

void CIngameScene::MapDataLoad(const char * Filename)
{
	char addr[300];
	FILE* fp = fopen(Filename, "rt");
	const char* pTemp;

	fscanf(fp, "Mystic Arts MapDataFile \n 제작자 : 조원우 \n 연락처 : 01035399774\n\n");

	int cnt = 0;
	LPCSprite pTempSprite;
	float pX, pY;
	float pTempSizeX, pTempSizeY, pTempSizeW, pTempSizeH;
	float pScaleX, pScaleY;
	fscanf(fp, "Texture Count = %d\n\n", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		fscanf(fp, "FileName = %s PositionX = %f, PositionY = %f, textureRectX = %f, textureRectY = %f, textureRectWidth = %f, textureRectHeight = %f, ScaleX = %f, ScaleY = %f \n",
			addr,
			&pX,
			&pY,
			&pTempSizeX,
			&pTempSizeY,
			&pTempSizeW,
			&pTempSizeH,
			&pScaleX,
			&pScaleY
			);
		pTempSprite = new CSprite();
		pTempSprite->initWithFile(addr, CRect(pTempSizeX, pTempSizeY, pTempSizeW, pTempSizeH));
		pTempSprite->SetPosition(pX, pY);
		pTempSprite->SetScale(pScaleX, pScaleY);
		m_TileVector.push_back(pTempSprite);
		this->AddChild(pTempSprite, 2);
	}

	int width = 640 / m_TileWidthCnt;
	int height = 480 / m_TileWidthCnt;

	for (int i = 0; i < m_TileWidthCnt; i++)
	{
		for (int j = 0; j < m_TileWidthCnt; j++)
		{
			m_Crash_Blocks[j][i] = 0;
		}
	}

	int value;
	fscanf(fp, "BoundingBox Count = %d\n\n", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt; j++)
		{
			fscanf(fp, "%d,", &value);
			m_Crash_Blocks[j][i] = value;
			if (value != 0 && value != 1 && value != 2)
			{
				CCLog("ERROR!!!!!!!!!");
			}
		}
		fscanf(fp, "\n");
	}

	fclose(fp);
}

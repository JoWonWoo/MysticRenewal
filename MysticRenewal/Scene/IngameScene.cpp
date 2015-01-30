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
	Camera::GetInstance()->Init_3D();
	//전개도 모양으로 


	m_BackGround = new CSprite();
	m_BackGround->initWithFile("Resource/Stage/st01_bg.bmp");
	this->AddChild(m_BackGround, -1);
	m_BackGround->SetPosition(CPoint(0, 0));
}

void CIngameScene::Update(float Tick)
{

//	throw std::logic_error("The method or operation is not implemented.");
}

void CIngameScene::Rander()
{

//	throw std::logic_error("The method or operation is not implemented.");
}

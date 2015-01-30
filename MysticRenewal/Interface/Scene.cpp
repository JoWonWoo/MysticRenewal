#include "Stdafx.h"



CScene::CScene(void)
{
}


CScene::~CScene(void)
{
	this->RemoveFromParent();
}

void CScene::Update(float Tick)
{
	CNode::Update(Tick);
}

void CScene::Rander()
{
	CNode::Rander();
}

void CScene::Control(UINT msg, LPARAM lParam)
{
	CNode::Control(msg, lParam);
}
void CScene::init()
{

}

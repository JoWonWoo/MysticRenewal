#pragma once
#include "Stdafx.h"
//3D��������Ʈ�� AddChild�� �߰���������, ���� ������ �ҷ��ٰ�. ���� Node�Լ��� �����������..!
class CSprite3D :
	public CSprite
{
private:
	C3Point Position_LT;	//�»��
	C3Point Position_RT;	//����
	C3Point Position_LB;	//���ϴ�
	C3Point Position_RB;	//���ϴ�

	C3Point Position_One;
public:
	CSprite3D();
	~CSprite3D();

	virtual void Update(float Tick);
	virtual void Rander();
	virtual void Control(UINT msg, LPARAM lParam);
	virtual bool initWithFile(LPCSTR pszFilename);

	void SetPosition(C3Point LT, C3Point RT, C3Point LB, C3Point RB);
	void SetPosition(C3Point Po);
	void SetPositionZ(float Z);

};


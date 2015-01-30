#ifndef __NODE_H__
#define __NODE_H__
#include "Stdafx.h"


class CNode
{
protected:
	CPoint m_Position;					//default 0,0
	float m_PositionZ;
	std::list<CNode*> m_pChildren;		//Children
	CNode *m_pParent;                 //Parent, default NULL

	float m_fScaleX;			//default 1
	float m_fScaleY;			//default 1
	float m_fRotationX;			//default 0
	float m_fRotationY;			//default 0
	float m_fRotationZ;			//default 0

	CRect m_ContentSize;       //������ ������
	CSize m_ImageSize;       //�̹��� ������
	std::string filename;			//�̹��������̸�

	int TAG;	//�±�

	D3DXCOLOR m_Color;		//�÷�

	int Alpa_value;

public:
	CNode();
	~CNode();
	virtual void	Update(float Tick);
	virtual void	Rander();
	virtual void	Control(UINT msg, LPARAM lParam);

	void	_Update(float Tick);
	void	_Rander();
	void	_Control(UINT msg, LPARAM lParam);

	void	_KeyboardControl(BYTE Key[MAX_KEY]);

	bool                  m_Key[MAX_KEY];

	virtual void	Keyboard_DownEvent(BYTE Key[MAX_KEY]);

	void	_MouseControl(DIMOUSESTATE MouseState);
	virtual void	MouseEvent( DIMOUSESTATE MouseState);


	virtual void	AddChild(CNode * Child);			//�ڽ� �߰�
	virtual void	AddChild(CNode * Child,int z_order);			//�ڽ� �߰�
	virtual std::list<CNode*>* GetChildList();			//�ڽ� ����
	virtual CNode*	GetParent();						//�θ� ����
	virtual void	SetParent(CNode* Parent);			//�θ� ����
	virtual void	RemoveChild(CNode* child);			//�ڽ� ����
	virtual void	MovePosition(CPoint _point);		//��ǥ ����
	virtual void	MovePosition(float x, float y);		//��ǥ ����
	virtual void	SetPosition(CPoint _point);		//��ǥ ����
	virtual void	SetPosition(float x, float y);		//��ǥ ����
	virtual void	SetPosition(float x, float y, float z);		//��ǥ ����
	virtual void	SetPositionBy(float x, float y);		//��ǥ ����
	virtual void	SetPositionBy(float x, float y, float z);		//��ǥ ����
	virtual void	SetPositionX(float x);				//��ǥ ����
	virtual void	SetPositionY(float y);				//��ǥ ����
	virtual CPoint	GetPosition();						//��ǥ ����
	virtual float	GetPositionX();						//��ǥ ����
	virtual float	GetPositionY();						//��ǥ ����
	virtual bool	RemoveFromParent();					//�θ�κ��� �����ڱ��ڽ�����
	virtual void	RemoveAllChildren();				//�� �ڽ� ���� ���̱�
	virtual CRect	GetBoundingBox();					//�̹����ڽ� ����
	virtual void	SetPositionZ(float _z);
	virtual float	GetPositionZ();


	virtual void SetRotation(float fRotation);			//ȸ��������
	virtual float GetRotation();						//ȸ��������
	virtual void SetRotationX(float fRotationX);		//ȸ��������
	virtual float GetRotationX();						//ȸ��������
	virtual void SetRotationY(float fRotationY);		//ȸ��������
	virtual float GetRotationY();						//ȸ��������
	virtual void SetRotationZ(float fRotationZ);		//ȸ��������
	virtual float GetRotationZ();						//ȸ��������
	virtual void SetScaleX(float fScaleX);				//�����ϼ���
	virtual float GetScaleX();							//�����ϸ���
	virtual void SetScaleY(float fScaleY);				//�����ϼ���
	virtual float GetScaleY();							//�����ϸ���
	virtual void SetScale(float scale);					//�����ϼ���
	virtual float GetScale();							//�����ϸ���
	virtual void SetScale(float fScaleX, float fScaleY);	//������ ����

	virtual void SetImageSize(CSize _Size);
	virtual void SetImageSize(float width, float height);
	virtual CSize GetImageSize();						//�����̹��������� ����

	virtual void SetContentSize(CSize _Size);				//����̹��������� ����
	virtual void SetContentSize(float width, float height);	//����̹��������� ����
	virtual void SetContentSizeBy(CSize _Size);				//����̹��������� ����
	virtual void SetContentSizeBy(float width, float height);	//����̹��������� ����
	virtual CSize GetContentSize();						//����̹��������� ����
	virtual void SetContentRect(CRect _Rect);				//����̹��������� ����
	virtual void SetContentRect(float x,float y,float width,float height);				//����̹��������� ����
	virtual CRect GetContentRect();						//����̹��������� ����

	virtual void SetColor(D3DXCOLOR _color);
	virtual void SetColor(int r, int g, int b, int a);
	virtual D3DXCOLOR GetColor();

	virtual void SetAlpa(int _Alpa);
	virtual int GetAlpa();

	virtual LPCSTR Get_FileName();
	virtual void Set_FileName(std::string _filename);


	bool IsIn(CPoint _pos);

private:
	bool m_IsDestroy;
public:
	void Set_Destroy(bool _flag);
	bool Get_Destroy();

	bool Is_UI;


private:
	CPoint m_Anchor_Point;
public:
	void Set_Anchor_Point(CPoint an);
	void Set_Anchor_Point(float x, float y);

	CPoint Get_Anchor_Point();


private:
	bool m_Follow_Parent;
public:
	void Set_Follow_Parent(bool flag);
	bool Get_Follow_Parent();



private:
	bool m_visible;
public:
	bool Get_Visible();
	void Set_Visible(bool flag);



	virtual void Destroy(){};

};

#endif
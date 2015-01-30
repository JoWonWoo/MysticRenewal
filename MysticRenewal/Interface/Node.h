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

	CRect m_ContentSize;       //컨텐츠 사이즈
	CSize m_ImageSize;       //이미지 사이즈
	std::string filename;			//이미지파일이름

	int TAG;	//태그

	D3DXCOLOR m_Color;		//컬러

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


	virtual void	AddChild(CNode * Child);			//자식 추가
	virtual void	AddChild(CNode * Child,int z_order);			//자식 추가
	virtual std::list<CNode*>* GetChildList();			//자식 리턴
	virtual CNode*	GetParent();						//부모 리턴
	virtual void	SetParent(CNode* Parent);			//부모 설정
	virtual void	RemoveChild(CNode* child);			//자식 제거
	virtual void	MovePosition(CPoint _point);		//좌표 설정
	virtual void	MovePosition(float x, float y);		//좌표 설정
	virtual void	SetPosition(CPoint _point);		//좌표 설정
	virtual void	SetPosition(float x, float y);		//좌표 설정
	virtual void	SetPosition(float x, float y, float z);		//좌표 설정
	virtual void	SetPositionBy(float x, float y);		//좌표 설정
	virtual void	SetPositionBy(float x, float y, float z);		//좌표 설정
	virtual void	SetPositionX(float x);				//좌표 설정
	virtual void	SetPositionY(float y);				//좌표 설정
	virtual CPoint	GetPosition();						//좌표 리턴
	virtual float	GetPositionX();						//좌표 리턴
	virtual float	GetPositionY();						//좌표 리턴
	virtual bool	RemoveFromParent();					//부모로부터 현재자기자신제거
	virtual void	RemoveAllChildren();				//내 자식 전부 죽이기
	virtual CRect	GetBoundingBox();					//이미지박스 리턴
	virtual void	SetPositionZ(float _z);
	virtual float	GetPositionZ();


	virtual void SetRotation(float fRotation);			//회전값설정
	virtual float GetRotation();						//회전값리턴
	virtual void SetRotationX(float fRotationX);		//회전값설정
	virtual float GetRotationX();						//회전값리턴
	virtual void SetRotationY(float fRotationY);		//회전값설정
	virtual float GetRotationY();						//회전값리턴
	virtual void SetRotationZ(float fRotationZ);		//회전값설정
	virtual float GetRotationZ();						//회전값리턴
	virtual void SetScaleX(float fScaleX);				//스케일설정
	virtual float GetScaleX();							//스케일리턴
	virtual void SetScaleY(float fScaleY);				//스케일설정
	virtual float GetScaleY();							//스케일리턴
	virtual void SetScale(float scale);					//스케일설정
	virtual float GetScale();							//스케일리턴
	virtual void SetScale(float fScaleX, float fScaleY);	//스케일 설정

	virtual void SetImageSize(CSize _Size);
	virtual void SetImageSize(float width, float height);
	virtual CSize GetImageSize();						//실제이미지사이즈 리턴

	virtual void SetContentSize(CSize _Size);				//출력이미지사이즈 설정
	virtual void SetContentSize(float width, float height);	//출력이미지사이즈 설정
	virtual void SetContentSizeBy(CSize _Size);				//출력이미지사이즈 설정
	virtual void SetContentSizeBy(float width, float height);	//출력이미지사이즈 설정
	virtual CSize GetContentSize();						//출력이미지사이즈 리턴
	virtual void SetContentRect(CRect _Rect);				//출력이미지사이즈 설정
	virtual void SetContentRect(float x,float y,float width,float height);				//출력이미지사이즈 설정
	virtual CRect GetContentRect();						//출력이미지사이즈 리턴

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
#include "Stdafx.h"
//#include "System.h"
//#include "_Device.h"
//#include "SpriteManager.h"
//#include "GameManager.h"



CNode::CNode()
{
	m_Position.setPoint(0, 0);
	
	m_pParent = NULL;
	filename.clear();// = NULL;

	m_pParent = NULL;

	m_fScaleX = 1;
	m_fScaleY = 1;

	m_fRotationX = 0;
	m_fRotationY = 0;

	m_ContentSize.m_size.setSize(0, 0);

	TAG = -1;
	
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 255);

	Alpa_value = 255;
	Is_UI = false;
	m_PositionZ = 0;
	m_Anchor_Point.setPoint(0, 0);
	m_Follow_Parent = false;
	m_visible = true;
}
CNode::~CNode()
{
	CC_SAFE_DELETE(m_pParent);
	while (m_pChildren.size() != 0)
	{
		CNode * Temp = m_pChildren.back();
		m_pChildren.pop_back();
		CC_SAFE_DELETE(Temp);
	}
}
void CNode::Update(float Tick)
{
}

void CNode::Rander(){}

void CNode::Control(UINT msg, LPARAM lParam){}

void CNode::_Update(float Tick)
{
	auto it = GetChildList()->begin();
	while (it != GetChildList()->end())
	{
		if (*it != NULL)
			(*it++)->_Update(Tick);
		else
			*it++;
	}

	Update(Tick);
}
void CNode::_Rander()
{
	auto it = GetChildList()->begin();
	while (it != GetChildList()->end())
	{
		if (*it != NULL)
		{
			if ((*it)->GetPositionZ() < 0)
			{
				(*it++)->_Rander();
			}
			else
				*it++;
		}
		else
		{
			*it++;
		}
	}
	if (m_visible)
	{
		if (filename.size() != 0)
		{
			if (Is_UI)
			{
				Direct3dx::GetInstance()->DrawTexture_2D_UI(
					CTextureManager::GetInstance()->GetTexture(filename)->GetTexture(),
					GetImageSize().width,
					GetImageSize().height,
					GetPositionX(),
					GetPositionY(),
					GetPositionZ(),
					GetScaleX(),
					GetScaleY(),
					GetRotationX(),
					GetRotationY(),
					GetRotationZ(),
					GetColor(),
					GetContentRect(),
					Get_Anchor_Point().x,
					Get_Anchor_Point().y
					);
			}
			else
			{
				if (m_Follow_Parent && this->GetParent() != NULL)
				{
					Direct3dx::GetInstance()->DrawTexture_2D(
						CTextureManager::GetInstance()->GetTexture(filename)->GetTexture(),
						GetImageSize().width,
						GetImageSize().height,
						GetPositionX() + this->GetParent()->GetPositionX(),
						GetPositionY() + this->GetParent()->GetPositionY(),
						GetPositionZ(),
						GetScaleX() * this->GetParent()->GetScaleX(),
						GetScaleY() * this->GetParent()->GetScaleY(),
						GetRotationX() + this->GetParent()->GetRotationX(),
						GetRotationY() + this->GetParent()->GetRotationY(),
						GetRotationZ() + this->GetParent()->GetRotationZ(),
						GetColor(),
						GetContentRect(),
						Get_Anchor_Point().x,
						Get_Anchor_Point().y
						);
				}
				else
				{
					Direct3dx::GetInstance()->DrawTexture_2D(
						CTextureManager::GetInstance()->GetTexture(filename)->GetTexture(),
						GetImageSize().width,
						GetImageSize().height,
						GetPositionX(),
						GetPositionY(),
						GetPositionZ(),
						GetScaleX(),
						GetScaleY(),
						GetRotationX(),
						GetRotationY(),
						GetRotationZ(),
						GetColor(),
						GetContentRect(),
						Get_Anchor_Point().x,
						Get_Anchor_Point().y
						);
				}
			}
		}
	}

	Rander();

	auto it2 = GetChildList()->begin();
	while (it2 != GetChildList()->end())
	{
		if (*it2 != NULL)
		{
			if ((*it2)->GetPositionZ() >= 0)
			{
				(*it2++)->_Rander();
			}
			else
				*it2++;
		}
		else
		{
			*it2++;
		}
	}

}

void CNode::_Control(UINT msg, LPARAM lParam)
{
	std::list<CNode *>::iterator it;
	it = GetChildList()->begin();
	while (it != GetChildList()->end())
		if (*it != NULL)
			(*it++)->_Control(msg, lParam);
		else
			*it++;

	Control(msg, lParam);
}


//////////////////////////////////////////////////////////////////////////
//qsort용
//////////////////////////////////////////////////////////////////////////
class Abssort
{
public:
	bool operator() (CNode *a, CNode *b)const{
		return a->GetPositionZ() < b->GetPositionZ();
	}
};

void		CNode::AddChild(CNode * Child)
{
	if (Child->GetPositionZ() != NULL)
		AddChild(Child, Child->GetPositionZ());
	else
		AddChild(Child, 0);

}

void CNode::AddChild(CNode * Child, int z_order)
{
	if (Child == NULL)
		return;
	Child->SetPositionZ(z_order);
	m_pChildren.push_front(Child);
	Child->SetParent(this);

	m_pChildren.sort(Abssort());
}

std::list<CNode*>* CNode::GetChildList(){ return &m_pChildren; }
CNode*	CNode::GetParent(){ return m_pParent; }
void	CNode::SetParent(CNode* Parent){ m_pParent = Parent; }
void	CNode::RemoveChild(CNode* child)
{
	if (child == NULL)
		return;

	Log("while (child->GetChildList()->size() != 0) 진입");
	while (child->GetChildList()->size() != 0)
	{
		CNode * Temp = child->GetChildList()->front();
		child->RemoveChild(Temp);
	//	child->GetChildList()->pop_front();
	}


	Log("GetChildList()->remove(child); != 0) 진입");
	GetChildList()->remove(child);

	Log("child->Destroy(); != 0) 진입");
	child->Destroy();
	if (child != NULL)
		child->SetParent(NULL);
	Log("CC_SAFE_DELETE(child); 진입");
	CC_SAFE_DELETE(child);
	child = NULL;
	Log("RemoveChild(CNode* child) 완료");
}
void	CNode::RemoveAllChildren()
{
	if (m_pChildren.size() == 0)
		return;
	while (m_pChildren.size() != 0)
	{
		CNode * Temp = this->GetChildList()->front();
		this->GetChildList()->pop_front();
		this->RemoveChild(Temp);
	}
}
bool	CNode::RemoveFromParent()
{
	if (m_pParent == NULL)
		return false;

	m_pParent->RemoveChild(this);
	return true;
}
void	CNode::SetPosition(CPoint _point){ m_Position.setPoint(_point); }
void	CNode::SetPosition(float x, float y){ m_Position.setPoint(x, y); }
void	CNode::SetPosition(float x, float y, float z){ SetPosition(x, y); SetPositionZ(z); }
void	CNode::SetPositionZ(float _z){ m_PositionZ = _z; }
float	CNode::GetPositionZ(){	return m_PositionZ;}
void	CNode::SetPositionBy(float x, float y){ m_Position.setPointBy(x, y); }
void	CNode::SetPositionBy(float x, float y, float z){	SetPositionBy(x, y); m_PositionZ += z;}
void	CNode::SetPositionX(float x){ m_Position.x = x; }
void	CNode::SetPositionY(float y){ m_Position.y = y; }
CPoint	CNode::GetPosition(){ return m_Position; }
float	CNode::GetPositionX(){ return m_Position.x; }
float	CNode::GetPositionY(){ return m_Position.y; }
CRect	CNode::GetBoundingBox(){
	CRect rect;
	rect.setRect(GetPositionX(), GetPositionY(), GetContentSize().width, GetContentSize().height);
	return rect;
}

void CNode::SetRotation(float fRotation)
{
	m_fRotationX = m_fRotationY = fRotation;
}

float CNode::GetRotation()
{
	if (m_fRotationX == m_fRotationY)
		return m_fRotationX;
	else
		return -1;
}

void CNode::SetRotationX(float fRotationX)
{
	m_fRotationX = fRotationX;
}

float CNode::GetRotationX()
{
	return m_fRotationX;
}

void CNode::SetRotationY(float fRotationY)
{
	m_fRotationY = fRotationY;
}

float CNode::GetRotationY()
{
	return m_fRotationY;

}

void CNode::SetScaleX(float fScaleX)
{
	m_fScaleX = fScaleX;
}

float CNode::GetScaleX()
{
	return m_fScaleX;
}

void CNode::SetScaleY(float fScaleY)
{
	m_fScaleY = fScaleY;
}

float CNode::GetScaleY()
{
	return m_fScaleY;
}

void CNode::SetScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
}

void CNode::SetScale(float fScaleX, float fScaleY)
{
	m_fScaleX = fScaleX;
	m_fScaleY = fScaleY;
}

float CNode::GetScale()
{
	if (m_fScaleX == m_fScaleY)
		return m_fScaleX;
	else
		return -1;

}

void CNode::SetContentSize(CSize _Size)
{
	m_ContentSize.m_size = _Size;
}

void CNode::SetContentSize(float width, float height)
{
	m_ContentSize.m_size.width = width;
	m_ContentSize.m_size.height = height;
}

CSize CNode::GetContentSize()
{
	CSize m_Size = m_ContentSize.m_size;
//	m_Size.width = m_Size.width*GetScaleX();
//	m_Size.height = m_Size.height*GetScaleY();
	return m_Size;
}

void CNode::_KeyboardControl(BYTE Key[MAX_KEY])
{
	std::list<CNode *>::iterator it;
	it = GetChildList()->begin();
	while (it != GetChildList()->end())
		(*it++)->_KeyboardControl(Key);

	Keyboard_DownEvent(Key);

//	if (!m_Key[key])
//	{
//		m_Key[key] = true;
//		Keyboard_PressEvent(Key);
//	}
}

void CNode::Keyboard_DownEvent(BYTE Key[MAX_KEY])
{
	////아래쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_DOWN] & 0x80)
	//{
	//	Log("아래 방향키 눌림");
	//}
	////위쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_UP] & 0x80)
	//{
	//	Log("위 방향키 눌림");
	//}
	////왼쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_LEFT] & 0x80)
	//{
	//	Log("왼쪽 방향키 눌림");
	//}
	////오른쪽 방향키가 눌러졌는지 체크.
	//if (Key[DIK_RIGHT] & 0x80)
	//{
	//	Log("오른쪽 방향키 눌림");
	//}
}

void CNode::_MouseControl( DIMOUSESTATE MouseState)
{
	std::list<CNode *>::iterator it;
	it = GetChildList()->begin();
	while (it != GetChildList()->end())
		(*it++)->_MouseControl(MouseState);

	MouseEvent( MouseState);
}

void CNode::MouseEvent( DIMOUSESTATE MouseState)
{
	//CCLog("마우스 값 %0.f, %0.f", m_Mouse.x, m_Mouse.y);
	/*if (m_mouse_state.rgbButtons[0] & 0x80)
	{
	Log("왼쪽 버튼 클릭!");
	}
	if (m_mouse_state.rgbButtons[1] & 0x80)
	{
	Log("오른쪽 버튼 클릭!");
	}
	if (m_mouse_state.rgbButtons[2] & 0x80)
	{
	Log("중앙 버튼 클릭!");
	}*/
}

void CNode::MovePosition(CPoint _point)
{
	this->SetPosition(GetPositionX() + _point.x, GetPositionY() + _point.y);
}

void CNode::MovePosition(float x, float y)
{
	MovePosition(CPoint(x, y));
}

void CNode::SetColor(int r, int g, int b, int a)
{
	m_Color = D3DCOLOR_RGBA(r,g,b,a);		//컬러

}

void CNode::SetColor(D3DXCOLOR _color)
{
	m_Color = _color;		//컬러
}

D3DXCOLOR CNode::GetColor()
{
	return m_Color;
}

LPCSTR CNode::Get_FileName()
{
	return filename.c_str();
}

bool CNode::IsIn(CPoint _pos)
{
	if (_pos.x > m_Position.x&& _pos.x < m_Position.x + GetContentSize().width)
	{
		if (_pos.y > m_Position.y && _pos.y < m_Position.y + GetContentSize().height)
		{
#if DEBUG
			Log("오브젝트 크기 : left = %0.f, Right = %0.f, Top = %0.f, Bottom = %0.f"
				, m_Position.x 
				, m_Position.x + m_ContentSize.width 
				, m_Position.y 
				, m_Position.y + m_ContentSize.height);
			Log("내가 터치 한곳 %0.f , %0.f", _pos.x, _pos.y);
#endif
			return true;
		}
	}
	return false;
}

void CNode::SetAlpa(int _Alpa)
{
	Alpa_value = _Alpa;
	m_Color = D3DCOLOR_RGBA((int)(m_Color.r * 255), (int)(m_Color.g * 255), (int)(m_Color.b * 255), (int)Alpa_value);
}

int CNode::GetAlpa()
{
	return Alpa_value;
}

void CNode::SetContentSizeBy(CSize _Size)
{
	m_ContentSize.m_size += _Size;
}

void CNode::SetContentSizeBy(float width, float height)
{
	m_ContentSize.m_size.width += width;
	m_ContentSize.m_size.height += height;
}

void CNode::Set_FileName(std::string _filename)
{
	filename = _filename;
}


void CNode::SetRotationZ(float fRotationZ)
{
	m_fRotationZ = fRotationZ;
}

float CNode::GetRotationZ()
{
	return m_fRotationZ;
}

void CNode::Set_Destroy(bool _flag)
{
	m_IsDestroy = _flag;
}

bool CNode::Get_Destroy()
{
	return m_IsDestroy;
}

void CNode::SetImageSize(CSize _Size)
{
	m_ImageSize = _Size;
}

void CNode::SetImageSize(float width, float height)
{
	m_ImageSize.width = width;
	m_ImageSize.height = height;
}

CSize CNode::GetImageSize()
{
	return m_ImageSize;
}

void CNode::SetContentRect(CRect _Rect)
{
	m_ContentSize = _Rect;
}

void CNode::SetContentRect(float x, float y, float width, float height)
{
	SetContentRect(CRect(x, y, width, height));
}

CRect CNode::GetContentRect()
{
	return m_ContentSize;
}

void CNode::Set_Anchor_Point(CPoint an)
{
	m_Anchor_Point = an;
}

void CNode::Set_Anchor_Point(float x, float y)
{
	Set_Anchor_Point(CPoint(x, y));
}

CPoint CNode::Get_Anchor_Point()
{
	return m_Anchor_Point;
}

void CNode::Set_Follow_Parent(bool flag)
{
	m_Follow_Parent = flag;
}

bool CNode::Get_Follow_Parent()
{
	return m_Follow_Parent;
}

bool CNode::Get_Visible()
{
	return m_visible;
}

void CNode::Set_Visible(bool flag)
{
	m_visible = flag;
}






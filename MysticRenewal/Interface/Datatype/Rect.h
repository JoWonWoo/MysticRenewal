#pragma once
#include "Stdafx.h"
#include "Point.h"
#include "Size.h"

#define MAKECCRECT(x,y,width,height) Rect(x,y,width,height)

class CRect
{
public:
	CPoint m_positon;
	CSize  m_size;

public:
	CRect()
	{setRect(0.0f, 0.0f, 0.0f, 0.0f);}
	CRect(float x, float y, float width, float height)
	{setRect(x, y, width, height);}
	CRect(const CRect& other)
	{setRect(other.m_positon.x, other.m_positon.y, other.m_size.width, other.m_size.height);}
	CRect& operator= (const CRect& other)
	{setRect(other.m_positon.x, other.m_positon.y, other.m_size.width, other.m_size.height);return *this;}

	void setRect(float x, float y, float width, float height);
	float getMaxX() ;
	float getMidX() ;
	float getMinX() ;
	float getMaxY() ;
	float getMidY() ;
	float getMinY() ;
	bool equals(CRect& rect);
	bool containsPoint(CPoint & point);
	bool intersectsRect(CRect& rect);
};


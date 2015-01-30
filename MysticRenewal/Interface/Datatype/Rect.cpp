#include "Stdafx.h"


void CRect::setRect(float x, float y, float width, float height)
{
	m_positon.x = x;
	m_positon.y = y;

	m_size.width = width;
	m_size.height = height;
}

float CRect::getMaxX()
{
	return (float)(m_positon.x + m_size.width);	
}

float CRect::getMidX() 
	{
		return (float)(m_positon.x + m_size.width / 2.0);	
}

float CRect::getMinX()
{
	return (float)m_positon.x;	
}

float CRect::getMaxY()
{
	return m_positon.y + m_size.height;
}

float CRect::getMidY()
{
	return (float)(m_positon.y + m_size.height / 2.0);
}

float CRect::getMinY()
{
	return m_positon.y;
}

bool CRect::equals(CRect& rect)
{
			return(rect.m_positon.equals(m_positon) &&	rect.m_size.equals(m_size));	
}

bool CRect::containsPoint(CPoint & point)
{
		return (point.x >= getMinX() && point.x <= getMaxX()
			&& point.y >= getMinY() && point.y <= getMaxY());

}

bool CRect::intersectsRect(CRect& rect)
{
	//if( getMaxX() < rect.getMinX() ) 
	//	return false;
	//if( rect.getMaxX() <      getMinX() ) 
	//	return false;
	//if( getMaxY() < rect.getMinY() ) 
	//	return false;
	//if( rect.getMaxY() <      getMinY() ) 
	//	return false;

	//return true;

	return !(     getMaxX() < rect.getMinX() ||
		rect.getMaxX() <      getMinX() ||
		getMaxY() < rect.getMinY() ||
		rect.getMaxY() <      getMinY());
}

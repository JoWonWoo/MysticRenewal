#pragma once
#include "Stdafx.h"
#include "Point.h"

class CSize
{
public:
	float width;
	float height;

public:
	CSize(void) : width(0), height(0)	{	}
	CSize(float width, float height) : width(width), height(height)	{	}
	CSize(const CSize& other) : width(other.width), height(other.height)	{	}
	CSize(const CPoint& point) : width(point.x), height(point.y)	{	}
	
	CSize& operator= (const CSize& other)
	{setSize(other.width, other.height);return *this;}
	CSize& operator= (const CPoint& point)	
	{setSize(point.x, point.y);	return *this;}
	CSize operator+(const CSize& right) const
	{return CSize(this->width + right.width, this->height + right.height);}
	CSize operator+=(const CSize& right)
	{
		this->width += right.width;
		this->height += right.height;
		return CSize(this->width, this->height);
	}
	CSize operator-(const CSize& right) const
	{return CSize(this->width - right.width, this->height - right.height);}
	CSize operator*(float a) const
	{return CSize(this->width * a, this->height * a);}
	CSize operator/(float a) const
	{return CSize(this->width / a, this->height / a);}

	void setSize(float width, float height);
	bool equals(const CSize& target);
};
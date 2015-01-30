#include "Stdafx.h"


CPoint::CPoint(void)
{
	x = 0;
	y = 0;
}

CPoint::CPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

CPoint::CPoint(const CPoint& other)
{
	x = other.x;
	y = other.y;
}

void CPoint::setPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CPoint::setPoint(CPoint _point)
{
	this->x = _point.x;
	this->y = _point.y;
}

bool CPoint::equals(const CPoint& target)
{
	return (fabs(this->x - target.x) < FLT_EPSILON)
		&& (fabs(this->y - target.y) < FLT_EPSILON);
}

float CPoint::Length(CPoint *_Point)
{	
	return sqrt(_Point->x*_Point->x+_Point->y*_Point->y);
}

float CPoint::Length(CPoint *Me, CPoint *Other)
{
	return sqrt(
		(Me->x - Other->x)*(Me->x - Other->x) + (Me->y - Other->y)*(Me->y - Other->y));

}

CPoint * CPoint::Normalize(CPoint * p_out,CPoint * _Point)
{
	float _Length = Length(_Point);
	p_out->setPoint(_Point->x/_Length,_Point->y/_Length);
	return p_out;
}

void CPoint::setPointBy(float x, float y)
{
	this->x += x;
	this->y += y;
}

void CPoint::setPointBy(CPoint _point)
{
	this->x += _point.x;
	this->y += _point.y;
}

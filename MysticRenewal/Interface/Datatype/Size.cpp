#include "Stdafx.h"

void CSize::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

bool CSize::equals(const CSize& target)
{
	return (fabs(this->width  - target.width)  < FLT_EPSILON)
		&& (fabs(this->height - target.height) < FLT_EPSILON);
}


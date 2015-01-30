#pragma once
class CPoint
{
public:
	float x;
	float y;

public:
	CPoint(void);
	CPoint(float x, float y);
	CPoint(const CPoint& other);

	CPoint& operator= (const CPoint& other)
	{
		setPoint(other.x, other.y);	return *this;
	}
	CPoint operator+(const CPoint& right) const
	{
		return CPoint(this->x + right.x, this->y + right.y);
	}
	CPoint operator+=(const CPoint& right)
	{
		this->x += right.x; y += right.y;
		return CPoint(this->x, this->y);
	}
	CPoint operator-(const CPoint& right) const
	{
		return CPoint(this->x - right.x, this->y - right.y);
	}
	CPoint operator-() const
	{
		return CPoint(-x, -y);
	}
	CPoint operator*(float a) const
	{
		return CPoint(this->x * a, this->y * a);
	}
	CPoint operator/(float a) const
	{
		return CPoint(this->x / a, this->y / a);
	}

	void setPoint(float x, float y);
	void setPoint(CPoint _point);
	void setPointBy(float x, float y);
	void setPointBy(CPoint _point);

	bool equals(const CPoint& target);

	float Length(CPoint *_Point);							//벡터의 크기,길이
	float Length(CPoint *Me,CPoint *Other);							//벡터의 크기,길이
	CPoint * Normalize(CPoint * p_out, CPoint * _Point);	//단위벡터구하기.
};

class C3Point : public CPoint
{
public:
	C3Point(){}
	~C3Point(){}
public:
	C3Point(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	C3Point(const C3Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}
	float z;

	C3Point& operator= (const C3Point& other)
	{
		x = other.x; y = other.y; z = other.z; return *this;
	}
	C3Point operator+(const C3Point& right) const
	{
		return C3Point(this->x + right.x, this->y + right.y, this->z + right.z);
	}
	C3Point operator+=(const C3Point& right)
	{
		this->x += right.x; y += right.y; z += right.z;
		return C3Point(this->x, this->y, this->z);
	}
	C3Point operator-=(const C3Point& right)
	{
		this->x -= right.x; y -= right.y; z -= right.z;
		return C3Point(this->x, this->y, this->z);
	}
	C3Point operator-(const C3Point& right) const
	{
		return C3Point(this->x - right.x, this->y - right.y, this->z - right.z);
	}
	C3Point operator-() const
	{
		return C3Point(-x, -y, -z);
	}
	C3Point operator*(float a) const
	{
		return C3Point(this->x * a, this->y * a, this->z * a);
	}
	C3Point operator/(float a) const
	{
		return C3Point(this->x / a, this->y / a, this->z / a);
	}

	bool operator!=(const C3Point& right) const
	{
		if (this->x == right.x &&
			this->y == right.y &&
			this->z == right.z
			)
			return false;
		return true;

	}
	bool operator==(const C3Point& right) const
	{
		if (this->x == right.x &&
			this->y == right.y &&
			this->z == right.z
			)
			return true;
		return false;

	}
};